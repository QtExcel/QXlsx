#include "mini_formula_evaluator.hpp"

#include <QtCore/QRegularExpression>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <cmath>

namespace qxlsx_formula {

static QString strip_leading_equals(QString s)
{
    s = s.trimmed();
    if (s.startsWith('=')) s.remove(0, 1);
    return s.trimmed();
}

static int find_top_level_op(const QString& s, const QChar op1, const QChar op2)
{
    int depth = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        const QChar ch = s[i];
        if (ch == ')') ++depth;
        else if (ch == '(') --depth;
        else if (depth == 0 && (ch == op1 || ch == op2)) {
            // Exclude unary +/-
            if ((ch == '+' || ch == '-') && (i == 0)) continue;
            if ((ch == '+' || ch == '-') && QString("+-*/(").contains(s[i-1])) continue;
            return i;
        }
    }
    return -1;
}

mini_formula_evaluator_t::mini_formula_evaluator_t(get_value_fn_t get_value, get_formula_fn_t get_formula)
    : get_value_(std::move(get_value)), get_formula_(std::move(get_formula))
{
}

QVariant mini_formula_evaluator_t::eval(const QString& base_sheet, const QString& expr)
{
    const QString s = strip_leading_equals(expr);
    return parse_expression(base_sheet, s);
}

QString mini_formula_evaluator_t::trim_outer(const QString& s)
{
    QString t = s.trimmed();
    // Remove one pair of outer parentheses
    while (t.startsWith('(') && t.endsWith(')')) {
        int depth = 0;
        bool ok = true;
        for (int i = 0; i < t.size(); ++i) {
            const QChar ch = t[i];
            if (ch == '(') ++depth;
            else if (ch == ')') --depth;
            if (depth == 0 && i != t.size() - 1) { ok = false; break; }
        }
        if (!ok) break;
        t = t.mid(1, t.size() - 2).trimmed();
    }
    return t;
}

bool mini_formula_evaluator_t::is_number_token(const QString& s)
{
    static const QRegularExpression re(R"(^[+-]?(\d+(\.\d*)?|\.\d+)$)");
    return re.match(s.trimmed()).hasMatch();
}

double mini_formula_evaluator_t::to_double_or_nan(const QVariant& v)
{
    bool ok = false;
    const double d = v.toDouble(&ok);
    return ok ? d : std::numeric_limits<double>::quiet_NaN();
}

QVariant mini_formula_evaluator_t::parse_expression(const QString& base_sheet, const QString& s)
{
    const QString t = trim_outer(s);
    const int idx = find_top_level_op(t, '+', '-');
    if (idx >= 0) {
        const QChar op = t[idx];
        const QVariant lv = parse_expression(base_sheet, t.left(idx));
        const QVariant rv = parse_term(base_sheet, t.mid(idx + 1));
        const double a = to_double_or_nan(lv);
        const double b = to_double_or_nan(rv);
        if (std::isnan(a) || std::isnan(b)) return {};
        return (op == '+') ? QVariant(a + b) : QVariant(a - b);
    }
    return parse_term(base_sheet, t);
}

QVariant mini_formula_evaluator_t::parse_term(const QString& base_sheet, const QString& s)
{
    const QString t = trim_outer(s);
    const int idx = find_top_level_op(t, '*', '/');
    if (idx >= 0) {
        const QChar op = t[idx];
        const QVariant lv = parse_term(base_sheet, t.left(idx));
        const QVariant rv = parse_factor(base_sheet, t.mid(idx + 1));
        const double a = to_double_or_nan(lv);
        const double b = to_double_or_nan(rv);
        if (std::isnan(a) || std::isnan(b)) return {};
        if (op == '/' && b == 0.0) return {};
        return (op == '*') ? QVariant(a * b) : QVariant(a / b);
    }
    return parse_factor(base_sheet, t);
}

QVariant mini_formula_evaluator_t::parse_factor(const QString& base_sheet, const QString& s)
{
    QString t = trim_outer(s);

    // unary +
    if (t.startsWith('+')) return parse_factor(base_sheet, t.mid(1));

    // unary -
    if (t.startsWith('-')) {
        const QVariant v = parse_factor(base_sheet, t.mid(1));
        const double a = to_double_or_nan(v);
        if (std::isnan(a)) return {};
        return QVariant(-a);
    }

    // number
    if (is_number_token(t)) {
        bool ok = false;
        const double d = t.toDouble(&ok);
        return ok ? QVariant(d) : QVariant();
    }

    // string literal: "abc"
    if (t.size() >= 2 && t.startsWith('"') && t.endsWith('"')) {
        return QVariant(t.mid(1, t.size() - 2));
    }

    // function call?
    {
        static const QRegularExpression re(R"(^([A-Za-z_][A-Za-z0-9_]*)\((.*)\)$)");
        const auto m = re.match(t);
        if (m.hasMatch()) {
            return parse_function(base_sheet, t);
        }
    }

    // cell ref (with optional sheet)
    {
        QString sheet = base_sheet;
        int r = 0, c = 0;
        if (try_parse_sheet_cell_ref(t, sheet, r, c)) {
            return eval_cell(sheet, r, c);
        }
        if (try_parse_cell_ref(t, r, c)) {
            return eval_cell(base_sheet, r, c);
        }
    }

    return {};
}

static QStringList split_args_top_level(const QString& s)
{
    QStringList out;
    int depth = 0;
    QString cur;
    for (int i = 0; i < s.size(); ++i) {
        const QChar ch = s[i];
        if (ch == '(') ++depth;
        else if (ch == ')') --depth;
        if (depth == 0 && ch == ',') {
            out.push_back(cur.trimmed());
            cur.clear();
        } else {
            cur.push_back(ch);
        }
    }
    if (!cur.trimmed().isEmpty()) out.push_back(cur.trimmed());
    return out;
}

QVariant mini_formula_evaluator_t::parse_function(const QString& base_sheet, const QString& func)
{
    static const QRegularExpression re(R"(^([A-Za-z_][A-Za-z0-9_]*)\((.*)\)$)");
    const auto m = re.match(func.trimmed());
    if (!m.hasMatch()) return {};

    const QString name = m.captured(1).toUpper();
    const QString args_str = m.captured(2).trimmed();
    const QStringList args = split_args_top_level(args_str);

    auto eval_arg_number = [&](const QString& a) -> double {
        const QVariant v = eval(base_sheet, a);
        return to_double_or_nan(v);
    };

    if (name == "SUM" || name == "AVERAGE" || name == "MIN" || name == "MAX") {
        double acc = 0.0;
        double mn = std::numeric_limits<double>::infinity();
        double mx = -std::numeric_limits<double>::infinity();
        int cnt = 0;

        auto consume_value = [&](double d) {
            if (std::isnan(d)) return;
            acc += d;
            mn = std::min(mn, d);
            mx = std::max(mx, d);
            ++cnt;
        };

        for (const QString& a0 : args) {
            const QString a = a0.trimmed();

            // range: A1:B3 or Sheet1!A1:B3
            static const QRegularExpression re_sheet(R"(^([^!]+)!(.+)$)");
            static const QRegularExpression re_range(R"(^(\$?[A-Za-z]+\$?\d+):(\$?[A-Za-z]+\$?\d+)$)");

            QString sheet = base_sheet;
            QString range = a;

            const auto ms = re_sheet.match(a);
            if (ms.hasMatch()) {
                sheet = ms.captured(1).trimmed();
                range = ms.captured(2).trimmed();
            }

            const auto mr = re_range.match(range);
            if (mr.hasMatch()) {
                int r1=0,c1=0,r2=0,c2=0;
                if (!try_parse_cell_ref(mr.captured(1), r1, c1)) continue;
                if (!try_parse_cell_ref(mr.captured(2), r2, c2)) continue;
                if (r1 > r2) std::swap(r1, r2);
                if (c1 > c2) std::swap(c1, c2);
                for (int r = r1; r <= r2; ++r) {
                    for (int c = c1; c <= c2; ++c) {
                        consume_value(to_double_or_nan(eval_cell(sheet, r, c)));
                    }
                }
                continue;
            }

            // single value
            consume_value(eval_arg_number(a));
        }

        if (cnt == 0) return {};
        if (name == "SUM") return QVariant(acc);
        if (name == "AVERAGE") return QVariant(acc / cnt);
        if (name == "MIN") return QVariant(mn);
        if (name == "MAX") return QVariant(mx);
    }

    // IF(cond, a, b): cond is false if 0, true otherwise
    if (name == "IF" && args.size() >= 2) {
        const double cond = eval_arg_number(args[0]);
        if (std::isnan(cond)) return {};
        if (cond != 0.0) return eval(base_sheet, args[1]);
        if (args.size() >= 3) return eval(base_sheet, args[2]);
        return {};
    }

    return {};
}

bool mini_formula_evaluator_t::try_parse_cell_ref(const QString& token, int& row, int& col) const
{
    static const QRegularExpression re(R"(^\$?([A-Za-z]+)\$?(\d+)$)");
    const auto m = re.match(token.trimmed());
    if (!m.hasMatch()) return false;

    const QString col_str = m.captured(1).toUpper();
    const QString row_str = m.captured(2);

    int c = 0;
    for (const QChar ch : col_str) {
        if (ch < 'A' || ch > 'Z') return false;
        c = c * 26 + (ch.unicode() - 'A' + 1);
    }
    bool ok = false;
    const int r = row_str.toInt(&ok);
    if (!ok || r <= 0 || c <= 0) return false;

    row = r;
    col = c;
    return true;
}

bool mini_formula_evaluator_t::try_parse_sheet_cell_ref(const QString& token, QString& sheet, int& row, int& col) const
{
    // Sheet1!A1 (Sheet names in quotes are simply handled as-is in this implementation)
    const int bang = token.indexOf('!');
    if (bang <= 0) return false;
    const QString sname = token.left(bang).trimmed();
    const QString addr = token.mid(bang + 1).trimmed();
    int r=0,c=0;
    if (!try_parse_cell_ref(addr, r, c)) return false;
    sheet = sname;
    row = r;
    col = c;
    return true;
}

QVariant mini_formula_evaluator_t::eval_cell(const QString& sheet, int row, int col)
{
    const cell_key_t key{sheet, row, col};

    if (cell_cache_.contains(key)) return cell_cache_.value(key);

    if (evaluating_.contains(key)) {
        // Circular reference
        return {};
    }
    evaluating_.insert(key);

    QVariant v = get_value_ ? get_value_(sheet, row, col) : QVariant();

    // If there is no value, try to calculate with formula
    if ((!v.isValid() || v.isNull() || (v.typeId() == QMetaType::QString && v.toString().isEmpty())) && get_formula_) {
        const QString f = get_formula_(sheet, row, col);
        if (!f.isEmpty()) {
            const QVariant calc = eval(sheet, f);
            if (calc.isValid()) v = calc;
        }
    }

    evaluating_.remove(key);
    cell_cache_.insert(key, v);
    return v;
}

} // namespace qxlsx_formula

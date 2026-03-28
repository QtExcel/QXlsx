#pragma once

#include <QHash>
#include <QSet>
#include <QString>
#include <QVariant>
#include <functional>

namespace qxlsx_formula {

// (sheet,row,col) key
struct cell_key_t
{
    QString sheet;
    int row = 0;
    int col = 0;

    bool operator==(const cell_key_t& o) const noexcept
    {
        return sheet == o.sheet && row == o.row && col == o.col;
    }
};

// Qt6: To use a custom key in QHash, you need to overload qHash.
inline size_t qHash(const cell_key_t& k, size_t seed = 0) noexcept
{
    seed ^= ::qHash(k.sheet, seed);
    seed ^= ::qHash(k.row, seed + 0x9e3779b97f4a7c15ULL);
    seed ^= ::qHash(k.col, seed + 0x85ebca6b);
    return seed;
}

class mini_formula_evaluator_t
{
public:
    using get_value_fn_t   = std::function<QVariant(const QString& sheet, int row, int col)>;
    using get_formula_fn_t = std::function<QString(const QString& sheet, int row, int col)>;

    mini_formula_evaluator_t(get_value_fn_t get_value, get_formula_fn_t get_formula);

    // expr: in the form of "=B2+C2*2" or "B2+C2*2"
    QVariant eval(const QString& base_sheet, const QString& expr);

    // Evaluate a single cell (if there is no value and there is a formula, try to calculate)
    QVariant eval_cell(const QString& sheet, int row, int col);

private:
    QVariant parse_expression(const QString& base_sheet, const QString& s);
    QVariant parse_term(const QString& base_sheet, const QString& s);
    QVariant parse_factor(const QString& base_sheet, const QString& s);
    QVariant parse_function(const QString& base_sheet, const QString& func);

    bool try_parse_cell_ref(const QString& token, int& row, int& col) const;
    bool try_parse_sheet_cell_ref(const QString& token, QString& sheet, int& row, int& col) const;

    static QString trim_outer(const QString& s);
    static bool is_number_token(const QString& s);
    static double to_double_or_nan(const QVariant& v);

    get_value_fn_t   get_value_;
    get_formula_fn_t get_formula_;

    QHash<cell_key_t, QVariant> cell_cache_;
    QSet<cell_key_t> evaluating_;
};

} // namespace qxlsx_formula

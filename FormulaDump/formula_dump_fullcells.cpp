#include "formula_dump_fullcells.hpp"
#include "mini_formula_evaluator.hpp"

#include <QDebug>
#include <QTextStream>

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcell.h"
#include "xlsxcellformula.h"

namespace {

static QString cell_to_string(const QVariant& v)
{
    if (!v.isValid() || v.isNull()) return QString();

    // Simple output for numbers/strings only
    if (v.typeId() == QMetaType::Double || v.typeId() == QMetaType::Float ||
        v.typeId() == QMetaType::Int || v.typeId() == QMetaType::LongLong ||
        v.typeId() == QMetaType::UInt || v.typeId() == QMetaType::ULongLong) {
        return v.toString();
    }
    if (v.typeId() == QMetaType::QString) return v.toString();
    if (v.canConvert<QString>()) return v.toString();
    return QString();
}

static QString formula_text(const std::shared_ptr<QXlsx::Cell>& cell)
{
    if (!cell) return {};
    if (cell->hasFormula() ) {
        const auto f = cell->formula();
        // QXlsx's formula() often returns a string without '='.
        // Always prepend '=' for consistent output.
        if (!f.formulaText().startsWith( QChar('=') ))
            return (QString("=") + f.formulaText());
        return f.formulaText();
    }
    return {};
}

} // namespace

namespace qxlsx_dump {

formula_dump_fullcells::formula_dump_fullcells(QXlsx::Document* doc, dump_options_t opt)
    : doc_(doc), opt_(opt)
{
}

int formula_dump_fullcells::dump(const QString& sheet)
{
    if (!doc_) return 1;

    if (!sheet.isEmpty()) {
        return dump_one_sheet(sheet);
    }

    const QStringList sheets = doc_->sheetNames();
    int rc = 0;
    for (const QString& s : sheets) {
        rc |= dump_one_sheet(s);
    }
    return rc;
}

int formula_dump_fullcells::dump_one_sheet(const QString& sheet_name)
{
    QXlsx::AbstractSheet* sheet = doc_->sheet(sheet_name);
    auto* ws = dynamic_cast<QXlsx::Worksheet*>(sheet);
    if (!ws) return 0;

    const auto dim = ws->dimension();
    int max_r = dim.lastRow();
    int max_c = dim.lastColumn();

    if (opt_.max_rows > 0) max_r = std::min(max_r, opt_.max_rows);
    if (opt_.max_cols > 0) max_c = std::min(max_c, opt_.max_cols);

    qInfo().noquote() << QString("=== Sheet: %1 (rows=%2, cols=%3) ===").arg(sheet_name).arg(max_r).arg(max_c);

    // Simple formula evaluator (used only if needed)
    qxlsx_formula::mini_formula_evaluator_t evaluator(
        [&](const QString& s, int r, int c) -> QVariant {
            QXlsx::AbstractSheet* sh = doc_->sheet(s);
            auto* w = dynamic_cast<QXlsx::Worksheet*>(sh);
            if (!w) return {};
            const auto cell = w->cellAt(r, c);
            if (!cell) return {};
            return cell->value();
        },
        [&](const QString& s, int r, int c) -> QString {
            QXlsx::AbstractSheet* sh = doc_->sheet(s);
            auto* w = dynamic_cast<QXlsx::Worksheet*>(sh);
            if (!w) return {};
            const auto cell = w->cellAt(r, c);
            return formula_text(cell);
        }
    );

    int printed = 0;

    for (int r = 1; r <= max_r; ++r) {
        for (int c = 1; c <= max_c; ++c) {
            const auto cell = ws->cellAt(r, c);
            if (!cell) continue;

            const bool is_formula = cell->hasFormula();

            if (opt_.only_formula_cells && !is_formula) {
                continue;
            }

            const QString f = formula_text(cell);

            QVariant v = cell->value();
            QString vs = cell_to_string(v);

            // If it's a formula and the cached value is empty, try to calculate
            if (is_formula && opt_.evaluate_formulas) {
                if (vs.isEmpty()) {
                    const QVariant calc = evaluator.eval_cell(sheet_name, r, c);
                    const QString cs = cell_to_string(calc);
                    if (!cs.isEmpty()) {
                        v = calc;
                        vs = cs;
                    }
                }
            }

            if (!opt_.print_empty_value && vs.isEmpty() && is_formula) {
                // If it's a formula cell but the value is empty and the print empty value option is off, skip
                // (If you want to print the formula, change this condition.)
                // Currently, to match user expectations, the formula is printed and value can be empty
                ;
            }

            // 출력
            QTextStream out(stdout);
            out << "R " << r << " C " << c;
            if (is_formula) out << " formula: " << f;
            if (opt_.show_value) out << " value: " << vs;
            out << "\n";
            ++printed;
        }
    }

    qInfo().noquote() << QString("Printed %1 cells.").arg(printed);
    return 0;
}

} // namespace qxlsx_dump

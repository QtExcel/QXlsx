#include "formula_single_cell_evaluator.hpp"
#include "mini_formula_evaluator.hpp"

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcell.h"
#include "xlsxcellformula.h"

namespace {

static QString formula_text(const std::shared_ptr<QXlsx::Cell>& cell)
{
    if (!cell) return {};

    if (!cell->hasFormula()) return {};

    const QString f = cell->formula().formulaText();

           // If there is no '=' in Excel style, add it (you can remove this logic if you want)
    if (!f.isEmpty() && !f.startsWith('=')) return "=" + f;

    return f;
}

} // namespace

namespace qxlsx_dump {

formula_single_cell_evaluator::formula_single_cell_evaluator(QXlsx::Document* doc)
    : doc_(doc)
{
}

QVariant formula_single_cell_evaluator::evaluate(const QString& sheet, int row, int col)
{
    if (!doc_) return {};

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

    return evaluator.eval_cell(sheet, row, col);
}

} // namespace qxlsx_dump

#pragma once

#include <QString>
#include <QVariant>

namespace QXlsx { class Document; }

namespace qxlsx_dump {

class formula_single_cell_evaluator
{
public:
    explicit formula_single_cell_evaluator(QXlsx::Document* doc);

    QVariant evaluate(const QString& sheet, int row, int col);

private:
    QXlsx::Document* doc_ = nullptr;
};

} // namespace qxlsx_dump

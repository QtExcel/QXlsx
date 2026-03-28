#pragma once

#include "dump_options.hpp"

#include <QString>

namespace QXlsx { class Document; }

namespace qxlsx_dump {

class formula_dump_fullcells
{
public:
    formula_dump_fullcells(QXlsx::Document* doc, dump_options_t opt);

    // If sheet is empty, dump all sheets
    int dump(const QString& sheet = QString());

private:
    int dump_one_sheet(const QString& sheet_name);

    QXlsx::Document* doc_ = nullptr;
    dump_options_t opt_;
};

} // namespace qxlsx_dump

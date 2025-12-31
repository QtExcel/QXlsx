#pragma once

#include <QString>

namespace qxlsx_dump {

struct dump_options_t
{
    bool only_formula_cells = true;   // Default: Output only formula cells
    bool show_value = true;           // Output cell value
    bool evaluate_formulas = true;    // If there is no cached value, calculate with a simple calculator (within supported range)
    bool print_empty_value = false;   // Output even if the value is empty
    int  max_rows = 0;                // 0 means no limit
    int  max_cols = 0;                // 0 means no limit
};

} // namespace qxlsx_dump

#pragma once

namespace qxlsx_formula {

// Since dump_options_t appears in user build logs, options are integrated here.
struct dump_options_t {
    bool only_formula_cells = true;   // Dump only formula cells
    bool evaluate_formulas = false;   // Evaluate formulas (simple evaluator)
};

} // namespace qxlsx_formula

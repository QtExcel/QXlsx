# FormulaDump

FormulaDump is a lightweight C++ utility for extracting and evaluating formulas from Excel (XLSX) files using the QXlsx library. It provides options to dump formula cells, evaluate simple formulas, and output cell values in a customizable way.

## Features
- Dump all or specific sheets from an XLSX file
- Output only formula cells or all cells
- Evaluate formulas with a built-in mini evaluator (supports basic arithmetic and simple functions)
- Print cell values, formulas, or both
- Configurable output options (max rows/columns, print empty values, etc.)

## Requirements
- Qt 6.x
- QXlsx library (https://github.com/QtExcel/QXlsx)
- C++17 or later

## Usage

### Build
1. Clone this repository and QXlsx.
2. Open `FormulaDum.pro` in Qt Creator or build with qmake:
   ```sh
   qmake FormulaDum.pro
   make
   ```

### Run
The main executable allows you to dump formulas and values from an XLSX file. Example usage:

```sh
./FormulaDump <xlsx-file> [options]
```

#### Options
- `--sheet <name>`: Dump only the specified sheet
- `--all`: Dump all sheets
- `--only-formula`: Output only formula cells
- `--show-value`: Output cell values
- `--eval-formula`: Evaluate formulas if no cached value
- `--max-rows <n>`: Limit the number of rows
- `--max-cols <n>`: Limit the number of columns
- `--print-empty`: Print cells even if the value is empty

## Code Structure
- `main.cpp`: Entry point and CLI handling
- `formula_dump_fullcells.*`: Full sheet/cell dumping logic
- `mini_formula_evaluator.*`: Simple formula evaluator for basic Excel formulas
- `formula_single_cell_evaluator.*`: Evaluate a single cell's formula
- `dump_options.hpp`, `formula_dump_options.hpp`: Option structures for controlling output

## License
This project is licensed under the MIT License.

## Acknowledgements
- [QXlsx](https://github.com/QtExcel/QXlsx) for Excel file handling

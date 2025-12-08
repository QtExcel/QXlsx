
# ExcelTableEditor

This example demonstrates how to build a simple Excel editor using **Qt Widgets** and **QXlsx**.
It shows how to load workbook data into Qt models, edit sheets, and write the modified content back to an `.xlsx` file.

## Features

* Load Excel files with **multiple sheets**
* Display sheet contents in a `QTableView`
* Edit all cells (including row 1)
* Boolean values displayed as checkboxes
* Read & preserve basic cell formatting (font, alignment, colors)
* Sheet operations:
  * **Rename sheet**
  * **Add new sheet**
  * **Delete sheet**
  * **Reorder sheets** (move left/right)
* Save or Save As to produce a modified workbook

## User Interface

* A sheet toolbar allows selecting the active worksheet, renaming it, adding/removing sheets, and changing sheet order.
* The main area is a `QTableView` backed by a `QStandardItemModel`, making the sheet fully editable.

## How it Works

* Each worksheet is mapped to its own `QStandardItemModel`.
* All sheet data (including row 1) is loaded as editable items.
* Formatting is stored per-cell and reapplied to the item view.
* When saving:
  * A new `QXlsx::Document` is created
  * Sheets are added in the current order
  * Cell values and (available) formatting are written back

 

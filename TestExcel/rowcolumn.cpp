// rowcolumn.cpp

#include "xlsxdocument.h"
#include "xlsxformat.h"

#include <QtCore>
#include <QtGlobal>

int rowcolumn()
{
    QXlsx::Document xlsx;
    xlsx.write(1, 2, "Row:0, Col:2 ==> (C1)");

    // Set the height of the first row to 50.0(points)
    xlsx.setRowHeight(1, 50.0);

    // Set the width of the third column to 40.0(chars)
    xlsx.setColumnWidth(3, 3, 40.0);

    // Set style for the row 11th.
    QXlsx::Format format1;
    format1.setFontBold(true);
    format1.setFontColor(QColor(Qt::blue));
    format1.setFontSize(20);
    xlsx.write(11, 1, "Hello Row Style");
    xlsx.write(11, 6, "Blue Color");
    xlsx.setRowFormat(11, format1);
    xlsx.setRowHeight(11, 41);

    // Set style for the col [9th, 16th)
    QXlsx::Format format2;
    format2.setFontBold(true);
    format2.setFontColor(QColor(Qt::magenta));
    for (int row = 12; row <= 30; row++)
        for (int col = 9; col <= 15; col++)
            xlsx.write(row, col, row + col);
    xlsx.setColumnWidth(9, 16, 5.0);
    xlsx.setColumnFormat(9, 16, format2);

    // Autosize columns
    xlsx.addSheet("Autosize");
    QXlsx::Format header;
    header.setFontBold(true);
    header.setFontSize(20);

    // Custom number formats
    int row = 2;
    xlsx.write(row, 1, "Small", header);
    xlsx.write(row, 2, "Large header", header);
    for (int i = 0; i < 10; ++i) {
        xlsx.write(row + 1 + i, 1, i);
        xlsx.write(row + 1 + i, 2, i);
    }
    xlsx.autosizeColumnWidth(1, 2);

    xlsx.write(2, 4, "Small", header);
    xlsx.write(2, 5, "<--- Large header --->", header);
    for (int i = 0; i < 10; ++i) {
        xlsx.write(row + 1 + i, 4, exp(i));
        xlsx.write(row + 1 + i, 5, exp(i));
    }
    xlsx.autosizeColumnWidth(4, 5);

    xlsx.write(1, 7, "<--- Very big first line --->", header);
    xlsx.write(row, 7, "Small", header);
    xlsx.write(row, 8, "<--- Large header --->", header);
    for (int i = 0; i < 10; ++i) {
        xlsx.write(row + 1 + i, 7, exp(i));
        xlsx.write(row + 1 + i, 8, exp(i));
    }
    xlsx.autosizeColumnWidth(QXlsx::CellRange(2, 7, 1000, 8));

    xlsx.saveAs("rowcolumn.xlsx");
    return 0;
}

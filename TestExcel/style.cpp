// style.cpp

#include "xlsxdocument.h"
#include "xlsxformat.h"

#include <QtCore>
#include <QtGlobal>

int style()
{
    QXlsx::Document xlsx;
    QXlsx::Format format1;
    format1.setFontColor(QColor(Qt::red));
    format1.setFontSize(15);
    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format1.setBorderStyle(QXlsx::Format::BorderDashDotDot);
    xlsx.write("A1", "Hello Qt!", format1);
    xlsx.write("B3", 12345, format1);

    QXlsx::Format format2;
    format2.setFontBold(true);
    format2.setFontUnderline(QXlsx::Format::FontUnderlineDouble);
    format2.setFillPattern(QXlsx::Format::PatternLightUp);
    xlsx.write("C5", "=44+33", format2);
    xlsx.write("D7", true, format2);

    QXlsx::Format format3;
    format3.setFontBold(true);
    format3.setFontColor(QColor(Qt::blue));
    format3.setFontSize(20);
    xlsx.write(11, 1, "Hello Row Style");
    xlsx.write(11, 6, "Blue Color");
    xlsx.setRowFormat(11, 41, format3);

    QXlsx::Format format4;
    format4.setFontBold(true);
    format4.setFontColor(QColor(Qt::magenta));
    for (int row = 21; row <= 40; row++)
        for (int col = 9; col < 16; col++)
            xlsx.write(row, col, row + col);
    xlsx.setColumnFormat(9, 16, format4);

    xlsx.write("A5", QDate(2013, 8, 29));

    QXlsx::Format format6;
    format6.setPatternBackgroundColor(QColor(Qt::green));
    xlsx.write("A6", "Background color: green", format6);

    xlsx.saveAs("style1.xlsx");

    return 0;
}

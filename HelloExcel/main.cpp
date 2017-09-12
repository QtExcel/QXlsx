//
// main.cpp
//

#include <QCoreApplication>
#include <QtCore>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

void WriteExcel(bool isTest);
void ReadExcel(bool isTest);

void UseSheet(bool isTest);

void RichText(bool isTest);
void CellFormat(bool isTest);

void DoChart(bool isTest);
void Align(bool isTest);

int main(int argc, char *argv[])
{
    WriteExcel(true);
    ReadExcel(true);

    UseSheet(true);

    RichText(true);
    CellFormat(true);

    DoChart(true);
    Align(true);

    return 0;
}

void WriteExcel(bool isTest)
{
    if (!isTest)
        return;

    Document xlsx;

    xlsx.write("A1", "Hello Qt! 한글");
    xlsx.write("A2", 12345);
    xlsx.write("A3", "=44+33"); // cell value is 77.
    xlsx.write("A4", true);
    xlsx.write("A5", "http://qt-project.org");
    xlsx.write("A6", QDate(2013, 12, 27));
    xlsx.write("A7", QTime(6, 30));

    if (!xlsx.saveAs("Test1.xlsx"))
        qDebug() << "[TEST1] failed to save excel file" ;
}

void ReadExcel(bool isTest)
{
    if (!isTest)
        return;

    {
        //Create a new .xlsx file.
        QXlsx::Document xlsx;

        xlsx.write("A1", "Hello Qt!");
        xlsx.write("A2", 12345);
        xlsx.write("A3", "=44+33");
        xlsx.write("A4", true);
        xlsx.write("A5", "http://qt-project.org");
        xlsx.write("A6", QDate(2013, 12, 27));
        xlsx.write("A7", QTime(6, 30));

        if (!xlsx.saveAs("Test2.xlsx"))
        {
            qDebug() << "[TEST2] failed to save excel file" ;
            return;
        }
    }

    //![0]
    QXlsx::Document xlsx("Test2.xlsx");
    //![0]

    //![1]
    qDebug() << xlsx.read("A1");
    qDebug() << xlsx.read("A2");
    qDebug() << xlsx.read("A3");
    qDebug() << xlsx.read("A4");
    qDebug() << xlsx.read("A5");
    qDebug() << xlsx.read("A6");
    qDebug() << xlsx.read("A7");

    qDebug() << "--------------------";
    //![1]

    //![2]
    for ( int row = 1 ; row < 10 ; ++row )
    {
        if ( Cell* cell = xlsx.cellAt( row, 1 ) )
        {
            QVariant var = cell->value();
            qDebug() << row << " " << var;
        }
    }
    //![2]

    /* debug output

    QVariant(QString, "Hello Qt!")
    QVariant(double, 12345)
    QVariant(QString, "=44+33")
    QVariant(bool, true)
    QVariant(QString, "http://qt-project.org")
    QVariant(QDate, QDate("2013-12-27"))
    QVariant(QTime, QTime("06:30:00.000"))
    --------------------
    1   QVariant(QString, "Hello Qt!")
    2   QVariant(double, 12345)
    3   QVariant(double, 0)
    4   QVariant(bool, true)
    5   QVariant(QString, "http://qt-project.org")
    6   QVariant(double, 41635)
    7   QVariant(double, 0.270833)

    */
}

void DoChart(bool isTest)
{
    if (!isTest)
        return;

    //![0]
    Document xlsx;
    for ( int i = 1 ; i < 10 ; ++i )
    {
        xlsx.write(i, 1, i*i);
    }
    //![0]
    /*
        1
        4
        9
        16
        25
        36
        49
        64
        81
    */

    //![1]
    xlsx.addSheet("Chart1", AbstractSheet::ST_ChartSheet);
    Chartsheet *sheet = static_cast<Chartsheet*>(xlsx.currentSheet());
    Chart *barChart = sheet->chart();
    barChart->setChartType(Chart::CT_Bar);
    barChart->addSeries(CellRange("A1:A9"), xlsx.sheet("Sheet1"));
    //![1]

    //![2]
    if (!xlsx.saveAs("Test3.xlsx"))
    {
        qDebug() << "[TEST3] failed to create excel file";
    }
    //![2]

}

void Align(bool isTest)
{
    if (!isTest)
        return;

    Document xlsx;

    //![0]
    Format format;
    format.setHorizontalAlignment(Format::AlignHCenter);
    format.setVerticalAlignment(Format::AlignVCenter);
    //![0]

    //![1]
    xlsx.write("B4", "Hello Qt!");
    xlsx.mergeCells("B4:F6", format);

    xlsx.write("B8", 1);
    xlsx.mergeCells("B8:C21", format);

    xlsx.write("E8", 2);
    xlsx.mergeCells("E8:F21", format);
    //![1]

    if (!xlsx.saveAs("Test4.xlsx"))
    {
        qDebug() << "[TEST4] failed to create excel file";
    }

}

void UseSheet(bool isTest)
{
    if (!isTest)
        return;

    {
        //![Create a xlsx file]
        Document xlsx;

        for ( int i = 1 ; i < 20 ; ++i )
        {
            for ( int j = 1 ; j < 15 ; ++j )
                xlsx.write( i, j, QString("R %1 C %2").arg(i).arg(j) );
        }
        xlsx.addSheet();

        xlsx.write(2, 2, "Hello Qt Xlsx");
        xlsx.addSheet();

        xlsx.write(3, 3, "This will be deleted...");
        xlsx.addSheet("HiddenSheet");

        xlsx.currentSheet()->setHidden(true);
        xlsx.write("A1", "This sheet is hidden.");
        xlsx.addSheet("VeryHiddenSheet");

        xlsx.sheet("VeryHiddenSheet")->setSheetState(AbstractSheet::SS_VeryHidden);
        xlsx.write("A1", "This sheet is very hidden.");

        xlsx.save();//Default name is "Book1.xlsx"
        //![Create a xlsx file]
    }

    {
        Document xlsx2("Book1.xlsx");
        //![add_copy_move_delete]

        xlsx2.renameSheet("Sheet1", "TheFirstSheet");

        xlsx2.copySheet("TheFirstSheet", "CopyOfTheFirst");

        xlsx2.selectSheet("CopyOfTheFirst");
        xlsx2.write(25, 2, "On the Copy Sheet");

        xlsx2.deleteSheet("Sheet3");

        xlsx2.moveSheet("Sheet2", 0);
        //![add_copy_move_delete]

        //![show_hidden_sheets]
        xlsx2.sheet("HiddenSheet")->setVisible(true);
        xlsx2.sheet("VeryHiddenSheet")->setVisible(true);
        //![show_hidden_sheets]

        if ( !xlsx2.saveAs("Book2.xlsx") )
        {
            return;
        }
    }
}

void RichText(bool isTest)
{
    if (!isTest)
        return;

    //![0]
    QXlsx::Document xlsx;
    //![0]

    //![1]
    QXlsx::Format blue;
    blue.setFontColor(Qt::blue);
    QXlsx::Format red;
    red.setFontColor(Qt::red);
    red.setFontSize(15);
    QXlsx::Format bold;
    bold.setFontBold(true);

    QXlsx::RichString rich;
    rich.addFragment("Hello ", blue);
    rich.addFragment("Qt ", red);
    rich.addFragment("Xlsx", bold);
    xlsx.write("B2", rich);

    xlsx.workbook()->setHtmlToRichStringEnabled(true);
    xlsx.write("B4", "<b>Hello</b> <font color=\"red\">Qt</font> <i>Xlsx</i>");

    xlsx.write("B6", "<font color=\"red\"><b><u><i>Qt Xlsx</i></u></b></font>");

    //![1]

    //![2]
    xlsx.saveAs("Test6.xlsx");
    //![2]
}

void writeHorizontalAlignCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align)
{
   Format format;
   format.setHorizontalAlignment(align);
   format.setBorderStyle(Format::BorderThin);
   xlsx.write(cell, text, format);
}

void writeVerticalAlignCell(Document &xlsx, const QString &range, const QString &text, Format::VerticalAlignment align)
{
   Format format;
   format.setVerticalAlignment(align);
   format.setBorderStyle(Format::BorderThin);
   CellRange r(range);
   xlsx.write(r.firstRow(), r.firstColumn(), text);
   xlsx.mergeCells(r, format);
}

void writeBorderStyleCell(Document &xlsx, const QString &cell, const QString &text, Format::BorderStyle bs)
{
   Format format;
   format.setBorderStyle(bs);
   xlsx.write(cell, text, format);
}

void writeSolidFillCell(Document &xlsx, const QString &cell, const QColor &color)
{
   Format format;
   format.setPatternBackgroundColor(color);
   xlsx.write(cell, QVariant(), format);
}

void writePatternFillCell(Document &xlsx, const QString &cell, Format::FillPattern pattern, const QColor &color)
{
   Format format;
   format.setPatternForegroundColor(color);
   format.setFillPattern(pattern);
   xlsx.write(cell, QVariant(), format);
}

void writeBorderAndFontColorCell(Document &xlsx, const QString &cell, const QString &text, const QColor &color)
{
   Format format;
   format.setBorderStyle(Format::BorderThin);
   format.setBorderColor(color);
   format.setFontColor(color);
   xlsx.write(cell, text, format);
}

void writeFontNameCell(Document &xlsx, const QString &cell, const QString &text)
{
    Format format;
    format.setFontName(text);
    format.setFontSize(16);
    xlsx.write(cell, text, format);
}

void writeFontSizeCell(Document &xlsx, const QString &cell, int size)
{
    Format format;
    format.setFontSize(size);
    xlsx.write(cell, "Qt Xlsx", format);
}

void writeInternalNumFormatsCell(Document &xlsx, int row, double value, int numFmt)
{
    Format format;
    format.setNumberFormatIndex(numFmt);
    xlsx.write(row, 1, value);
    xlsx.write(row, 2, QString("Builtin NumFmt %1").arg(numFmt));
    xlsx.write(row, 3, value, format);
}

void writeCustomNumFormatsCell(Document &xlsx, int row, double value, const QString &numFmt)
{
    Format format;
    format.setNumberFormat(numFmt);
    xlsx.write(row, 1, value);
    xlsx.write(row, 2, numFmt);
    xlsx.write(row, 3, value, format);
}

void CellFormat(bool isTest)
{
    if (!isTest)
        return;

    Document xlsx;

    //---------------------------------------------------------------
    //Create the first sheet (Otherwise, default "Sheet1" will be created)
    xlsx.addSheet("Aligns & Borders");
    xlsx.setColumnWidth(2, 20); //Column B // ABCDEFGHI
    xlsx.setColumnWidth(8, 12); //Column H // 123456789
    xlsx.currentWorksheet()->setGridLinesVisible(false);

    //Alignment
    writeHorizontalAlignCell(xlsx, "B3", "AlignLeft", Format::AlignLeft);
    writeHorizontalAlignCell(xlsx, "B5", "AlignHCenter", Format::AlignHCenter);
    writeHorizontalAlignCell(xlsx, "B7", "AlignRight", Format::AlignRight);
    writeVerticalAlignCell(xlsx, "D3:D7", "AlignTop", Format::AlignTop);
    writeVerticalAlignCell(xlsx, "F3:F7", "AlignVCenter", Format::AlignVCenter);
    writeVerticalAlignCell(xlsx, "H3:H7", "AlignBottom", Format::AlignBottom);

    //Border
    writeBorderStyleCell(xlsx, "B13", "BorderMedium", Format::BorderMedium);
    writeBorderStyleCell(xlsx, "B15", "BorderDashed", Format::BorderDashed);
    writeBorderStyleCell(xlsx, "B17", "BorderDotted", Format::BorderDotted);
    writeBorderStyleCell(xlsx, "B19", "BorderThick", Format::BorderThick);
    writeBorderStyleCell(xlsx, "B21", "BorderDouble", Format::BorderDouble);
    writeBorderStyleCell(xlsx, "B23", "BorderDashDot", Format::BorderDashDot);

    //Fill
    writeSolidFillCell(xlsx, "D13", Qt::red);
    writeSolidFillCell(xlsx, "D15", Qt::blue);
    writeSolidFillCell(xlsx, "D17", Qt::yellow);
    writeSolidFillCell(xlsx, "D19", Qt::magenta);
    writeSolidFillCell(xlsx, "D21", Qt::green);
    writeSolidFillCell(xlsx, "D23", Qt::gray);
    writePatternFillCell(xlsx, "F13", Format::PatternMediumGray, Qt::red);
    writePatternFillCell(xlsx, "F15", Format::PatternDarkHorizontal, Qt::blue);
    writePatternFillCell(xlsx, "F17", Format::PatternDarkVertical, Qt::yellow);
    writePatternFillCell(xlsx, "F19", Format::PatternDarkDown, Qt::magenta);
    writePatternFillCell(xlsx, "F21", Format::PatternLightVertical, Qt::green);
    writePatternFillCell(xlsx, "F23", Format::PatternLightTrellis, Qt::gray);

    writeBorderAndFontColorCell(xlsx, "H13", "Qt::red", Qt::red);
    writeBorderAndFontColorCell(xlsx, "H15", "Qt::blue", Qt::blue);
    writeBorderAndFontColorCell(xlsx, "H17", "Qt::yellow", Qt::yellow);
    writeBorderAndFontColorCell(xlsx, "H19", "Qt::magenta", Qt::magenta);
    writeBorderAndFontColorCell(xlsx, "H21", "Qt::green", Qt::green);
    writeBorderAndFontColorCell(xlsx, "H23", "Qt::gray", Qt::gray);

    //---------------------------------------------------------------
    //Create the second sheet.
    xlsx.addSheet("Fonts");

    xlsx.write("B3", "Normal");
    Format font_bold;
    font_bold.setFontBold(true);
    xlsx.write("B4", "Bold", font_bold);
    Format font_italic;
    font_italic.setFontItalic(true);
    xlsx.write("B5", "Italic", font_italic);
    Format font_underline;
    font_underline.setFontUnderline(Format::FontUnderlineSingle);
    xlsx.write("B6", "Underline", font_underline);
    Format font_strikeout;
    font_strikeout.setFontStrikeOut(true);
    xlsx.write("B7", "StrikeOut", font_strikeout);

    writeFontNameCell(xlsx, "D3", "Arial");
    writeFontNameCell(xlsx, "D4", "Arial Black");
    writeFontNameCell(xlsx, "D5", "Comic Sans MS");
    writeFontNameCell(xlsx, "D6", "Courier New");
    writeFontNameCell(xlsx, "D7", "Impact");
    writeFontNameCell(xlsx, "D8", "Times New Roman");
    writeFontNameCell(xlsx, "D9", "Verdana");

    writeFontSizeCell(xlsx, "G3", 10);
    writeFontSizeCell(xlsx, "G4", 12);
    writeFontSizeCell(xlsx, "G5", 14);
    writeFontSizeCell(xlsx, "G6", 16);
    writeFontSizeCell(xlsx, "G7", 18);
    writeFontSizeCell(xlsx, "G8", 20);
    writeFontSizeCell(xlsx, "G9", 25);

    Format font_vertical;
    font_vertical.setRotation(255);
    font_vertical.setFontSize(16);
    xlsx.write("J3", "vertical", font_vertical);
    xlsx.mergeCells("J3:J9");

    //---------------------------------------------------------------
    //Create the third sheet.
    xlsx.addSheet("Formulas");
    xlsx.setColumnWidth(1, 2, 40);
    Format rAlign;
    rAlign.setHorizontalAlignment(Format::AlignRight);
    Format lAlign;
    lAlign.setHorizontalAlignment(Format::AlignLeft);
    xlsx.write("B3", 40, lAlign);
    xlsx.write("B4", 30, lAlign);
    xlsx.write("B5", 50, lAlign);
    xlsx.write("A7", "SUM(B3:B5)=", rAlign);
    xlsx.write("B7", "=SUM(B3:B5)", lAlign);
    xlsx.write("A8", "AVERAGE(B3:B5)=", rAlign);
    xlsx.write("B8", "=AVERAGE(B3:B5)", lAlign);
    xlsx.write("A9", "MAX(B3:B5)=", rAlign);
    xlsx.write("B9", "=MAX(B3:B5)", lAlign);
    xlsx.write("A10", "MIN(B3:B5)=", rAlign);
    xlsx.write("B10", "=MIN(B3:B5)", lAlign);
    xlsx.write("A11", "COUNT(B3:B5)=", rAlign);
    xlsx.write("B11", "=COUNT(B3:B5)", lAlign);

    xlsx.write("A13", "IF(B7>100,\"large\",\"small\")=", rAlign);
    xlsx.write("B13", "=IF(B7>100,\"large\",\"small\")", lAlign);

    xlsx.write("A15", "SQRT(25)=", rAlign);
    xlsx.write("B15", "=SQRT(25)", lAlign);
    xlsx.write("A16", "RAND()=", rAlign);
    xlsx.write("B16", "=RAND()", lAlign);
    xlsx.write("A17", "2*PI()=", rAlign);
    xlsx.write("B17", "=2*PI()", lAlign);

    xlsx.write("A19", "UPPER(\"qtxlsx\")=", rAlign);
    xlsx.write("B19", "=UPPER(\"qtxlsx\")", lAlign);
    xlsx.write("A20", "LEFT(\"ubuntu\",3)=", rAlign);
    xlsx.write("B20", "=LEFT(\"ubuntu\",3)", lAlign);
    xlsx.write("A21", "LEN(\"Hello Qt!\")=", rAlign);
    xlsx.write("B21", "=LEN(\"Hello Qt!\")", lAlign);

    Format dateFormat;
    dateFormat.setHorizontalAlignment(Format::AlignLeft);
    dateFormat.setNumberFormat("yyyy-mm-dd");
    xlsx.write("A23", "DATE(2013,8,13)=", rAlign);
    xlsx.write("B23", "=DATE(2013,8,13)", dateFormat);
    xlsx.write("A24", "DAY(B23)=", rAlign);
    xlsx.write("B24", "=DAY(B23)", lAlign);
    xlsx.write("A25", "MONTH(B23)=", rAlign);
    xlsx.write("B25", "=MONTH(B23)", lAlign);
    xlsx.write("A26", "YEAR(B23)=", rAlign);
    xlsx.write("B26", "=YEAR(B23)", lAlign);
    xlsx.write("A27", "DAYS360(B23,TODAY())=", rAlign);
    xlsx.write("B27", "=DAYS360(B23,TODAY())", lAlign);

    xlsx.write("A29", "B3+100*(2-COS(0)))=", rAlign);
    xlsx.write("B29", "=B3+100*(2-COS(0))", lAlign);
    xlsx.write("A30", "ISNUMBER(B29)=", rAlign);
    xlsx.write("B30", "=ISNUMBER(B29)", lAlign);
    xlsx.write("A31", "AND(1,0)=", rAlign);
    xlsx.write("B31", "=AND(1,0)", lAlign);

    xlsx.write("A33", "HYPERLINK(\"http://qt-project.org\")=", rAlign);
    xlsx.write("B33", "=HYPERLINK(\"http://qt-project.org\")", lAlign);

    //---------------------------------------------------------------
    //Create the fourth sheet.
    xlsx.addSheet("NumFormats");
    xlsx.setColumnWidth(2, 40);
    writeInternalNumFormatsCell(xlsx, 4, 2.5681, 2);
    writeInternalNumFormatsCell(xlsx, 5, 2500000, 3);
    writeInternalNumFormatsCell(xlsx, 6, -500, 5);
    writeInternalNumFormatsCell(xlsx, 7, -0.25, 9);
    writeInternalNumFormatsCell(xlsx, 8, 890, 11);
    writeInternalNumFormatsCell(xlsx, 9, 0.75, 12);
    writeInternalNumFormatsCell(xlsx, 10, 41499, 14);
    writeInternalNumFormatsCell(xlsx, 11, 41499, 17);

    writeCustomNumFormatsCell(xlsx, 13, 20.5627, "#.###");
    writeCustomNumFormatsCell(xlsx, 14, 4.8, "#.00");
    writeCustomNumFormatsCell(xlsx, 15, 1.23, "0.00 \"RMB\"");
    writeCustomNumFormatsCell(xlsx, 16, 60, "[Red][<=100];[Green][>100]");

    //---------------------------------------------------------------
    //Create the fifth sheet.
    xlsx.addSheet("Merging");
    Format centerAlign;
    centerAlign.setHorizontalAlignment(Format::AlignHCenter);
    centerAlign.setVerticalAlignment(Format::AlignVCenter);
    xlsx.write("B4", "Hello Qt!");
    xlsx.mergeCells("B4:F6", centerAlign);
    xlsx.write("B8", 1);
    xlsx.mergeCells("B8:C21", centerAlign);
    xlsx.write("E8", 2);
    xlsx.mergeCells("E8:F21", centerAlign);

    //---------------------------------------------------------------
    //Create the fifth sheet.
    xlsx.addSheet("Grouping");
    qsrand(QDateTime::currentMSecsSinceEpoch());
    for (int row=2; row<31; ++row) {
        for (int col=1; col<=10; ++col)
            xlsx.write(row, col, qrand() % 100);
    }
    xlsx.groupRows(4, 7);
    xlsx.groupRows(11, 26, false);
    xlsx.groupRows(15, 17, false);
    xlsx.groupRows(20, 22, false);
    xlsx.setColumnWidth(1, 10, 10.0);
    xlsx.groupColumns(1, 2);
    xlsx.groupColumns(5, 8, false);

    if (!xlsx.saveAs("Test7.xlsx"))
    {
        return;
    }
}


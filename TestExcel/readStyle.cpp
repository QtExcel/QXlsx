// readStyle.cpp

#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <QtCore>
#include <QtGlobal>

QXLSX_USE_NAMESPACE

int readGoogleSpreadsheet();
int readMSExcel201x();
int readMSExcel201xNumber(QXlsx::Document *pXlsx);
int readLibreOffice();
int readWPSOffice();

int readStyle()
{
    int ret = 0;

    // ret = readGoogleSpreadsheet();

    // ret = readMSExcel201x();

    return 0;
}

int readGoogleSpreadsheet()
{
    Document xlsx("google-spreadsheet.xlsx"); // google docs

    if (!xlsx.isLoadPackage()) {
        qDebug() << "[readGoogleSpreadsheet] failed to load package";
        return (-1);
    }

    // current sheet is default sheet. (Sheet1)

    for (int row = 1; row < 20; ++row) {
        auto cell = xlsx.cellAt(row, 1);
        if (cell == NULL)
            continue;
        QVariant var   = cell->readValue();
        qint32 styleNo = cell->styleNumber();

        Format fmt = cell->format();
        QString strFormat;
        if (fmt.hasNumFmtData()) {
            QString strNumFormat = fmt.numberFormat();
            if (!strNumFormat.isEmpty())
                strFormat = strFormat + QString(" number format : ") + strNumFormat;
        }

        if (fmt.hasFontData()) {
            Format::FontScript fs = fmt.fontScript();
        }

        if (fmt.hasFillData()) {
            int fillIndex = fmt.fillIndex();
            QByteArray ba = fmt.fillKey();
        }

        if (fmt.hasBorderData()) {
        }

        if (fmt.hasAlignmentData()) {
        }

        if (fmt.hasProtectionData()) {
        }

        if (styleNo >= 0) {
            qDebug() << row << " " << var << " , style:" << styleNo << strFormat;
        } else {
            qDebug() << row << " " << var << strFormat;
        }
    }

    /* Debug Output
    1   QVariant(double, 1)  , style: 1 ""
    2   QVariant(QString, "2")  , style: 2 ""
    3   QVariant(double, 3)  , style: 3 ""
    4   QVariant(double, 4)  , style: 4 ""
    5   QVariant(double, 5)  , style: 5 ""
    6   QVariant(double, 6)  , style: 6 " number format : _([$\-412]* #,##0.00_);_([$\-412]*
    \\(#,##0.00\\);_([$\-412]* \"-\"??_);_(@_)" 7   QVariant(double, 7)  , style: 7 " number format
    : #,##0.00;(#,##0.00)" 8   QVariant(double, 8)  , style: 8 " number format : [$\-412]#,##0.00"
    9   QVariant(double, 9)  , style: 9 " number format : [$\-412]#,##0"
    10   QVariant(QString, "1900. 1. 9")  , style: 10 " number format : yyyy. M. d"
    11   QVariant(QTime, QTime("00:00:00.000"))  , style: 11 " number format : am/pm h:mm:ss"
    12   QVariant(QString, "1900. 1. 11 AM 12:00:00")  , style: 12 " number format : yyyy. M. d
    am/pm h:mm:ss" 13   QVariant(QString, "312:0:0")  , style: 13 ""
    */

    /* Testing of read google spreadsheet file (made by google docs)
     https://github.com/j2doll/QXlsx/blob/master/image/LibreOffice-Google-XLSX.png

    1   QVariant(double, 1) OK:it's auto style (1)
    2   QVariant(QString, "2") OK:it's shared string. (2) see ./xl/sharedStrings.xml
    3   QVariant(double, 3) PENDING:it's number (3.00) (TODO: use style[3] of cell)
    4   QVariant(double, 4) PENDING:it's percentage (400.00%) (TODO: use style[4] of cell)
    5   QVariant(double, 5) PENDING:it's exponentiation (5.00E+00) (TODO: use style[5] of cell)
    6   QVariant(double, 6) PENDING:it's accounting#1 ($ 6.00) (TODO: use style[6] of cell)
    7   QVariant(double, 7) PENDING:it's accounting#2 (7.00) (TODO: use style[7] of cell)
    8   QVariant(double, 8) PENDING:it's currency ($8.00) (TODO: use style[8] of cell)
    9   QVariant(double, 9) PENDING:it's currency(rounds) ($9) (TODO: use style[9] of cell)

    10   QVariant(QString, "1900. 1. 9") OK:it's shared string. see /xl/sharedStrings.xml
    11   QVariant(QDateTime, QDateTime(1900-01-11 00:00:00.000 KOREA KST Qt::TimeSpec(LocalTime)))
    PENDING:it means '1900Y.1M.11D.00H-00m-00s'. but, style[11] uses 'AM/PM HH:mm:ss' format. (TODO:
    use style[11] of cell) 12   QVariant(QString, "1900. 1. 11 AM 12:00:00") OK:it's shared string.
    see /xl/sharedStrings.xml 13   QVariant(QDateTime, QDateTime(1900-01-13 00:00:00.000 KOREA KST
    Qt::TimeSpec(LocalTime))) NOK:it's period (312H:00m:00s). [it's date. but, 13 days means 312
    hours!!]
    */

    return 0;
}

int readLibreOffice()
{
    // WAIT...
    return 0;
}

int readMSExcel201x()
{
    Document xlsx("ms-number.xlsx"); // ms office online

    if (!xlsx.isLoadPackage()) {
        qDebug() << "[ms-number] failed to load package";
        return (-1);
    }

    return readMSExcel201xNumber(&xlsx);
}

int readMSExcel201xNumber(QXlsx::Document *pXlsx)
{
    if (NULL == pXlsx)
        return (-1);

    for (int row = 1; row < 10; ++row) {
        auto cell = pXlsx->cellAt(row, 1);
        if (cell == NULL)
            continue;

        QVariant var   = cell->readValue();
        qint32 styleNo = cell->styleNumber();
        Format fmt     = cell->format();

        QString strFomrat;
        if (fmt.hasNumFmtData()) {
            QString strNumFormat = fmt.numberFormat();
            strFomrat            = strFomrat + QString(" number format :") + strNumFormat;
        }

        if (styleNo >= 0) {
            qDebug() << row << " " << var << " , style:" << styleNo << strFomrat;
        } else {
            qDebug() << row << " " << var << strFomrat;
        }
    }

    /* Debug output
    1   QVariant(double, 1) ""
    2   QVariant(double, 2)  , style: 1 " number format :0.00_ "
    3   QVariant(double, 3000)  , style: 2 " number format :#,##0_ "
    4   QVariant(double, -4)  , style: 3 " number format :0_ ;[Red]\\-0\\ "

    cell value that is printed on excel
    [1]
    [2.00]
    [3,000]
    [red minus four]
    */

    return 0;
}

int readWPSOffice()
{
    return 0;
}

// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx

// main.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>
#include <QVariant>

#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <cstdio>
#include <iostream>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

#include "XlsxTableModel.h"
#include "DynArray2D.h"

std::string convertFromNumberToExcelColumn(int n);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctxt = engine.rootContext();

    QXlsx::Document xlsx( ":/test.xlsx" ); // load xlsx
    if (!xlsx.load())
    {
        qDebug() << "[ERROR] Failed to load xlsx";
        return (-1);
    }

    QList<QString> colTitle; // list of column title
    QVector<CellLocation> vcl; // vector of cell(s) location
    Worksheet* wsheet = (Worksheet*) xlsx.workbook()->activeSheet();
    if ( NULL == wsheet )
    {
        qDebug() << "[ERROR] Failed to get active sheet";
        return (-2);
    }

    int rowMax = -1;
    int colMax = -1;
    vcl = wsheet->getFullCells( &rowMax, &colMax );

    Q_ASSERT( (-1) != rowMax ); // To CHECK
    Q_ASSERT( (-1) != colMax );

    for (int ic = 0 ; ic < colMax ; ic++)
    {
        std::string strCol = convertFromNumberToExcelColumn(ic + 1);
        QString colName = QString::fromStdString( strCol );
        colTitle.append( colName );
    }

    // make cell matrix that has (colMax x rowMax) size.

    DynArray2D< std::string > dynIntArray(colMax, rowMax);

    for ( int icl = 0; icl < vcl.size(); ++icl )
    {
          CellLocation cl = vcl.at(icl); // cell location

          // NOTICE: First cell of tableWidget is 0.
          // But first cell of Qxlsx document is 1.
          int row = cl.row - 1;
          int col = cl.col - 1;

          auto ptrCell = cl.cell; // cell pointer

          // value of cell
          QVariant var = ptrCell->value();
          QString str = var.toString();

          // set string value to (col, row)
          dynIntArray.setValue( col, row, str.toStdString() );
    }

    QList<VLIST> xlsxData;
    for (int ir = 0; ir < rowMax; ir++ )
    {
        VLIST vl;
        for (int ic = 0; ic < colMax; ic++)
        {
            std::string value = dynIntArray.getValue( ic, ir );
            vl.append( QString::fromStdString(value) );
        }
        xlsxData.append(vl);
    }

    // set model for tableview
    XlsxTableModel xlsxTableModel(colTitle, xlsxData);
    ctxt->setContextProperty( "xlsxModel", &xlsxTableModel );

    engine.load( QUrl(QStringLiteral("qrc:/main.qml")) ); // load QML
    if ( engine.rootObjects().isEmpty() )
    {
        qDebug() << "Failed to load qml";
        return (-1);
    }

    int ret = app.exec();
    return ret;
}

std::string convertFromNumberToExcelColumn(int n)
{
    // main code from https://www.geeksforgeeks.org/find-excel-column-name-given-number/
    // Function to print Excel column name for a given column number

    std::string stdString;

    char str[1000]; // To store result (Excel column name)
    int i = 0; // To store current index in str which is result

    while ( n > 0 )
    {
        // Find remainder
        int rem = n % 26;

        // If remainder is 0, then a 'Z' must be there in output
        if ( rem == 0 )
        {
            str[i++] = 'Z';
            n = (n/26) - 1;
        }
        else // If remainder is non-zero
        {
            str[i++] = (rem-1) + 'A';
            n = n / 26;
        }
    }
    str[i] = '\0';

    // Reverse the string and print result
    std::reverse( str, str + strlen(str) );

    stdString = str;
    return stdString;
}

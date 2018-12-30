// main.cpp
// QXlsx // MIT License // https://github.com/j2doll/QXlsx
//

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDir>
#include <QDebug>

#include <iostream>
using namespace std;

// [0] include QXlsx headers
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // [1]  Writing excel file(*.xlsx)
    QXlsx::Document xlsxW;
    xlsxW.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    if ( xlsxW.saveAs("Test.xlsx") ) // save the document as 'Test.xlsx'
    {
        qDebug() << "[debug] success to write xlsx file";
    }
    else
    {
        qDebug() << "[debug][error] failed to write xlsx file";
    }

    qDebug() << "[debug] current directory is " << QDir::currentPath();

    // [2] Reading excel file(*.xlsx)
    Document xlsxR("Test.xlsx"); 
    if ( xlsxR.load() ) // load excel file
    {
        qDebug() << "[debug] success to load xlsx file.";

        int row = 1; int col = 1;
        Cell* cell = xlsxR.cellAt(row, col); // get cell pointer.
        if ( cell != NULL )
        {
            QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
            qDebug() << "[debug] cell(1,1) is " << var; // Display value. It is 'Hello Qt!'.
        }
        else
        {
            qDebug() << "[debug][error] cell(1,1) is not set.";
        }
    }
    else
    {
        qDebug() << "[debug][error] failed to load xlsx file.";
    }

    return 0;
}

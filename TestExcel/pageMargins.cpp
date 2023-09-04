// pageMargins.cpp

#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <QDebug>
#include <QObject>
#include <QString>
#include <QtGlobal>

QXLSX_USE_NAMESPACE

#include <cstdio>
#include <iostream>
// using namespace std;

int pageMargin(bool isTest);

int pages()
{
    pageMargin(true);

    return 0;
}

int pageMargin(bool isTest)
{
    if (!isTest)
        return (-1);

    // TODO:
    /*
    Document xlsx;

    xlsx.write("A1", "Hello QtXlsx!"); // current file is utf-8 character-set.
    xlsx.write("A2", 12345);
    xlsx.write("A3", "=44+33"); // cell value is 77.
    xlsx.write("A4", true);
    xlsx.write("A5", "http://qt-project.org");
    xlsx.write("A6", QDate(2013, 12, 27));
    xlsx.write("A7", QTime(6, 30));


    if (!xlsx.saveAs("WriteExcel.xlsx"))
    {
        qDebug() << "[WriteExcel] failed to save excel file";
        return (-2);
    }
    */

    return 0;
}

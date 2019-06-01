// test.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVector>
#include <QVariant>
#include <QDebug> 
#include <QDir>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

int test( QVector<QVariant> params );

int testIssue38();
int testIssue39();

int test( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();

    using namespace QXlsx;

    Document output;
    // TEST CODE
    output.saveAs("test10.xlsx");

    Document output2("test10.xlsx");
    if ( output2.load() )
    {
        output2.saveAs("test20.xlsx");
        qDebug() << "[debug] xlsx is saved.";
    }

    return 0;
}


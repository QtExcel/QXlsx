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

// int test( QVector<QVariant> params );

int test( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();

    using namespace QXlsx;

    Document doc1;

    /*
    I simply added "0.####" to numberformat.xlsx:

    //Custom number formats
    QStringList numFormats;
    numFormats
    << "Qt #"
    << "yyyy-mmm-dd"
    << "$ #,##0.00"
    << "[red]0.00"
    << "0.####";
    */

    Format fmt;
    fmt.setNumberFormat( "0.####" );
    // doc1.write( 1, 1, int(30), fmt );
    doc1.write( 1, 2, double(30), fmt );

    doc1.saveAs("test10.xlsx");

    return 0;
}


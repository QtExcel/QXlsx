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
int test1( QVector<QVariant> params );
int test2( QVector<QVariant> params );

int test( QVector<QVariant> params )
{
    // return test1( params );
    return test2( params );
}

int test1( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();

    using namespace QXlsx;

    Document doc;

    doc.write( "A1", QVariant(QDateTime::currentDateTimeUtc()) );
    doc.write( "A2", QVariant(double(10.5)) );
    doc.write( "A3", QVariant(QDate(2019, 10, 9)) );
    doc.write( "A4", QVariant(QTime(10, 9, 5)) );
    doc.write( "A5", QVariant((int) 40000) );

    qDebug() << "doc.read()";
    qDebug() << doc.read( 1, 1 ).type() << doc.read( 1, 1 );
    qDebug() << doc.read( 2, 1 ).type() << doc.read( 2, 1 );
    qDebug() << doc.read( 3, 1 ).type() << doc.read( 3, 1 );
    qDebug() << doc.read( 4, 1 ).type() << doc.read( 4, 1 );
    qDebug() << doc.read( 5, 1 ).type() << doc.read( 5, 1 );
    qDebug() << "\n";

    qDebug() << "doc.cellAt()->value()";
    qDebug() << doc.cellAt( 1, 1 )->value().type() << doc.cellAt( 1, 1 )->value();
    qDebug() << doc.cellAt( 2, 1 )->value().type() << doc.cellAt( 2, 1 )->value();
    qDebug() << doc.cellAt( 3, 1 )->value().type() << doc.cellAt( 3, 1 )->value();
    qDebug() << doc.cellAt( 4, 1 )->value().type() << doc.cellAt( 4, 1 )->value();
    qDebug() << doc.cellAt( 5, 1 )->value().type() << doc.cellAt( 5, 1 )->value();

    doc.saveAs("datetime.xlsx");

    return 0;
}

int test2( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();

    using namespace QXlsx;

    qDebug() << "\n\ndoc1\n";

    Document doc;

    doc.write( "A1", QVariant(QDateTime::currentDateTimeUtc()) );
    doc.write( "A2", QVariant(double(10.5)) );
    doc.write( "A3", QVariant(QDate(2019, 10, 9)) );
    doc.write( "A4", QVariant(QTime(10, 9, 5)) );
    doc.write( "A5", QVariant((int) 40000) );

    qDebug() << "doc.read()";
    qDebug() << doc.read( 1, 1 ).type() << doc.read( 1, 1 );
    qDebug() << doc.read( 2, 1 ).type() << doc.read( 2, 1 );
    qDebug() << doc.read( 3, 1 ).type() << doc.read( 3, 1 );
    qDebug() << doc.read( 4, 1 ).type() << doc.read( 4, 1 );
    qDebug() << doc.read( 5, 1 ).type() << doc.read( 5, 1 );
    qDebug() << "\n";

    qDebug() << "doc.cellAt()->value()";
    qDebug() << doc.cellAt( 1, 1 )->value().type() << doc.cellAt( 1, 1 )->value();
    qDebug() << doc.cellAt( 2, 1 )->value().type() << doc.cellAt( 2, 1 )->value();
    qDebug() << doc.cellAt( 3, 1 )->value().type() << doc.cellAt( 3, 1 )->value();
    qDebug() << doc.cellAt( 4, 1 )->value().type() << doc.cellAt( 4, 1 )->value();
    qDebug() << doc.cellAt( 5, 1 )->value().type() << doc.cellAt( 5, 1 )->value();
    qDebug() << "\n";

    doc.saveAs("datetime.xlsx");

    qDebug() << "\n\ndoc2\n";

    Document doc2("datetime.xlsx");
    if ( !doc2.load() )
    {
        qWarning() << "failed to load datetime.xlsx" ;
        return (-1);
    }
    qDebug() << "\n\n";

    doc2.write( "A6", QVariant(QDateTime::currentDateTimeUtc()) );
    doc2.write( "A7", QVariant(double(10.5)) );
    doc2.write( "A8", QVariant(QDate(2019, 10, 9)) );
    doc2.write( "A9", QVariant(QTime(10, 9, 5)) );
    doc2.write( "A10", QVariant((int) 40000) );

    qDebug() << "doc2.read()";
    qDebug() << doc2.read( 1, 1 ).type() << doc2.read( 1, 1 );
    qDebug() << doc2.read( 2, 1 ).type() << doc2.read( 2, 1 );
    qDebug() << doc2.read( 3, 1 ).type() << doc2.read( 3, 1 );
    qDebug() << doc2.read( 4, 1 ).type() << doc2.read( 4, 1 );
    qDebug() << doc2.read( 5, 1 ).type() << doc2.read( 5, 1 );
    qDebug() << doc2.read( 6, 1 ).type() << doc2.read( 6, 1 );
    qDebug() << doc2.read( 7, 1 ).type() << doc2.read( 7, 1 );
    qDebug() << doc2.read( 8, 1 ).type() << doc2.read( 8, 1 );
    qDebug() << doc2.read( 9, 1 ).type() << doc2.read( 9, 1 );
    qDebug() << doc2.read(10, 1 ).type() << doc2.read(10, 1 );
    qDebug() << "\n";

    qDebug() << "doc2.cellAt()->value()";
    qDebug() << doc2.cellAt( 1, 1 )->value().type() << doc2.cellAt( 1, 1 )->value();
    qDebug() << doc2.cellAt( 2, 1 )->value().type() << doc2.cellAt( 2, 1 )->value();
    qDebug() << doc2.cellAt( 3, 1 )->value().type() << doc2.cellAt( 3, 1 )->value();
    qDebug() << doc2.cellAt( 4, 1 )->value().type() << doc2.cellAt( 4, 1 )->value();
    qDebug() << doc2.cellAt( 5, 1 )->value().type() << doc2.cellAt( 5, 1 )->value();
    qDebug() << doc2.cellAt( 6, 1 )->value().type() << doc2.cellAt( 6, 1 )->value();
    qDebug() << doc2.cellAt( 7, 1 )->value().type() << doc2.cellAt( 7, 1 )->value();
    qDebug() << doc2.cellAt( 8, 1 )->value().type() << doc2.cellAt( 8, 1 )->value();
    qDebug() << doc2.cellAt( 9, 1 )->value().type() << doc2.cellAt( 9, 1 )->value();
    qDebug() << doc2.cellAt(10, 1 )->value().type() << doc2.cellAt(10, 1 )->value();
    doc2.saveAs("datetime2.xlsx");

    qDebug() << "\n\ndoc3\n";

    Document doc3("datetime2.xlsx");
    if ( !doc3.load() )
    {
        qWarning() << "failed to load datetime2.xlsx" ;
        return (-1);
    }
    qDebug() << "\n\n";

    qDebug() << "doc3.read()";
    qDebug() << doc3.read( 1, 1 ).type() << doc3.read( 1, 1 );
    qDebug() << doc3.read( 2, 1 ).type() << doc3.read( 2, 1 );
    qDebug() << doc3.read( 3, 1 ).type() << doc3.read( 3, 1 );
    qDebug() << doc3.read( 4, 1 ).type() << doc3.read( 4, 1 );
    qDebug() << doc3.read( 5, 1 ).type() << doc3.read( 5, 1 );
    qDebug() << doc3.read( 6, 1 ).type() << doc3.read( 6, 1 );
    qDebug() << doc3.read( 7, 1 ).type() << doc3.read( 7, 1 );
    qDebug() << doc3.read( 8, 1 ).type() << doc3.read( 8, 1 );
    qDebug() << doc3.read( 9, 1 ).type() << doc3.read( 9, 1 );
    qDebug() << doc3.read(10, 1 ).type() << doc3.read(10, 1 );
    qDebug() << "\n";

    qDebug() << "doc3.cellAt()->value()";
    qDebug() << doc3.cellAt( 1, 1 )->value().type() << doc3.cellAt( 1, 1 )->value();
    qDebug() << doc3.cellAt( 2, 1 )->value().type() << doc3.cellAt( 2, 1 )->value();
    qDebug() << doc3.cellAt( 3, 1 )->value().type() << doc3.cellAt( 3, 1 )->value();
    qDebug() << doc3.cellAt( 4, 1 )->value().type() << doc3.cellAt( 4, 1 )->value();
    qDebug() << doc3.cellAt( 5, 1 )->value().type() << doc3.cellAt( 5, 1 )->value();
    qDebug() << doc3.cellAt( 6, 1 )->value().type() << doc3.cellAt( 6, 1 )->value();
    qDebug() << doc3.cellAt( 7, 1 )->value().type() << doc3.cellAt( 7, 1 )->value();
    qDebug() << doc3.cellAt( 8, 1 )->value().type() << doc3.cellAt( 8, 1 )->value();
    qDebug() << doc3.cellAt( 9, 1 )->value().type() << doc3.cellAt( 9, 1 )->value();
    qDebug() << doc3.cellAt(10, 1 )->value().type() << doc3.cellAt(10, 1 )->value();
    doc2.saveAs("datetime2.xlsx");

    return 0;
}


// test.cpp
// QXlsx // MIT License // https://github.com/j2doll/QXlsx

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
using namespace QXlsx;

int test( QVector<QVariant> params )
{
    qDebug() << " current path : " << QDir::currentPath();

    Document doc( "test.xlsx" );
    if ( ! doc.load() )
    {
        qDebug() << "Failed to load 'test.xlsx'";
        return (-1);
    }
    qDebug() << "load 'test2.xlsx'";

    if ( ! doc.saveAs( "test2.xlsx" ) )
    {
        qDebug() << "Failed to save 'test2.xlsx'";
        return (-2);
    }
    qDebug() << "save 'test2.xlsx'";

    return 0;
}


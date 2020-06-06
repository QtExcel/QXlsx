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

int test91( QVector<QVariant> params );

int test( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();
    return test91( params );
}

int test91( QVector<QVariant> params )
{
    using namespace QXlsx;

    Document doc(":/91.xlsx"); // made by ms excel 2019
    if (!doc.isLoadPackage()) {
        qDebug() << "Failed to load xlsx.";
        return (-1);
    }

    auto tmpCell = doc.cellAt(2, 2);
    if(tmpCell)
    {
        QString str = tmpCell->value().toString();
        qDebug() << str;
    }

    return 0;
}


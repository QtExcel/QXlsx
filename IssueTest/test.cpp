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

// tested in Qt 5.14.1, MingW 7.3.0 64bit
int test91( QVector<QVariant> params )
{
    using namespace QXlsx;

    Document doc(":/91.xlsx"); // made by ms excel 2019
    if (!doc.isLoadPackage()) {
        qDebug() << "Failed to load xlsx.";
        return (-1);
    }

    QXlsx::CellRange range = doc.dimension();
    for (int i = 2; i < range.rowCount() + 1; i++)
    {
         for (int j = 1; j < range.columnCount()+1; j++)
         {
              QString dataStr;
              auto tmpCell = doc.cellAt(i, j);
              if(tmpCell)
              {
                  dataStr = tmpCell->value().toString().trimmed();
                  qDebug() << dataStr;
              }
         }
    }

    return 0;
}


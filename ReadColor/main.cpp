// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDir>
#include <QColor>
#include <QDebug>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

void printColor(Cell* cell);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Document xlsxR(":/color.xlsx");
    if ( !xlsxR.load() )
    {
        return (-1);
    }

    printColor( xlsxR.cellAt(1, 1) );
    printColor( xlsxR.cellAt(1, 2) );
    printColor( xlsxR.cellAt(2, 1) );
    printColor( xlsxR.cellAt(2, 2) );

    return 0;
}

void printColor(Cell* cell)
{
    if ( NULL == cell )
        return;

     QColor clrForeGround = cell->format().patternForegroundColor();
     QColor clrBackGround = cell->format().patternBackgroundColor();

     if ( clrForeGround.isValid() &&
          clrBackGround.isValid() )
     {
           qDebug() << "[debug] color : " << clrForeGround << clrBackGround;
     }


}

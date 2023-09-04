// main.cpp

#include <iostream>

#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QVariant>
#include <QtCore>
#include <QtGlobal>
using namespace std;

#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

void printColor(Cell *cell);
void saveColor(Cell *cell);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Document xlsxR(":/color.xlsx");
    if (!xlsxR.load()) {
        return (-1);
    }

    printColor(xlsxR.cellAt(1, 1));
    printColor(xlsxR.cellAt(1, 2));
    printColor(xlsxR.cellAt(2, 1));
    printColor(xlsxR.cellAt(2, 2));

    xlsxR.write(3, 3, QVariant("HELLO"));
    saveColor(xlsxR.cellAt(3, 3));

    xlsxR.saveAs("color2.xlsx");

    return 0;
}

void printColor(Cell *cell)
{
    if (NULL == cell)
        return;

    QColor clrForeGround = cell->format().patternForegroundColor();
    QColor clrBackGround = cell->format().patternBackgroundColor();

    if (clrForeGround.isValid() && clrBackGround.isValid()) {
        qDebug() << "[debug] color : " << clrForeGround << clrBackGround;
    }
}

void saveColor(Cell *cell)
{

    cell->format().setVerticalAlignment(QXlsx::Format::AlignVCenter);
    cell->format().setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    cell->format().setFont(QFont("Calibri"));
    // fmt->setTextWarp(false);
    cell->format().setPatternBackgroundColor(Qt::blue);
    cell->format().setPatternForegroundColor(Qt::white);
}

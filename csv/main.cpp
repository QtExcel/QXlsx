// main.cpp

#include <iostream>
// using namespace std;

#include <QCoreApplication>
#include <QDebug>
#include <QVariant>
#include <QVector>
#include <QtCore>
#include <QtGlobal>

#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    {
        using namespace QXlsx;

        QString xlsxFileName = ":/test.xlsx";
        QXlsx::Document xlsxDoc(xlsxFileName);
        if (!xlsxDoc.isLoadPackage()) {
            return 0; // failed to load
        }

        QString csvFileName = "hello.csv";
        if ( xlsxDoc.saveAsCsv(csvFileName) ){
            qDebug() << "save as csv file";
        }

    }

     	
    return 0;
}

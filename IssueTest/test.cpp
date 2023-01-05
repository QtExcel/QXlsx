// test.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVector>
#include <QVariant>
#include <QDebug> 
#include <QDir>
#include <QColor>
#include <QImage>
#include <QRgb>
#include <QRandomGenerator>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

int test162( QVector<QVariant> params )
{
    using namespace QXlsx;

    Document xlsx;

    xlsx.saveAs("image1.xlsx");

    Document xlsx2("image1.xlsx");
    qDebug() << "xlsx2" ;
    qDebug() << " image count : " << xlsx.getImageCount();
    xlsx2.saveAs("image2.xlsx");

    return 0;
}

int test( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();
    // return test162( params );



    return 0;
}




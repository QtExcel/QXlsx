// test.cpp

#include <iostream>

#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QImage>
#include <QRandomGenerator>
#include <QRgb>
#include <QVariant>
#include <QVector>
#include <QtCore>
#include <QtGlobal>
using namespace std;

#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

int test162(QVector<QVariant> params)
{
    using namespace QXlsx;

    Document xlsx;

    xlsx.saveAs("image1.xlsx");

    Document xlsx2("image1.xlsx");
    qDebug() << "xlsx2";
    qDebug() << " image count : " << xlsx.getImageCount();
    xlsx2.saveAs("image2.xlsx");

    return 0;
}

int test(QVector<QVariant> params)
{
    qDebug() << "[debug] current path : " << QDir::currentPath();
    // return test162( params );

    return 0;
}

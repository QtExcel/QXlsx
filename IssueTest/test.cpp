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

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

int test95( QVector<QVariant> params );

int test( QVector<QVariant> params )
{
    qDebug() << "[debug] current path : " << QDir::currentPath();
    return test95( params );
}

int test95( QVector<QVariant> params )
{
    using namespace QXlsx;

    Document xlsx;

    for (int i=0; i<10; ++i)
    {
        QImage image(40, 30, QImage::Format_RGB32);
        image.fill( uint(qrand() % 16581375) );

        int index = xlsx.insertImage( 10*i, 5, image );

       QImage img;
       if ( xlsx.getImage( index, img ) )
       {
           QString filename;
           filename = QString("image %1.png").arg( index );
           img.save( filename );

            qDebug() << " [image index] " << index;
       }
    }
    xlsx.saveAs("image1.xlsx");

    QXlsx::Document xlsx2("image1.xlsx");
    xlsx2.saveAs("image2.xlsx");

    return 0;
}


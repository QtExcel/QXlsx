// image.cpp

#include <QtGlobal>
#include <QtCore>
#include <QDebug>
#include <QtGui>

#include "xlsxdocument.h"

int image()
{
    QXlsx::Document xlsx;
    QImage image(40, 30, QImage::Format_RGB32);
    image.fill(Qt::green);
    for (int i=0; i<10; ++i)
        xlsx.insertImage(10*i, 5, image);
    xlsx.saveAs("image1.xlsx");

    QXlsx::Document xlsx2("image1.xlsx");
    xlsx2.saveAs("image2.xlsx");

    return 0;
}

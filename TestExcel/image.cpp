// image.cpp

#include <QColor>
#include <QDebug>
#include <QDir>
#include <QImage>
#include <QRgb>
#include <QVariant>
#include <QVector>
#include <QtCore>
#include <QtGlobal>
#include <QtGui>

#if QT_VERSION >= 0x060000 // Qt 6.0 or over
#    include <QRandomGenerator>
#endif

#include "xlsxdocument.h"

int image()
{
    using namespace QXlsx;

    Document xlsx;

    for (int i = 0; i < 10; ++i) {
        QImage image(40, 30, QImage::Format_RGB32);

#if QT_VERSION >= 0x060000 // Qt 6.0 or over
        QRandomGenerator rgen;
        image.fill(uint(rgen.generate() % 16581375));
#else
        image.fill(uint(qrand() % 16581375));
#endif
        int index = xlsx.insertImage(10 * i, 5, image);

        QImage img;
        if (xlsx.getImage(index, img)) {
            QString filename;
            filename = QString("image %1.png").arg(index);
            img.save(filename);

            qDebug() << " [image index] " << index;
        }
    }
    xlsx.saveAs("image1.xlsx");

    QXlsx::Document xlsx2("image1.xlsx");
    xlsx2.saveAs("image2.xlsx");

    return 0;
}

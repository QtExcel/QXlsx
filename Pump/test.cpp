// test.cpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <QByteArray>
#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
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

#ifdef Q_OS_WIN
// #include "colorprintf.h" // https://github.com/VittGam/colorprintf
#endif

int test(QVector<QVariant> params);

int test(QVector<QVariant> params)
{
    qDebug() << "[debug] current path : " << QDir::currentPath();

    QFile fileNames(":/xlsx_files/dir2.txt");
    if (!fileNames.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "[debug] failed to load dir2.txt";
        return (-1);
    }

    while (!fileNames.atEnd()) {
        QByteArray line = fileNames.readLine();

        QString strArg(line);
        QString strArg2 = strArg.simplified();
        QString strArg3 = strArg2.trimmed();

        QString currentFilename = QString(":/xlsx_files/%1").arg(strArg3);

        {
            using namespace QXlsx;
            Document output2(currentFilename);
            if (output2.load()) {
                if (output2.saveAs(strArg3)) {
                    qDebug() << "[debug] xlsx is saved. " << strArg3;
                } else {
                    qCritical() << "[debug] failed to save. " << strArg3;
                }
            } else {
                qCritical() << "[debug] failed to load. " << strArg3;
            }
        }
    }

    return 0;
}

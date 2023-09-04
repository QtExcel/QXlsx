// main.cpp

#include <iostream>

#include <QCoreApplication>
#include <QDebug>
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
using namespace QXlsx;

extern int test(QVector<QVariant> params);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QVector<QVariant> testParams;
    int ret = test(testParams);
    // qDebug() << "test return value : " << ret;

    return 0;
}

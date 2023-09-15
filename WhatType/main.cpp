// main.cpp

#include <iostream>

#include <QCoreApplication>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QTime>
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

int whatType(QVariant var);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QXlsx::Document xlsxW;

    xlsxW.write(1, 1, QString("Hello Qt!"));
    xlsxW.write(2, 1, double(10.5));
    xlsxW.write(3, 1, (int) 10);
    xlsxW.write(4, 1, QDateTime::currentDateTimeUtc());
    xlsxW.write(5, 1, QDate(2019, 10, 5));
    xlsxW.write(6, 1, QTime(4, 13, 36));

    if (xlsxW.saveAs("Test.xlsx")) // save the document as 'Test.xlsx'
    {
        qDebug() << "[debug] success to write xlsx file";
    } else {
        qDebug() << "[debug][error] failed to write xlsx file";
    }

    qDebug() << "[debug] current directory is " << QDir::currentPath();

    Document xlsxR("Test.xlsx");
    if (!xlsxR.load()) {
        qDebug() << "[debug][error] failed to load xlsx file.";
    }

    whatType(xlsxR.cellAt(1, 1)->readValue());
    whatType(xlsxR.cellAt(2, 1)->readValue());
    whatType(xlsxR.cellAt(3, 1)->readValue());
    whatType(xlsxR.cellAt(4, 1)->readValue());
    whatType(xlsxR.cellAt(5, 1)->readValue());
    whatType(xlsxR.cellAt(6, 1)->readValue());

    return 0;
}

int whatType(QVariant var)
{
    if (var.type() == QVariant::Invalid) {
        qDebug() << "Invalid";
    }
    if (var.type() == QVariant::String) {
        qDebug() << "String";
    }
    if (var.type() == QVariant::Double) {
        qDebug() << "Double";
    }
    if (var.type() == QVariant::Int) {
        qDebug() << "Int";
    }
    if (var.type() == QVariant::DateTime) {
        qDebug() << "DateTime";
    }
    if (var.type() == QVariant::Date) {
        qDebug() << "Date";
    }
    if (var.type() == QVariant::Time) {
        qDebug() << "Time";
    }

    return 0;
}

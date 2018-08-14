// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx

// main.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>
#include <QVariant>

#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <cstdio>
#include <iostream>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

#include "XlsxTableModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctxt = engine.rootContext();

    QXlsx::Document xlsx( ":/test.xlsx" ); // load xlsx
    if (!xlsx.isLoadPackage())
    {
        qDebug() << "[ERROR] Failed to load xlsx";
        return (-1);
    }

    // A1 B1
    //    B2 C2
    // A3 B3 C3

    QList<QString> colTitle;

    colTitle.append(QString("A"));
    colTitle.append(QString("B"));
    colTitle.append(QString("C"));

    QList<VLIST> xlsxData;

    VLIST vl1;
    vl1.append( xlsx.read("A1") );
    vl1.append( xlsx.read("B1") );
    vl1.append( xlsx.read("C1") );
    xlsxData.append( vl1 );

    VLIST vl2;
    vl2.append( xlsx.read("A2") );
    vl2.append( xlsx.read("B2") );
    vl2.append( xlsx.read("C2") );
    xlsxData.append( vl2 );

    VLIST vl3;
    vl3.append( xlsx.read("A3") );
    vl3.append( xlsx.read("B3") );
    vl3.append( xlsx.read("C3") );
    xlsxData.append( vl3 );

    XlsxTableModel xlsxTableModel(colTitle, xlsxData);
    ctxt->setContextProperty( "xlsxModel", &xlsxTableModel ); // set model for tableview

    engine.load( QUrl(QStringLiteral("qrc:/main.qml")) ); // load QML
    if ( engine.rootObjects().isEmpty() )
    {
        qDebug() << "Failed to load qml";
        return (-1);
    }

    int ret = app.exec();
    return ret;
}

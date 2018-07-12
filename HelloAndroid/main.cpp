// main.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QUrl>

#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

#include "XlsxModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    XlsxModel xlsxModel;
    QQmlContext* ctxt = engine.rootContext();
    ctxt->setContextProperty( "xlsxModel", &xlsxModel ); // set model for tableview

    // TODO:
    //  1) read xlsx from qrc(*.xlsx)
    //  2) set xlsx data to xlsxModel

    engine.load( QUrl(QStringLiteral("qrc:/main.qml")) );
    if ( engine.rootObjects().isEmpty() )
    {
        qDebug() << "Failed to load qml";
        return (-1);
    }

    int ret = app.exec();

    return ret;
}

// main.cpp

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return (-1);

    // TODO:
    //  1) create qxlsx object
    //  2) load qxlsx object from xlsx file
    //  3) bind qxlsx object to qml

    return app.exec();
}

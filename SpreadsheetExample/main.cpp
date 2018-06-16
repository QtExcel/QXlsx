// (c) The Qt Company Ltd. BSD License
// Some code is fixed by j2doll.


#include "spreadsheet.h"

#include <QApplication>
#include <QLayout>

QApplication* g_app = NULL;

int main(int argc, char** argv) {

    Q_INIT_RESOURCE(spreadsheet);

    QApplication app(argc, argv);
    g_app = &app;

    SpreadSheet sheet(10, 6);

    sheet.setWindowIcon(QPixmap(":/images/interview.png"));
    sheet.show();
    sheet.layout()->setSizeConstraint(QLayout::SetFixedSize);

    return app.exec();
}



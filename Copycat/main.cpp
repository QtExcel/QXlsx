// main.cpp

#include <QtGlobal>

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow w;
    w.show();

    int ret = a.exec();
    return ret;
}

//
// main.cpp
//

#include <QCoreApplication>
#include <QtCore>

#include "xlsxdocument.h"

QTXLSX_USE_NAMESPACE

int main(int argc, char *argv[])
{
    Document xlsx;
    xlsx.write("A1", "Hello Qt!");
    xlsx.saveAs("Test.xlsx");
    return 0;
}

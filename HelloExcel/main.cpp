//
// main.cpp
//

#include <QCoreApplication>
#include <QtCore>

#include "xlsxdocument.h"

int main(int argc, char *argv[])
{
    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!");
    xlsx.saveAs("Test.xlsx");
    return 0;
}

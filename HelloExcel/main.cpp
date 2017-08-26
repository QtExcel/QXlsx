//
// main.cpp
//

#include <QCoreApplication>
#include <QtCore>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
using namespace QXlsx;

void Test1();

int main(int argc, char *argv[])
{
    Test1();
    return 0;
}

void Test1()
{
    Document xlsx;

    xlsx.write("A1", "Hello Qt!");
    xlsx.write("A2", 12345);
    xlsx.write("A3", "=44+33");
    xlsx.write("A4", true);
    xlsx.write("A5", "http://qt-project.org");
    xlsx.write("A6", QDate(2013, 12, 27));
    xlsx.write("A7", QTime(6, 30));

    if (!xlsx.saveAs("Test.xlsx"))
        cout << "failed to save excel file" << endl;
}



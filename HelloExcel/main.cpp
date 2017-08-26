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
void Test2();

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    return 0;
}

void Test1()
{
    Document xlsx;

    xlsx.write("A1", "Hello Qt!");
    xlsx.write("A2", 12345);
    xlsx.write("A3", "=44+33"); // cell value is 77.
    xlsx.write("A4", true);
    xlsx.write("A5", "http://qt-project.org");
    xlsx.write("A6", QDate(2013, 12, 27));
    xlsx.write("A7", QTime(6, 30));

    if (!xlsx.saveAs("Test1.xlsx"))
        qDebug() << "[TEST1] failed to save excel file" ;
}

void Test2()
{
    {
        //Create a new .xlsx file.
        QXlsx::Document xlsx;

        xlsx.write("A1", "Hello Qt!");
        xlsx.write("A2", 12345);
        xlsx.write("A3", "=44+33");
        xlsx.write("A4", true);
        xlsx.write("A5", "http://qt-project.org");
        xlsx.write("A6", QDate(2013, 12, 27));
        xlsx.write("A7", QTime(6, 30));

        if (!xlsx.saveAs("Test2.xlsx"))
        {
            qDebug() << "[TEST2] failed to save excel file" ;
            return;
        }
    }

    //![0]
    QXlsx::Document xlsx("Test2.xlsx");
    //![0]

    //![1]
    qDebug() << xlsx.read("A1");
    qDebug() << xlsx.read("A2");
    qDebug() << xlsx.read("A3");
    qDebug() << xlsx.read("A4");
    qDebug() << xlsx.read("A5");
    qDebug() << xlsx.read("A6");
    qDebug() << xlsx.read("A7");

    qDebug() << "--------------------";
    //![1]

    //![2]
    for ( int row = 1 ; row < 10 ; ++row )
    {
        if ( QXlsx::Cell *cell = xlsx.cellAt( row, 1 ) )
        {
            qDebug() << row << " " << cell->value() ;
        }
    }
    //![2]

    /* debug output

    QVariant(QString, "Hello Qt!")
    QVariant(double, 12345)
    QVariant(QString, "=44+33")
    QVariant(bool, true)
    QVariant(QString, "http://qt-project.org")
    QVariant(QDate, QDate("2013-12-27"))
    QVariant(QTime, QTime("06:30:00.000"))
    --------------------
    1   QVariant(QString, "Hello Qt!")
    2   QVariant(double, 12345)
    3   QVariant(double, 0)
    4   QVariant(bool, true)
    5   QVariant(QString, "http://qt-project.org")
    6   QVariant(double, 41635)
    7   QVariant(double, 0.270833)

    */
}


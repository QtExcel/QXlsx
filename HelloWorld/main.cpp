// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx
//
// QtXlsx
// https://github.com/dbzhang800/QtXlsxWriter
// http://qtxlsx.debao.me/
// MIT License

//
// main.cpp
//

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDebug>

#include <iostream>
using namespace std;

// [0] include QXlsx headers 
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	// [1]  Writing excel file(*.xlsx)
    QXlsx::Document xlsxW;
    xlsxW.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsxW.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'

	// [2] Reading excel file(*.xlsx)
    Document xlsxR("Test.xlsx"); // load excel file
    if (xlsxR.isLoadPackage())
	{ 
		int row = 1; int col = 1;
        Cell* cell = xlsxR.cellAt(row, col); // get cell pointer.
        if ( cell != NULL )
        {
            QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
            qDebug() << var; // display value
        }
	}
 
	return 0;
}

// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QDebug>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

QXLSX_USE_NAMESPACE

extern int hello();
extern int calendar();
extern int chart();
extern int chartExtended();
extern int chartsheet();
extern int datavalidation();
extern int definename();
extern int demo();
extern int documentproperty();
extern int extractdata();
extern int formula();
extern int hyperlink();
extern int image();
extern int mergecells();
extern int numberformat();
extern int richtext();
extern int rowcolumn();
extern int style();
extern int worksheetoperations();
extern int readStyle(); 
extern int pages();

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	if ( argc == 2 )
	{
		QString strArg1 = argv[1];
		if ( strArg1 == QString("hello") )
		{
			hello();
			return 0;
		}
	}

	hello();
	readStyle();
	calendar();
    chart();
    chartExtended();
    chartsheet();
	datavalidation();
	definename();
	demo();
	documentproperty();
	extractdata();
	formula();
	hyperlink();
	image();
	mergecells();
	numberformat();
	richtext();
	rowcolumn();
	style();
	worksheetoperations();
    pages();
	
    qDebug() << "**** end of main() ****";

	return 0;
}

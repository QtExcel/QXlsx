// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVector>
#include <QVariant>
#include <QDebug> 

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

extern int test(QVector<QVariant> params);

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QVector<QVariant> testParams;
	int ret = test(testParams);

	return 0; 
}


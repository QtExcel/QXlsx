//--------------------------------------------------------------------
//
// QXlsx https://github.com/j2doll/QXlsx
//
// GPL License v3 https://www.gnu.org/licenses/gpl-3.0.en.html
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//--------------------------------------------------------------------

//
// main.cpp
//

#include <QCoreApplication>
#include <QtCore>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

extern int hello();
extern int calendar();
extern int chart();
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

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	hello();
	return 0; 

	calendar();
	chart();
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
	
	return 0;
}

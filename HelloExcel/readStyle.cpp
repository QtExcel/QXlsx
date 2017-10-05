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

// readStyle.cpp

#include <QtCore>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx; 

int readGoogleStyle();

int readStyle()
{
	readGoogleStyle(); 
	return 0; 
}

int readGoogleStyle()
{
	Document xlsx("google-spreadsheet.xlsx");

	for (int row = 1; row < 15; ++row)
	{
		if (Cell* cell = xlsx.cellAt(row, 1))
		{
			if (cell == NULL)
				continue;
			QVariant var = cell->readValue();
			qDebug() << row << " " << var;
		}
	}

	/* read google spreadsheet file (made by google docs) 
	1   QVariant(double, 1) :it's auto style 
	2   QVariant(QString, "2") :it's general text style 
	3   QVariant(double, 3) :it's number
	4   QVariant(double, 4) :it's percentage
	5   QVariant(double, 5) :it's exponentiation 
	6   QVariant(double, 6) :it's accounting#1
	7   QVariant(double, 7) :it's accounting#2
	8   QVariant(double, 8) :it's currency
	9   QVariant(double, 9) :it's currency(rounds)
	10   QVariant(QString, "1900. 1. 9") :it's date :something wrong!
	11   QVariant(QDate, QDate("1900-01-11")) :it's time
	12   QVariant(QString, "1900. 1. 11 AM 12:00:00") :it's date time :something wrong!
	13   QVariant(QDate, QDate("1900-01-13")) :it's period
	*/
	  
	return 0; 
}
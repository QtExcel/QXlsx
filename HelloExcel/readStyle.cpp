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

#include <QtGlobal>
#include <QtCore>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx; 

int readGoogleSpreadsheet();
int readLibreOffice();
int readMSExcel201x();

int readStyle()
{
	int ret = readGoogleSpreadsheet();

	return 0; 
}

int readGoogleSpreadsheet()
{
	Document xlsx("google-spreadsheet.xlsx"); // google docs 

	if (!xlsx.isLoadPackage())
	{
		qDebug() << "[readGoogleSpreadsheet] failed to load package"; 
		return (-1); 
	}

	for (int row = 1; row < 20; ++row)
	{
		Cell* cell = xlsx.cellAt(row, 1);
 		if ( cell == NULL )
			continue;
		QVariant var = cell->readValue();
		qint32 styleNo = cell->styleNumber();
		if ( styleNo >= 0 )
		{
			qDebug() << row << " " << var << " , style:" << styleNo;
		}
		else
		{
			qDebug() << row << " " << var;
		}
 	}

	/* Deug output 
	1   QVariant(double, 1)  , style: 1
	2   QVariant(QString, "2")  , style: 2
	3   QVariant(double, 3)  , style: 3
	4   QVariant(double, 4)  , style: 4
	5   QVariant(double, 5)  , style: 5
	6   QVariant(double, 6)  , style: 6
	7   QVariant(double, 7)  , style: 7
	8   QVariant(double, 8)  , style: 8
	9   QVariant(double, 9)  , style: 9
	10   QVariant(QString, "1900. 1. 9")  , style: 10
	11   QVariant(QTime, QTime("00:00:00.000"))  , style: 11
	12   QVariant(QString, "1900. 1. 11 AM 12:00:00")  , style: 12
	13   QVariant(QString, "312:0:0")  , style: 13
	*/

	/* Testing fo read google spreadsheet file (made by google docs) 
  	 https://github.com/j2doll/QXlsx/blob/master/image/LibreOffice-Google-XLSX.png

	1   QVariant(double, 1) OK:it's auto style (1)
	2   QVariant(QString, "2") OK:it's shared string. (2) see ./xl/sharedStrings.xml 
	3   QVariant(double, 3) PENDING:it's number (3.00) 
	4   QVariant(double, 4) PENDING:it's percentage (400.00%) (TODO: use style[4] of cell)
	5   QVariant(double, 5) PENDING:it's exponentiation (5.00E+00) (TODO: use style[5] of cell)
	6   QVariant(double, 6) PENDING:it's accounting#1 ($ 6.00) (TODO: use style[6] of cell)
	7   QVariant(double, 7) PENDING:it's accounting#2 (7.00) (TODO: use style[7] of cell)
	8   QVariant(double, 8) PENDING:it's currency ($8.00) (TODO: use style[8] of cell)
	9   QVariant(double, 9) PENDING:it's currency(rounds) ($9) (TODO: use style[9] of cell)

	10   QVariant(QString, "1900. 1. 9") OK:it's shared string. see /xl/sharedStrings.xml
	11   QVariant(QDateTime, QDateTime(1900-01-11 00:00:00.000 KOREA KST Qt::TimeSpec(LocalTime))) PENDING:it means '1900Y.1M.11D.00H-00m-00s'. but, style[11] uses 'AM/PM HH:mm:ss' format. (TODO: use style[11] of cell)
	12   QVariant(QString, "1900. 1. 11 AM 12:00:00") OK:it's shared string. see /xl/sharedStrings.xml
	13   QVariant(QDateTime, QDateTime(1900-01-13 00:00:00.000 KOREA KST Qt::TimeSpec(LocalTime))) NOK:it's period (312H:00m:00s). [it's date. but, 13 days means 312 hours!!]
	*/

	return 0; 
}

int readLibreOffice()
{
	// WAIT...
	return 0; 
}

int readMSExcel201x()
{
	// Document xlsx("date-time.xlsx"); // ms office online

	return 0;
}


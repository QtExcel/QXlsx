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

#include "xlsxcell.h"
#include "xlsxcell_p.h"
#include "xlsxformat.h"
#include "xlsxformat_p.h"
#include "xlsxutility_p.h"
#include "xlsxworksheet.h"
#include "xlsxworkbook.h"
#include <cmath>
#include <QDateTime>
#include <QDate>
#include <QTime>

QT_BEGIN_NAMESPACE_XLSX

CellPrivate::CellPrivate(Cell *p) :
	q_ptr(p)
{

}

CellPrivate::CellPrivate(const CellPrivate * const cp)
	: value(cp->value), formula(cp->formula), cellType(cp->cellType)
	, format(cp->format), richString(cp->richString), parent(cp->parent),
	styleNumber(cp->styleNumber)
{

}

/*!
  \class Cell
  \inmodule QtXlsx
  \brief The Cell class provides a API that is used to handle the worksheet cell.

*/

/*!
  \enum Cell::CellType
  \value BooleanType      Boolean type
  \value NumberType       Number type, can be blank or used with forumula
  \value ErrorType        Error type
  \value SharedStringType Shared string type
  \value StringType       String type, can be used with forumula
  \value InlineStringType Inline string type
  */

/*!
 * \internal
 * Created by Worksheet only.
 */
// qint32 styleIndex = (-1)
Cell::Cell(const QVariant &data, 
	CellType type, 
	const Format &format, 
	Worksheet *parent,
	qint32 styleIndex ) :
	d_ptr(new CellPrivate(this))
{
	d_ptr->value = data;
	d_ptr->cellType = type;
	d_ptr->format = format;
	d_ptr->parent = parent;
	d_ptr->styleNumber = styleIndex; 
}

/*!
 * \internal
 */
Cell::Cell(const Cell * const cell):
	d_ptr(new CellPrivate(cell->d_ptr))
{
	d_ptr->q_ptr = this;
}

/*!
 * Destroys the Cell and cleans up.
 */
Cell::~Cell()
{
	delete d_ptr;
}

/*!
 * Return the dataType of this Cell
 */
Cell::CellType Cell::cellType() const
{
	Q_D(const Cell);
	return d->cellType;
}

/*!
 * Return the data content of this Cell
 */
QVariant Cell::value() const
{
	Q_D(const Cell); 
	return d->value; 
}

/*!
* Return the data content of this Cell for reading 
*/
QVariant Cell::readValue() const
{
	Q_D(const Cell);

	QVariant ret; // return value 
	ret = d->value;

	if (isDateTime())
	{
		QDateTime dt = dateTime(); 
		ret = dt;

		qint32 styleNo = d->styleNumber;

		if (styleNo == 10)
		{
			// TODO: change string to time (1900. 1. 9)
		}

		if (styleNo == 11) // only time. (HH:mm:ss) 
		{
			QTime timeValue = dt.time();
			ret = timeValue;
			return ret;
		}

		if (styleNo == 12) 
		{
			// TODO: change string to time (1900. 1. 11 AM 12:00:00)
		}

		if (styleNo == 13) // (HH:mm:ss) 
		{
 			double dValue = d->value.toDouble(); 
			int day = int(dValue); // unit is day. 
			double deciamlPointValue1 = dValue - double(day);

			double dHour = deciamlPointValue1 * (double(1.0) / double(24.0));
			int hour = int(dHour);

			double deciamlPointValue2 = deciamlPointValue1 - (double(hour) * (double(1.0) / double(24.0)));
			double dMin = deciamlPointValue2 * (double(1.0) / double(60.0));
			int min = int(dMin);

			double deciamlPointValue3 = deciamlPointValue2 - (double(min) * (double(1.0) / double(60.0)));
			double dSec = deciamlPointValue3 * (double(1.0) / double(60.0));
			int sec = int(dSec);
	
			int totalHour = hour + (day * 24);

			QString strTime;
			strTime = QString("%1:%2:%3").arg(totalHour).arg(min).arg(sec);
			ret = strTime;

			return ret;
		}

		return ret; 
 	}

	if (hasFormula())
	{
		// QVariant::Type vt = ret.type(); // it's double type.  
		QString formulaString = this->formula().formulaText();
		ret = formulaString;
		return ret; // return formula string 
	}

	return ret;
}

/*!
 * Return the style used by this Cell. If no style used, 0 will be returned.
 */
Format Cell::format() const
{
	Q_D(const Cell);
	return d->format;
}

/*!
 * Returns true if the cell has one formula.
 */
bool Cell::hasFormula() const
{
	Q_D(const Cell);
	return d->formula.isValid();
}

/*!
 * Return the formula contents if the dataType is Formula
 */
CellFormula Cell::formula() const
{
	Q_D(const Cell);
	return d->formula;
}

/*!
 * Returns whether the value is probably a dateTime or not
 */
bool Cell::isDateTime() const
{
	Q_D(const Cell);

	Cell::CellType cellType = d->cellType;
	double dValue = d->value.toDouble();
	QString strValue = d->value.toString().toUtf8(); 
	bool isValidFormat = d->format.isValid();
	bool isDateTimeFormat = d->format.isDateTimeFormat();

	// NOTICE: google spreadsheet data is not adoptable.
	//  cell style(10): cellType is SharedStringType. strValue is '1900. 1. 9'.
	//  cell style(12): cellType is SharedStringType. strValue is '1900. 1. 11 AM 12:00:00'.

	if ( cellType == NumberType && 
		 dValue >= 0 &&
		 isValidFormat &&
		 isDateTimeFormat )
	{
		return true;
	}

	return false;
}

/*!
 * Return the data time value.
 */
QDateTime Cell::dateTime() const
{
	Q_D(const Cell);
	if (!isDateTime())
		return QDateTime();
	return datetimeFromNumber(d->value.toDouble(), d->parent->workbook()->isDate1904());
}

/*!
 * Returns whether the cell is probably a rich string or not
 */
bool Cell::isRichString() const
{
	Q_D(const Cell);

	if (d->cellType != SharedStringType && d->cellType != InlineStringType
			&& d->cellType != StringType)
		return false;

	return d->richString.isRichString();
}

qint32 Cell::styleNumber() const 
{
	Q_D(const Cell);

	qint32 ret = d->styleNumber;
	return ret; 
}

QT_END_NAMESPACE_XLSX

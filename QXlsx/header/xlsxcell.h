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

#ifndef QXLSX_XLSXCELL_H
#define QXLSX_XLSXCELL_H

#include "xlsxglobal.h"
#include "xlsxformat.h"
#include <QVariant>

QT_BEGIN_NAMESPACE_XLSX

class Worksheet;
class Format;
class CellFormula;
class CellPrivate;
class WorksheetPrivate;

class   Cell
{
	Q_DECLARE_PRIVATE(Cell)
public:

	enum CellType {
		BooleanType,      //t="b"
		NumberType,       //t="n" (default)
		ErrorType,        //t="e"
		SharedStringType, //t="s"
		StringType,       //t="str"
		InlineStringType  //t="inlineStr"
	};
	/* cell type  of MIcrosoft Excel
		01) General − This is the default cell format of Cell.
		02) Number − This displays cell as number with separator.
		03) Currency − This displays cell as currency i.e. with currency sign.
		04) Accounting − Similar to Currency, used for accounting purpose.
		05) Date − Various date formats are available under this like 17-09-2013, 17th-Sep-2013, etc.
		06) Time − Various Time formats are available under this, like 1.30PM, 13.30, etc.
		07) Percentage − This displays cell as percentage with decimal places like 50.00%.
		08) Fraction − This displays cell as fraction like 1/4, 1/2 etc.
		09) Scientific − This displays cell as exponential like 5.6E+01.
		10) Text − This displays cell as normal text.
		11) Special − Special formats of cell like Zip code, Phone Number.
		12) Custom − You can use custom format by using this.
	*/

	CellType cellType() const;
	QVariant value() const;
	QVariant readValue() const;
	Format format() const;
	
	bool hasFormula() const;
	CellFormula formula() const;

	bool isDateTime() const;
	QDateTime dateTime() const;

	bool isRichString() const;

	~Cell();
private:
	friend class Worksheet;
	friend class WorksheetPrivate;

	Cell(const QVariant &data=QVariant(), CellType type=NumberType, const Format &format=Format(), Worksheet *parent=0);
	Cell(const Cell * const cell);
	CellPrivate * const d_ptr;
};

QT_END_NAMESPACE_XLSX

#endif // QXLSX_XLSXCELL_H

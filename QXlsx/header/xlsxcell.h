//--------------------------------------------------------------------
//
// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx
//
// QtXlsx
// https://github.com/dbzhang800/QtXlsxWriter
// http://qtxlsx.debao.me/
// MIT License

#ifndef QXLSX_XLSXCELL_H
#define QXLSX_XLSXCELL_H

#include <QtGlobal>
#include <QVariant>
#include <cstdio>

#include "xlsxglobal.h"
#include "xlsxformat.h"

QT_BEGIN_NAMESPACE_XLSX

class Worksheet;
class Format;
class CellFormula;
class CellPrivate;
class WorksheetPrivate;

class Cell
{
	Q_DECLARE_PRIVATE(Cell)
public:


    enum CellType
    {
        // ECMA 376, 18.18.11. ST_CellType (Cell Type)
		BooleanType,      //t="b"
		NumberType,       //t="n" (default)
		ErrorType,        //t="e"
		SharedStringType, //t="s"
		StringType,       //t="str"
        InlineStringType,  //t="inlineStr"
        DateType,   // "d" [dev34]

        CustomType,
	};

	CellType cellType() const;
	QVariant value() const;
	QVariant readValue() const;
	Format format() const;
	
	bool hasFormula() const;
	CellFormula formula() const;

	bool isDateTime() const;
	QDateTime dateTime() const;

	bool isRichString() const;

	qint32 styleNumber() const;

	~Cell();
private:
	friend class Worksheet;
	friend class WorksheetPrivate;

	Cell(const QVariant &data = QVariant(), 
		CellType type = NumberType, 
		const Format &format = Format(), 
		Worksheet *parent = NULL,
		qint32 styleIndex = (-1) );
	Cell(const Cell * const cell);
	CellPrivate * const d_ptr;
};

QT_END_NAMESPACE_XLSX

#endif // QXLSX_XLSXCELL_H

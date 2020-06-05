// numberformat.cpp

#include <QtGlobal>
#include <QtGui>

#include "xlsxdocument.h"
#include "xlsxformat.h"

QXLSX_USE_NAMESPACE

int numberformat()
{
	QXlsx::Document xlsx;
	xlsx.setColumnWidth(1, 4, 20.0);

	QXlsx::Format header;
	header.setFontBold(true);
	header.setFontSize(20);

	//Custom number formats
	QStringList numFormats;
	numFormats
		<< "Qt #"
		<< "yyyy-mmm-dd"
		<< "$ #,##0.00"
		<< "[red]0.00";
	xlsx.write(1, 1, "Raw data", header);
	xlsx.write(1, 2, "Format", header);
	xlsx.write(1, 3, "Shown value", header);
	for (int i=0; i<numFormats.size(); ++i) 
	{
		int row = i+2;
		xlsx.write(row, 1, 100.0);
		xlsx.write(row, 2, numFormats[i]);
		QXlsx::Format format;
		format.setNumberFormat(numFormats[i]);
		xlsx.write(row, 3, 100.0, format);
	}

	//Builtin number formats
	xlsx.addSheet();
	xlsx.setColumnWidth(1, 4, 20.0);
	xlsx.write(1, 1, "Raw data", header);
	xlsx.write(1, 2, "Builtin Format", header);
	xlsx.write(1, 3, "Shown value", header);
	for (int i=0; i<50; ++i) 
	{
		int row = i+2;
		int numFmt = i;
		xlsx.write(row, 1, 100.0);
		xlsx.write(row, 2, numFmt);
		QXlsx::Format format;
		format.setNumberFormatIndex(numFmt);
		xlsx.write(row, 3, 100.0, format);
	}

	xlsx.saveAs("numberformat.xlsx");

	return 0;
}

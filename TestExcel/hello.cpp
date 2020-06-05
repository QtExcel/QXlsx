// hello.cpp

#include <QtGlobal>
#include <QtCore>
#include <QDebug>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

QXLSX_USE_NAMESPACE

#include <cstdio>
#include <iostream>
// using namespace std;

int WriteExcel(bool isTest);
int ReadExcel(bool isTest);

void UseSheet(bool isTest);

void RichText(bool isTest);

void DoChart(bool isTest);
void Align(bool isTest);

int hello()
{
    WriteExcel(true);

	ReadExcel(true);

	UseSheet(true);

	RichText(true);

	DoChart(true);
    Align(true);

   return 0;
}

int WriteExcel(bool isTest)
{
	if (!isTest)
		return (-1);

	Document xlsx;

	xlsx.write("A1", "Hello QtXlsx!"); // current file is utf-8 character-set.
	xlsx.write("A2", 12345);
	xlsx.write("A3", "=44+33"); // cell value is 77.
	xlsx.write("A4", true);
	xlsx.write("A5", "http://qt-project.org");
	xlsx.write("A6", QDate(2013, 12, 27));
	xlsx.write("A7", QTime(6, 30));
    xlsx.write("A8", QDateTime(QDate(2049,7,23), QTime(23,5,32), Qt::LocalTime));

    if (!xlsx.saveAs("WriteExcel1.xlsx"))
	{
        qDebug() << "[WriteExcel1] failed to save excel file";
		return (-2);
	}

	return 0; 
}

int ReadExcel(bool isTest)
{
	if (!isTest)
		return (-1);

	{
		//Create a new .xlsx file.
		QXlsx::Document xlsx;

        xlsx.write("A1", "Hello Qt!");
        xlsx.write("A2", 12345);
        xlsx.write("A3", "=44+33");
        xlsx.write("A4", true);
        xlsx.write("A5", "http://qt-project.org");
        xlsx.write("A6", QDate(2013, 12, 27));
        xlsx.write("A7", QTime(6, 30));
        xlsx.write("A8", QDateTime(QDate(2049,7,23), QTime(23,5,32), Qt::LocalTime));

		if (!xlsx.saveAs("ReadExcel.xlsx"))
		{
			qDebug() << "[ReadExcel] failed to save excel file." ;
			return (-2);
		}
	}

	//![0]
	QXlsx::Document xlsx("ReadExcel.xlsx");
	if (!xlsx.isLoadPackage())
	{
		qDebug() << "[ReadExcel.xlsx] failed to load package";
		return (-3);
	}
	//![0]

	//![1]
	qDebug() << " QXlsx::Document.read()";
	qDebug() << xlsx.read("A1");
	qDebug() << xlsx.read("A2");
	qDebug() << xlsx.read("A3");
	qDebug() << xlsx.read("A4");
	qDebug() << xlsx.read("A5");
	qDebug() << xlsx.read("A6");
	qDebug() << xlsx.read("A7");
	qDebug() << xlsx.read("A8");
	//![1]

	/* debug output
	 QXlsx::Document.read()
	QVariant(QString, "Hello Qt!")
	QVariant(double, 12345)
	QVariant(QString, "=44+33")
	QVariant(bool, true)
	QVariant(QString, "http://qt-project.org")
	QVariant(QDate, QDate("2013-12-27"))
	QVariant(QTime, QTime("06:30:00.000"))
	QVariant(QDateTime, QDateTime(2049-07-23 23:05:32.000 KST Qt::TimeSpec(LocalTime)))
	*/

	//![2]
	qDebug() << " QXlsx::Cell.cellAt()";
	for ( int row = 1 ; row < 20 ; ++row )
	{
		Cell* cell = xlsx.cellAt(row, 1);
		if (cell == NULL)
			continue;
		QVariant var = cell->readValue();
		qint32 styleNo = cell->styleNumber();
		if (styleNo >= 0)
		{
			qDebug() << row << " " << var << " , style:" << styleNo;
		}
		else
		{
			qDebug() << row << " " << var;
		}
	}
	//![2]

	/* debug output 
	 QXlsx::Cell.cellAt()
	1   QVariant(QString, "Hello Qt!")
	2   QVariant(double, 12345)
	3   QVariant(QString, "44+33")
	4   QVariant(bool, true)
	5   QVariant(QString, "http://qt-project.org")  , style: 1
	6   QVariant(QDateTime, QDateTime(2013-12-27 00:00:00.000 KST Qt::TimeSpec(LocalTime)))  , style: 2
	7   QVariant(QDateTime, QDateTime(1899-12-31 06:30:00.000 KST Qt::TimeSpec(LocalTime)))  , style: 3
	8   QVariant(QDateTime, QDateTime(2049-07-23 23:05:32.000 KST Qt::TimeSpec(LocalTime)))  , style: 2
	*/ 

	return 0; 
}

void UseSheet(bool isTest)
{
	if (!isTest)
		return;

	{
		//![Create a xlsx file]
		Document xlsx;

		// current sheet is Sheet1(default sheet)
		for (int i = 1; i < 20; ++i)
		{
			for (int j = 1; j < 15; ++j)
			{
				xlsx.write(i, j, QString("R %1 C %2").arg(i).arg(j));
			}
		}

		xlsx.addSheet(); // current sheet is Sheet2
		xlsx.write(2, 2, "Hello Qt Xlsx");

		xlsx.addSheet(); // current sheet is Sheet3
		xlsx.write(3, 3, "This will be deleted...");

		xlsx.addSheet("HiddenSheet"); // current sheet is HiddenSheet
		xlsx.currentSheet()->setHidden(true);
		xlsx.write("A1", "This sheet is hidden.");

		xlsx.addSheet("VeryHiddenSheet"); // current sheet is VeryHiddenSheet 
		xlsx.sheet("VeryHiddenSheet")->setSheetState(AbstractSheet::SS_VeryHidden);
		xlsx.write("A1", "This sheet is very hidden.");

		if (!xlsx.save()) //Default name is "Book1.xlsx"
		{
			qDebug() << "[Book1.xlsx] failed to write excel.";
			return; 
		}
	}

	{
		Document xlsx2("Book1.xlsx");

		xlsx2.renameSheet("Sheet1", "TheFirstSheet"); // rename sheet 

		xlsx2.copySheet("TheFirstSheet", "CopyOfTheFirst"); // copy sheet 

		xlsx2.selectSheet("CopyOfTheFirst"); // current sheet is 'CopyOfTheFirst'
		xlsx2.write(25, 2, "On the Copy Sheet"); // write cell(25,2)

		xlsx2.deleteSheet("Sheet3"); // delete sheet 

		xlsx2.moveSheet("Sheet2", 0); // move sheet to first position 

		//![show_hidden_sheets]
		xlsx2.sheet("HiddenSheet")->setVisible(true);
		xlsx2.sheet("VeryHiddenSheet")->setVisible(true);
		//![show_hidden_sheets]

		xlsx2.selectSheet("TheFirstSheet"); // current sheet is 'TheFirstSheet'
		xlsx2.write(1, 1, QDate(2099,12,31));

		// list all sheets of document.
		QStringList slSheetNames = xlsx2.sheetNames();
		qDebug() << " Document::sheetNames()";
		for (int i = 0; i < slSheetNames.size(); ++i)
			qDebug() << " " << slSheetNames.at(i).toLocal8Bit().constData();
		/* debug output 
			Document::sheetNames()
				Sheet2
				TheFirstSheet
				HiddenSheet
				VeryHiddenSheet
				CopyOfTheFirst
		*/

		if (!xlsx2.saveAs("UseSheet.xlsx"))
		{
			qDebug() << "[UseSheet.xlsx] failed to write excel.";
			return;
		}
	}
}

void DoChart(bool isTest)
{
	if (!isTest)
		return;

	//![0]
	Document xlsx;
	for ( int i = 1 ; i < 10 ; ++i )
	{
		xlsx.write(i, 1, i*i);
	}
	//![0]
	/*
		1
		4
		9
		16
		25
		36
		49
		64
		81
	*/

	//![1]
	xlsx.addSheet("Chart1", AbstractSheet::ST_ChartSheet);
	Chartsheet *sheet = static_cast<Chartsheet*>(xlsx.currentSheet());
	Chart *barChart = sheet->chart();
    barChart->setChartType(Chart::CT_BarChart);
	barChart->addSeries(CellRange("A1:A9"), xlsx.sheet("Sheet1"));
	//![1]

	//![2]
	if (!xlsx.saveAs("DoChart.xlsx"))
	{
		qDebug() << "[DoChart] failed to create excel file";
	}
	//![2]

}

void Align(bool isTest)
{
	if (!isTest)
		return;

	Document xlsx;

	//![0]
	Format format;
	format.setHorizontalAlignment(Format::AlignHCenter);
	format.setVerticalAlignment(Format::AlignVCenter);
	//![0]

	//![1]
	xlsx.write("B4", "Hello Qt!");
	xlsx.mergeCells("B4:F6", format);

	xlsx.write("B8", 1);
	xlsx.mergeCells("B8:C21", format);

	xlsx.write("E8", 2);
	xlsx.mergeCells("E8:F21", format);
	//![1]

	if (!xlsx.saveAs("Align.xlsx"))
	{
		qDebug() << "[Align] failed to create excel file";
	}

}

void RichText(bool isTest)
{
	if (!isTest)
		return;

	//![0]
	QXlsx::Document xlsx;
	//![0]

	//![1]
	QXlsx::Format blue;
	blue.setFontColor(Qt::blue);
	QXlsx::Format red;
	red.setFontColor(Qt::red);
	red.setFontSize(15);
	QXlsx::Format bold;
	bold.setFontBold(true);

	QXlsx::RichString rich;
	rich.addFragment("Hello ", blue);
	rich.addFragment("Qt ", red);
	rich.addFragment("Xlsx", bold);
	xlsx.write("B2", rich);

	xlsx.workbook()->setHtmlToRichStringEnabled(true);
	xlsx.write("B4", "<b>Hello</b> <font color=\"red\">Qt</font> <i>Xlsx</i>");

	xlsx.write("B6", "<font color=\"red\"><b><u><i>Qt Xlsx</i></u></b></font>");

	//![1]

	//![2]
	xlsx.saveAs("RichText.xlsx");
	//![2]
}



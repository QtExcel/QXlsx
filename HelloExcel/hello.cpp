// hello.cpp

#include <QtCore>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

void WriteExcel(bool isTest);
void ReadExcel(bool isTest);

void UseSheet(bool isTest);

void RichText(bool isTest);

void DoChart(bool isTest);
void Align(bool isTest);

int hello()
{
	// WriteExcel(true);
	ReadExcel(true);

	UseSheet(true);

	RichText(true);

	DoChart(true);
	Align(true);

   return 0;
}

void WriteExcel(bool isTest)
{
	if (!isTest)
		return;

	Document xlsx;

	xlsx.write("A1", "Hello QtXlsx!"); // current file is utf-8 character-set.
	xlsx.write("A2", 12345);
	xlsx.write("A3", "=44+33"); // cell value is 77.
	xlsx.write("A4", true);
	xlsx.write("A5", "http://qt-project.org");
	xlsx.write("A6", QDate(2013, 12, 27));
	xlsx.write("A7", QTime(6, 30));

	if (!xlsx.saveAs("WriteExcel.xlsx"))
		qDebug() << "[WriteExcel] failed to save excel file" ;
}

void ReadExcel(bool isTest)
{
	if (!isTest)
		return;

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

		if (!xlsx.saveAs("ReadExcel.xlsx"))
		{
			qDebug() << "[ReadExcel] failed to save excel file" ;
			return;
		}
	}

	//![0]
	QXlsx::Document xlsx("ReadExcel.xlsx");
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
	//![1]

	/* debug output
	QVariant(QString, "Hello Qt!")
	QVariant(double, 12345)
	QVariant(QString, "=44+33") // it's string. it is not a formula.
	QVariant(bool, true)
	QVariant(QString, "http://qt-project.org")
	QVariant(QDate, QDate("2013-12-27"))
	QVariant(QTime, QTime("06:30:00.000"))
	*/

	//![2]
	qDebug() << " QXlsx::Cell.cellAt()";
	for ( int row = 1 ; row < 10 ; ++row )
	{
		if ( Cell* cell = xlsx.cellAt( row, 1 ) )
		{
			if (cell == NULL)
				continue;

			QVariant var = cell->value();

			// NOTICE!: this shoud be new function 
			// NOTE: Don't append code in cell.vlaue() fucntion.   
			if (cell->isDateTime()) 
			{
				double val = var.toDouble();
				if (val < 1) 
					var = cell->dateTime().time();
				if (fmod(val, 1.0) <  1.0 / (1000 * 60 * 60 * 24)) 
					var = cell->dateTime().date();
			}

			qDebug() << row << " " << var;
		}
	}
	//![2]
	
	/* debug output
	1   QVariant(QString, "Hello Qt!")
	2   QVariant(double, 12345)
	3   QVariant(double, 0)
	4   QVariant(bool, true)
	5   QVariant(QString, "http://qt-project.org")
	6   QVariant(double, 41635)      // something wrong
	7   QVariant(double, 0.270833)   // something wrong

	*/
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
	barChart->setChartType(Chart::CT_Bar);
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

void UseSheet(bool isTest)
{
	if (!isTest)
		return;

	{
		//![Create a xlsx file]
		Document xlsx;

		for ( int i = 1 ; i < 20 ; ++i )
		{
			for ( int j = 1 ; j < 15 ; ++j )
				xlsx.write( i, j, QString("R %1 C %2").arg(i).arg(j) );
		}

		xlsx.addSheet();
		xlsx.write(2, 2, "Hello Qt Xlsx");

		xlsx.addSheet();
		xlsx.write(3, 3, "This will be deleted...");

		xlsx.addSheet("HiddenSheet");
		xlsx.currentSheet()->setHidden(true);
		xlsx.write("A1", "This sheet is hidden.");

		xlsx.addSheet("VeryHiddenSheet");
		xlsx.sheet("VeryHiddenSheet")->setSheetState(AbstractSheet::SS_VeryHidden);
		xlsx.write("A1", "This sheet is very hidden.");

		xlsx.save();//Default name is "Book1.xlsx"
		//![Create a xlsx file]
	}

	{
		Document xlsx2("Book1.xlsx");
		//![add_copy_move_delete]

		xlsx2.renameSheet("Sheet1", "TheFirstSheet");

		xlsx2.copySheet("TheFirstSheet", "CopyOfTheFirst");

		xlsx2.selectSheet("CopyOfTheFirst");
		xlsx2.write(25, 2, "On the Copy Sheet");

		xlsx2.deleteSheet("Sheet3");

		xlsx2.moveSheet("Sheet2", 0);
		//![add_copy_move_delete]

		//![show_hidden_sheets]
		xlsx2.sheet("HiddenSheet")->setVisible(true);
		xlsx2.sheet("VeryHiddenSheet")->setVisible(true);
		//![show_hidden_sheets]

		if ( !xlsx2.saveAs("UseSheet.xlsx") )
		{
			return;
		}
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



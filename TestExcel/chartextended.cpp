// chartextended.cpp

#include <QtGlobal>
#include <QtCore>
#include <QDebug>

#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"

QXLSX_USE_NAMESPACE

/*
 * Test Chart with title, gridlines, legends, multiple headers
 *
 */

int chartExtended()
{
    Document xlsx;
    for (int i=1; i<10; ++i)
    {
        xlsx.write(1, i+1, "Pos " + QString::number(i));
    }

    xlsx.write(2, 1, "Set 1");
    xlsx.write(3, 1, "Set 2");

    for (int i=1; i<10; ++i)
    {
        xlsx.write(2, i+1, i*i*i);   //A2:A10
        xlsx.write(3, i+1, i*i);    //B2:B10
    }


    Chart *barChart1 = xlsx.insertChart(4, 3, QSize(300, 300));
    barChart1->setChartType(Chart::CT_BarChart);
    barChart1->setChartLegend(Chart::Right);
    barChart1->setChartTitle("Test1");
    // Messreihen
    barChart1->addSeries(CellRange(1,1,3,10), NULL, true, true, false);

    Chart *barChart2 = xlsx.insertChart(4, 9, QSize(300, 300));
    barChart2->setChartType(Chart::CT_BarChart);
    barChart2->setChartLegend(Chart::Right);
    barChart2->setChartTitle("Test2");
    barChart2->setGridlinesEnable(true);
    // Messreihen
    barChart2->addSeries(CellRange(1,1,3,10), NULL, true, true, true);

    Chart *barChart3 = xlsx.insertChart(24, 3, QSize(300, 300));
    barChart3->setChartType(Chart::CT_BarChart);
    barChart3->setChartLegend(Chart::Left);
    barChart3->setChartTitle("Test3");
    // Messreihen
    barChart3->addSeries(CellRange(1,1,3,10));

    Chart *barChart4 = xlsx.insertChart(24, 9, QSize(300, 300));
    barChart4->setChartType(Chart::CT_BarChart);
    barChart4->setChartLegend(Chart::Top);
    barChart4->setChartTitle("Test4");
    // Messreihen
    barChart4->addSeries(CellRange(1,1,3,10));

    Chart *barChart5 = xlsx.insertChart(44, 9, QSize(300, 300));
    barChart5->setChartType(Chart::CT_BarChart);
    barChart5->setChartLegend(Chart::Bottom);
    barChart5->setChartTitle("Test5");
    // Messreihen
    barChart5->addSeries(CellRange(1,1,3,10));


    //![2]
    xlsx.saveAs("chartExtended1.xlsx");
    //![2]

    Document xlsx2("chartExtended1.xlsx");
    if ( xlsx2.load() )
    {
        xlsx2.saveAs("chartExtended2.xlsx");
    }

    return 0;
}

#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"

using namespace QXlsx;

int main()
{
    //![0]
    Document xlsx;
    for (int i=1; i<10; ++i) {
        xlsx.write(i, 1, i*i*i);   //A1:A9
        xlsx.write(i, 2, i*i); //B1:B9
        xlsx.write(i, 3, i*i-1); //C1:C9
    }
    //![0]

    //![1]
    Chart *pieChart = xlsx.insertChart(3, 3, QSize(300, 300));
    pieChart->setChartType(Chart::CT_Pie);
    pieChart->addSeries(CellRange("A1:A9"));
    pieChart->addSeries(CellRange("B1:B9"));
    pieChart->addSeries(CellRange("C1:C9"));

    Chart *pie3DChart = xlsx.insertChart(3, 9, QSize(300, 300));
    pie3DChart->setChartType(Chart::CT_Pie3D);
    pie3DChart->addSeries(CellRange("A1:C9"));

    Chart *barChart = xlsx.insertChart(23, 3, QSize(300, 300));
    barChart->setChartType(Chart::CT_Bar);
    barChart->addSeries(CellRange("A1:C9"));

    Chart *bar3DChart = xlsx.insertChart(23, 9, QSize(300, 300));
    bar3DChart->setChartType(Chart::CT_Bar3D);
    bar3DChart->addSeries(CellRange("A1:C9"));

    Chart *lineChart = xlsx.insertChart(43, 3, QSize(300, 300));
    lineChart->setChartType(Chart::CT_Line);
    lineChart->addSeries(CellRange("A1:C9"));

    Chart *line3DChart = xlsx.insertChart(43, 9, QSize(300, 300));
    line3DChart->setChartType(Chart::CT_Line3D);
    line3DChart->addSeries(CellRange("A1:C9"));

    Chart *areaChart = xlsx.insertChart(63, 3, QSize(300, 300));
    areaChart->setChartType(Chart::CT_Area);
    areaChart->addSeries(CellRange("A1:C9"));

    Chart *area3DChart = xlsx.insertChart(63, 9, QSize(300, 300));
    area3DChart->setChartType(Chart::CT_Area3D);
    area3DChart->addSeries(CellRange("A1:C9"));

    Chart *scatterChart = xlsx.insertChart(83, 3, QSize(300, 300));
    scatterChart->setChartType(Chart::CT_Scatter);
    //Will generate three lines.
    scatterChart->addSeries(CellRange("A1:A9"));
    scatterChart->addSeries(CellRange("B1:B9"));
    scatterChart->addSeries(CellRange("C1:C9"));

    Chart *scatterChart_2 = xlsx.insertChart(83, 9, QSize(300, 300));
    scatterChart_2->setChartType(Chart::CT_Scatter);
    //Will generate two lines.
    scatterChart_2->addSeries(CellRange("A1:C9"));

    Chart *doughnutChart = xlsx.insertChart(103, 3, QSize(300, 300));
    doughnutChart->setChartType(Chart::CT_Doughnut);
    doughnutChart->addSeries(CellRange("A1:C9"));
    //![1]

    //![2]
    xlsx.saveAs("Book1.xlsx");
    //![2]

    Document xlsx2("Book1.xlsx");
    xlsx2.saveAs("Book2.xlsx");
    return 0;
}

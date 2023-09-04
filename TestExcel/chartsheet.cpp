// chartsheet.cpp

#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"

#include <QtGlobal>

QXLSX_USE_NAMESPACE

int chartsheet()
{
    //![0]
    Document xlsx;
    for (int i = 1; i < 10; ++i) {
        xlsx.write(i, 1, i * i);
    }
    //![0]

    //![1]
    xlsx.addSheet("Chart1", AbstractSheet::ST_ChartSheet);
    Chartsheet *sheet = static_cast<Chartsheet *>(xlsx.currentSheet());
    Chart *barChart   = sheet->chart();
    barChart->setChartType(Chart::CT_BarChart);
    barChart->addSeries(CellRange("A1:A9"), xlsx.sheet("Sheet1"));
    //![1]

    //![2]
    xlsx.saveAs("chartsheet1.xlsx");
    //![2]

    Document xlsx2("chartsheet1.xlsx");
    if (xlsx2.load()) {
        xlsx2.saveAs("chartsheet2.xlsx");
    }

    return 0;
}

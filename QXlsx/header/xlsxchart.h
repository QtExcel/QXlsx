/****************************************************************************
** Copyright (c) 2013-2014 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef QXLSX_CHART_H
#define QXLSX_CHART_H

#include "xlsxabstractooxmlfile.h"

#include <QSharedPointer>

class QXmlStreamReader;
class QXmlStreamWriter;

QT_BEGIN_NAMESPACE_XLSX

class AbstractSheet;
class Worksheet;
class ChartPrivate;
class CellRange;
class DrawingAnchor;
// class XlsxAxis;
// enum XlsxAxisPos : short;

class Chart : public AbstractOOXmlFile
{
    Q_DECLARE_PRIVATE(Chart)
public:
    enum ChartType { // 16 type of chart
        CT_NoStatementChart = 0, //Zero is internally used for unknown types
        CT_AreaChart, CT_Area3DChart, CT_LineChart,
        CT_Line3DChart, CT_StockChart, CT_RadarChart,
        CT_ScatterChart, CT_PieChart, CT_Pie3DChart,
        CT_DoughnutChart, CT_BarChart, CT_Bar3DChart,
        CT_OfPieChart, CT_SurfaceChart, CT_Surface3DChart,
        CT_BubbleChart,
    };
    enum ChartAxisPos { Left, Right, Top, Bottom  };
private:
    friend class AbstractSheet;
    friend class Worksheet;
    friend class Chartsheet;
    friend class DrawingAnchor;
private:
    Chart(AbstractSheet *parent, CreateFlag flag);
public:
    ~Chart();
public:
    void addSeries(const CellRange &range, AbstractSheet *sheet=0);
    void setChartType(ChartType type);
    void setChartStyle(int id);
    void setAxisTitle(Chart::ChartAxisPos pos, QString axisTitle);
    void setChartTitle(QString strchartTitle);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
};

QT_END_NAMESPACE_XLSX

#endif // QXLSX_CHART_H

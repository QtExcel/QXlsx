// xlsxchart_p.h

#ifndef QXLSX_CHART_P_H
#define QXLSX_CHART_P_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QVector>
#include <QMap>
#include <QList>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "xlsxabstractooxmlfile_p.h"
#include "xlsxchart.h"

QT_BEGIN_NAMESPACE_XLSX

class XlsxSeries
{
public:
    //At present, we care about number cell ranges only!
    QString numberDataSource_numRef; // yval, val
    QString axDataSource_numRef; // xval, cat
};

class XlsxAxis
{
public:
    enum Type { T_Cat, T_Val, T_Date, T_Ser };
    enum AxisPos { None = (-1), Left, Right, Top, Bottom };
public:
    XlsxAxis(){}
    XlsxAxis(Type t, XlsxAxis::AxisPos  p, int id, int crossId,
             QString axisTitle = QString(""))
        :type(t), axisPos(p), axisId(id), crossAx(crossId)
    {
        if ( !axisTitle.isEmpty() )
        {
            axisNames[ p ] = axisTitle;
        }
    }
public:
    Type type;
    XlsxAxis::AxisPos axisPos;
    int axisId;
    int crossAx;
    QMap< XlsxAxis::AxisPos, QString > axisNames;
};

class ChartPrivate : public AbstractOOXmlFilePrivate
{
    Q_DECLARE_PUBLIC(Chart)

public:
    ChartPrivate(Chart *q, Chart::CreateFlag flag);
    ~ChartPrivate();

public:
    bool loadXmlChart(QXmlStreamReader &reader);
    bool loadXmlPlotArea(QXmlStreamReader &reader);
    bool loadXmlXxxChart(QXmlStreamReader &reader);
    bool loadXmlSer(QXmlStreamReader &reader);
    QString loadXmlNumRef(QXmlStreamReader &reader);
    bool loadXmlAxis(QXmlStreamReader &reader);

public:
    void saveXmlChart(QXmlStreamWriter &writer) const;
    void saveXmlChartTitle(QXmlStreamWriter &writer) const;
    void saveXmlPieChart(QXmlStreamWriter &writer) const;
    void saveXmlBarChart(QXmlStreamWriter &writer) const;
    void saveXmlLineChart(QXmlStreamWriter &writer) const;
    void saveXmlScatterChart(QXmlStreamWriter &writer) const;
    void saveXmlAreaChart(QXmlStreamWriter &writer) const;
    void saveXmlDoughnutChart(QXmlStreamWriter &writer) const;
    void saveXmlSer(QXmlStreamWriter &writer, XlsxSeries *ser, int id) const;
    void saveXmlAxes(QXmlStreamWriter &writer) const;

public:
    Chart::ChartType chartType;
    QList< QSharedPointer<XlsxSeries> > seriesList;
    QList< QSharedPointer<XlsxAxis> > axisList;
    QMap< XlsxAxis::AxisPos, QString > axisNames;
    QString chartTitle;
    AbstractSheet *sheet;
};

QT_END_NAMESPACE_XLSX

#endif // QXLSX_CHART_P_H

// xlsxchart.cpp

#include <QtGlobal>
#include <QString>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

#include "xlsxchart_p.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxutility_p.h"

QT_BEGIN_NAMESPACE_XLSX

ChartPrivate::ChartPrivate(Chart *q, Chart::CreateFlag flag)
    : AbstractOOXmlFilePrivate(q, flag), chartType(static_cast<Chart::ChartType>(0))
{

}

ChartPrivate::~ChartPrivate()
{
    /*
    QList< QSharedPointer<XlsxSeries> > seriesList;
    QList< QSharedPointer<XlsxAxis> > axisList;
    QMap< XlsxAxis::AxisPos, QString > axisNames;
     */
    // qDeleteAll( seriesList );
    // qDeleteAll( axisList );
    // qDeleteAll( axisNames );

    /*
    for (int i = 0; i < axisList.size(); ++i)
    {
        QSharedPointer<XlsxAxis> ptr = axisList.at(i);
        // ptr->deleteLater();
    }
    */

}



/*!
 * \internal
 */
Chart::Chart(AbstractSheet *parent, CreateFlag flag)
    : AbstractOOXmlFile(new ChartPrivate(this, flag))
{
    d_func()->sheet = parent;
}

/*!
 * Destroys the chart.
 */
Chart::~Chart()
{
}

/*!
 * Add the data series which is in the range \a range of the \a sheet.
 */
void Chart::addSeries(const CellRange &range, AbstractSheet *sheet)
{
    Q_D(Chart);

    if (!range.isValid())
        return;
    if (sheet && sheet->sheetType() != AbstractSheet::ST_WorkSheet)
        return;
    if (!sheet && d->sheet->sheetType() != AbstractSheet::ST_WorkSheet)
        return;

    QString sheetName = sheet ? sheet->sheetName() : d->sheet->sheetName();
    //In case sheetName contains space or '
    sheetName = escapeSheetName(sheetName);

    if (range.columnCount() == 1 || range.rowCount() == 1)
    {
        QSharedPointer<XlsxSeries> series = QSharedPointer<XlsxSeries>(new XlsxSeries);
        series->numberDataSource_numRef = sheetName + QLatin1String("!") + range.toString(true, true);
        d->seriesList.append(series);
    }
    else if (range.columnCount() < range.rowCount())
    {
        //Column based series
        int firstDataColumn = range.firstColumn();
        QString axDataSouruce_numRef;
        if (d->chartType == CT_ScatterChart || d->chartType == CT_BubbleChart)
        {
            firstDataColumn += 1;
            CellRange subRange(range.firstRow(), range.firstColumn(), range.lastRow(), range.firstColumn());
            axDataSouruce_numRef = sheetName + QLatin1String("!") + subRange.toString(true, true);
        }

        for (int col=firstDataColumn; col<=range.lastColumn(); ++col)
        {
            CellRange subRange(range.firstRow(), col, range.lastRow(), col);
            QSharedPointer<XlsxSeries> series = QSharedPointer<XlsxSeries>(new XlsxSeries);
            series->axDataSource_numRef = axDataSouruce_numRef;
            series->numberDataSource_numRef = sheetName + QLatin1String("!") + subRange.toString(true, true);
            d->seriesList.append(series);
        }

    }
    else
    {
        //Row based series
        int firstDataRow = range.firstRow();
        QString axDataSouruce_numRef;
        if (d->chartType == CT_ScatterChart || d->chartType == CT_BubbleChart)
        {
            firstDataRow += 1;
            CellRange subRange(range.firstRow(), range.firstColumn(), range.firstRow(), range.lastColumn());
            axDataSouruce_numRef = sheetName + QLatin1String("!") + subRange.toString(true, true);
        }

        for (int row=firstDataRow; row<=range.lastRow(); ++row)
        {
            CellRange subRange(row, range.firstColumn(), row, range.lastColumn());
            QSharedPointer<XlsxSeries> series = QSharedPointer<XlsxSeries>(new XlsxSeries);
            series->axDataSource_numRef = axDataSouruce_numRef;
            series->numberDataSource_numRef = sheetName + QLatin1String("!") + subRange.toString(true, true);
            d->seriesList.append(series);
        }
    }
}

/*!
 * Set the type of the chart to \a type
 */
void Chart::setChartType(ChartType type)
{
    Q_D(Chart);

    d->chartType = type;
}

/*!
 * \internal
 *
 */
void Chart::setChartStyle(int id)
{
    Q_UNUSED(id)
    //!Todo
}

void Chart::setAxisTitle(Chart::ChartAxisPos pos, QString axisTitle)
{
    Q_D(Chart);

    if ( axisTitle.isEmpty() )
        return;

    // dev24 : fixed for old compiler
    if ( pos == Chart::Left )
    {
        d->axisNames[ XlsxAxis::Left ] = axisTitle;
    }
    else if ( pos == Chart::Top )
    {
        d->axisNames[ XlsxAxis::Top ] = axisTitle;
    }
    else if ( pos == Chart::Right )
    {
        d->axisNames[ XlsxAxis::Right ] = axisTitle;
    }
    else if ( pos == Chart::Bottom )
    {
        d->axisNames[ XlsxAxis::Bottom ] = axisTitle;
    }
    else
    {
    }

}

// dev25
void Chart::setChartTitle(QString strchartTitle)
{
    Q_D(Chart);

    d->chartTitle = strchartTitle;
}


/*!
 * \internal
 */
void Chart::saveToXmlFile(QIODevice *device) const
{
    Q_D(const Chart);

    /*
        <chartSpace>
            <chart>
                <view3D>
                    <perspective val="30"/>
                </view3D>
                <plotArea>
                    <layout/>
                    <barChart>
                    ...
                    </barChart>
                    <catAx/>
                    <valAx/>
                </plotArea>
                <legend>
                ...
                </legend>
            </chart>
            <printSettings>
            </printSettings>
        </chartSpace>
    */

    QXmlStreamWriter writer(device);

    writer.writeStartDocument(QStringLiteral("1.0"), true);

    // L.4.13.2.2 Chart
    //
    //  chartSpace is the root node, which contains an element defining the chart,
    // and an element defining the print settings for the chart.
    writer.writeStartElement(QStringLiteral("c:chartSpace"));

    writer.writeAttribute(QStringLiteral("xmlns:c"),
                          QStringLiteral("http://schemas.openxmlformats.org/drawingml/2006/chart"));
    writer.writeAttribute(QStringLiteral("xmlns:a"),
                          QStringLiteral("http://schemas.openxmlformats.org/drawingml/2006/main"));
    writer.writeAttribute(QStringLiteral("xmlns:r"),
                          QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships"));

    /*
    * chart is the root element for the chart. If the chart is a 3D chart,
    * then a view3D element is contained, which specifies the 3D view.
    * It then has a plot area, which defines a layout and contains an element
    * that corresponds to, and defines, the type of chart.
    */
    d->saveXmlChart(writer);

    writer.writeEndElement();// c:chartSpace
    writer.writeEndDocument();
}

/*!
 * \internal
 */
bool Chart::loadFromXmlFile(QIODevice *device)
{
    Q_D(Chart);

    QXmlStreamReader reader(device);
    while (!reader.atEnd())
    {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (reader.name() == QLatin1String("chart"))
            {
                if (!d->loadXmlChart(reader))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool ChartPrivate::loadXmlChart(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("chart"));

    while (!reader.atEnd())
    {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (reader.name() == QLatin1String("plotArea"))
            {
                if (!loadXmlPlotArea(reader))
                {
                    return false;
                }
            }
            else if (reader.name() == QLatin1String("title"))
            {
                //!Todo

                if ( loadXmlChartTitle(reader) )
                {
                }

            }
            else if (reader.name() == QLatin1String("legend"))
            {
                //!Todo
            }
        }
        else if (reader.tokenType() == QXmlStreamReader::EndElement &&
                 reader.name() == QLatin1String("chart") )
        {
            break;
        }
    }
    return true;
}

bool ChartPrivate::loadXmlPlotArea(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("plotArea"));

    while (!reader.atEnd())
    {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (reader.name() == QLatin1String("layout"))
            {
                //!ToDo
            }
            else if (reader.name().endsWith(QLatin1String("Chart")))
            {
                //For pieChart, barChart, ... (choose one)
                loadXmlXxxChart(reader);
            }
            else if (reader.name().endsWith(QLatin1String("Ax")))
            {
                // valAx, catAx, serAx, dateAx (select one)
                loadXmlAxis(reader);
            }
            else if (reader.name() == QLatin1String("dTable"))
            {
                //!ToDo
                // dTable "CT_DTable"
            }
            else if (reader.name() == QLatin1String("spPr"))
            {
                //!ToDo
                // spPr "a:CT_ShapeProperties"
            }
            else if (reader.name() == QLatin1String("extLst"))
            {
                //!ToDo
                // extLst "CT_ExtensionList"
            }
        }
        else if (reader.tokenType() == QXmlStreamReader::EndElement &&
                   reader.name() == QLatin1String("plotArea"))
        {
            break;
        }
    }
    return true;
}

bool ChartPrivate::loadXmlXxxChart(QXmlStreamReader &reader)
{
    QStringRef name = reader.name();

    // dev35
    if (name == QLatin1String("areaChart")) chartType = Chart::CT_AreaChart;
    else if (name == QLatin1String("area3DChart")) chartType = Chart::CT_Area3DChart;
    else if (name == QLatin1String("lineChart")) chartType = Chart::CT_LineChart;
    else if (name == QLatin1String("line3DChart")) chartType = Chart::CT_Line3DChart;
    else if (name == QLatin1String("stockChart")) chartType = Chart::CT_StockChart;
    else if (name == QLatin1String("radarChart")) chartType = Chart::CT_RadarChart;
    else if (name == QLatin1String("scatterChart")) chartType = Chart::CT_ScatterChart;
    else if (name == QLatin1String("pieChart")) chartType = Chart::CT_PieChart;
    else if (name == QLatin1String("pie3DChart")) chartType = Chart::CT_Pie3DChart;
    else if (name == QLatin1String("doughnutChart")) chartType = Chart::CT_DoughnutChart;
    else if (name == QLatin1String("barChart")) chartType = Chart::CT_BarChart;
    else if (name == QLatin1String("bar3DChart")) chartType = Chart::CT_Bar3DChart;
    else if (name == QLatin1String("ofPieChart")) chartType = Chart::CT_OfPieChart;
    else if (name == QLatin1String("surfaceChart")) chartType = Chart::CT_SurfaceChart;
    else if (name == QLatin1String("surface3DChart")) chartType = Chart::CT_Surface3DChart;
    else if (name == QLatin1String("bubbleChart")) chartType = Chart::CT_BubbleChart;
    else
    {
        qDebug() << "[undefined chart type] " << name;
        chartType = Chart::CT_NoStatementChart;
        return false;
    }

    while (!reader.atEnd())
    {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (reader.name() == QLatin1String("ser"))
            {
                loadXmlSer(reader);
            } else if (reader.name() == QLatin1String("axId"))
            {
                //!TODO
            }

        } else if (reader.tokenType() == QXmlStreamReader::EndElement &&
                   reader.name() == name)
        {
            break;
        }
    }

    return true;
}

bool ChartPrivate::loadXmlSer(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("ser"));

    QSharedPointer<XlsxSeries> series = QSharedPointer<XlsxSeries>(new XlsxSeries);
    seriesList.append(series);

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("ser")))
    {
        if (reader.readNextStartElement())
        {
            QStringRef name = reader.name();
            if (name == QLatin1String("cat") || name == QLatin1String("xVal"))
            {
                while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                            && reader.name() == name))
                {
                    if (reader.readNextStartElement())
                    {
                        if (reader.name() == QLatin1String("numRef"))
                            series->axDataSource_numRef = loadXmlNumRef(reader);
                    }
                }
            }
            else if (name == QLatin1String("val") || name == QLatin1String("yVal"))
            {
                while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                            && reader.name() == name))
                {
                    if (reader.readNextStartElement()) {
                        if (reader.name() == QLatin1String("numRef"))
                            series->numberDataSource_numRef = loadXmlNumRef(reader);
                    }
                }
            }
            else if (name == QLatin1String("extLst"))
            {
                while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                            && reader.name() == name)) {
                    reader.readNextStartElement();
                }
            }
        }
    }

    return true;
}


QString ChartPrivate::loadXmlNumRef(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("numRef"));

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("numRef"))) {
        if (reader.readNextStartElement()) {
            if (reader.name() == QLatin1String("f"))
                return reader.readElementText();
        }
    }

    return QString();
}

void ChartPrivate::saveXmlChart(QXmlStreamWriter &writer) const
{
    //----------------------------------------------------
    // c:chart
    writer.writeStartElement(QStringLiteral("c:chart"));

    //----------------------------------------------------
    // c:title

    saveXmlChartTitle(writer); // wrtie 'chart title'

    //----------------------------------------------------
    // c:plotArea

    writer.writeStartElement(QStringLiteral("c:plotArea"));

    // dev35
    switch (chartType)
    {
        case Chart::CT_AreaChart:       saveXmlAreaChart(writer); break;
        case Chart::CT_Area3DChart:     saveXmlAreaChart(writer); break;
        case Chart::CT_LineChart:       saveXmlLineChart(writer); break;
        case Chart::CT_Line3DChart:     saveXmlLineChart(writer); break;
        case Chart::CT_StockChart: break;
        case Chart::CT_RadarChart: break;
        case Chart::CT_ScatterChart:    saveXmlScatterChart(writer); break;
        case Chart::CT_PieChart:        saveXmlPieChart(writer); break;
        case Chart::CT_Pie3DChart:      saveXmlPieChart(writer); break;
        case Chart::CT_DoughnutChart:   saveXmlDoughnutChart(writer); break;
        case Chart::CT_BarChart:        saveXmlBarChart(writer); break;
        case Chart::CT_Bar3DChart:      saveXmlBarChart(writer); break;
        case Chart::CT_OfPieChart: break;
        case Chart::CT_SurfaceChart:  break;
        case Chart::CT_Surface3DChart: break;
        case Chart::CT_BubbleChart:  break;
        default:  break;
    }

    saveXmlAxes(writer);

    writer.writeEndElement(); // c:plotArea

    // save-legend // c:legend

    writer.writeEndElement(); // c:chart
}

bool ChartPrivate::loadXmlChartTitle(QXmlStreamReader &reader)
{
    //!TODO : load chart title

    Q_ASSERT(reader.name() == QLatin1String("title"));

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("title")))
    {
        if (reader.readNextStartElement())
        {
            // QStringRef strName = reader.name();
            // qDebug() << strName << reader.readElementText();

            if (reader.name() == QLatin1String("tx")) // c:tx
                return loadXmlChartTitleTx(reader);
        }
    }

    return false;
}

bool ChartPrivate::loadXmlChartTitleTx(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("tx"));

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("tx")))
    {
        if (reader.readNextStartElement())
        {
            // QStringRef strName = reader.name();
            // qDebug() << strName << reader.readElementText();

            if (reader.name() == QLatin1String("rich")) // c:rich
                return loadXmlChartTitleTxRich(reader);
        }
    }

    return false;
}

bool ChartPrivate::loadXmlChartTitleTxRich(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("rich"));

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("rich")))
    {
        if (reader.readNextStartElement())
        {
            // QStringRef strName = reader.name();
            // qDebug() << strName << reader.readElementText();

            if (reader.name() == QLatin1String("p")) // a:p
                return loadXmlChartTitleTxRichP(reader);
        }
    }

    return false;
}

bool ChartPrivate::loadXmlChartTitleTxRichP(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("p"));

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("p")))
    {
        if (reader.readNextStartElement())
        {
            // QStringRef strName = reader.name();
            // qDebug() << strName << reader.readElementText();

            if (reader.name() == QLatin1String("r")) // a:r
                return loadXmlChartTitleTxRichP_R(reader);
        }
    }

    return false;
}

bool ChartPrivate::loadXmlChartTitleTxRichP_R(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("r"));

    while (!reader.atEnd() && !(reader.tokenType() == QXmlStreamReader::EndElement
                                && reader.name() == QLatin1String("r")))
    {
        if (reader.readNextStartElement())
        {
            // QStringRef strName = reader.name();
            // qDebug() << strName << reader.readElementText();

            if (reader.name() == QLatin1String("t")) // a:t
            {
                QString textValue = reader.readElementText();
                this->chartTitle = textValue;
                return true;
            }
        }
    }

    return false;
}


// wrtie 'chart title'
void ChartPrivate::saveXmlChartTitle(QXmlStreamWriter &writer) const
{
    if ( chartTitle.isEmpty() )
        return;

    writer.writeStartElement(QStringLiteral("c:title"));
    /*
    <xsd:complexType name="CT_Title">
        <xsd:sequence>
            <xsd:element name="tx"      type="CT_Tx"                minOccurs="0" maxOccurs="1"/>
            <xsd:element name="layout"  type="CT_Layout"            minOccurs="0" maxOccurs="1"/>
            <xsd:element name="overlay" type="CT_Boolean"           minOccurs="0" maxOccurs="1"/>
            <xsd:element name="spPr"    type="a:CT_ShapeProperties" minOccurs="0" maxOccurs="1"/>
            <xsd:element name="txPr"    type="a:CT_TextBody"        minOccurs="0" maxOccurs="1"/>
            <xsd:element name="extLst"  type="CT_ExtensionList"     minOccurs="0" maxOccurs="1"/>
        </xsd:sequence>
    </xsd:complexType>
    */

        writer.writeStartElement(QStringLiteral("c:tx"));
        /*
        <xsd:complexType name="CT_Tx">
            <xsd:sequence>
                <xsd:choice     minOccurs="1"   maxOccurs="1">
                <xsd:element    name="strRef"   type="CT_StrRef"        minOccurs="1" maxOccurs="1"/>
                <xsd:element    name="rich"     type="a:CT_TextBody"    minOccurs="1" maxOccurs="1"/>
                </xsd:choice>
            </xsd:sequence>
        </xsd:complexType>
        */

            writer.writeStartElement(QStringLiteral("c:rich"));
            /*
            <xsd:complexType name="CT_TextBody">
                <xsd:sequence>
                    <xsd:element name="bodyPr"      type="CT_TextBodyProperties"    minOccurs=" 1"  maxOccurs="1"/>
                    <xsd:element name="lstStyle"    type="CT_TextListStyle"         minOccurs="0"   maxOccurs="1"/>
                    <xsd:element name="p"           type="CT_TextParagraph"         minOccurs="1"   maxOccurs="unbounded"/>
                </xsd:sequence>
            </xsd:complexType>
            */

                writer.writeEmptyElement(QStringLiteral("a:bodyPr")); // <a:bodyPr/>
                /*
                <xsd:complexType name="CT_TextBodyProperties">
                    <xsd:sequence>
                        <xsd:element name="prstTxWarp" type="CT_PresetTextShape" minOccurs="0" maxOccurs="1"/>
                        <xsd:group ref="EG_TextAutofit" minOccurs="0" maxOccurs="1"/>
                        <xsd:element name="scene3d" type="CT_Scene3D" minOccurs="0" maxOccurs="1"/>
                        <xsd:group ref="EG_Text3D" minOccurs="0" maxOccurs="1"/>
                        <xsd:element name="extLst" type="CT_OfficeArtExtensionList" minOccurs="0" maxOccurs="1"/>
                    </xsd:sequence>
                    <xsd:attribute name="rot" type="ST_Angle" use="optional"/>
                    <xsd:attribute name="spcFirstLastPara" type="xsd:boolean" use="optional"/>
                    <xsd:attribute name="vertOverflow" type="ST_TextVertOverflowType" use="optional"/>
                    <xsd:attribute name="horzOverflow" type="ST_TextHorzOverflowType" use="optional"/>
                    <xsd:attribute name="vert" type="ST_TextVerticalType" use="optional"/>
                    <xsd:attribute name="wrap" type="ST_TextWrappingType" use="optional"/>
                    <xsd:attribute name="lIns" type="ST_Coordinate32" use="optional"/>
                    <xsd:attribute name="tIns" type="ST_Coordinate32" use="optional"/>
                    <xsd:attribute name="rIns" type="ST_Coordinate32" use="optional"/>
                    <xsd:attribute name="bIns" type="ST_Coordinate32" use="optional"/>
                    <xsd:attribute name="numCol" type="ST_TextColumnCount" use="optional"/>
                    <xsd:attribute name="spcCol" type="ST_PositiveCoordinate32" use="optional"/>
                    <xsd:attribute name="rtlCol" type="xsd:boolean" use="optional"/>
                    <xsd:attribute name="fromWordArt" type="xsd:boolean" use="optional"/>
                    <xsd:attribute name="anchor" type="ST_TextAnchoringType" use="optional"/>
                    <xsd:attribute name="anchorCtr" type="xsd:boolean" use="optional"/>
                    <xsd:attribute name="forceAA" type="xsd:boolean" use="optional"/>
                    <xsd:attribute name="upright" type="xsd:boolean" use="optional" default="false"/>
                    <xsd:attribute name="compatLnSpc" type="xsd:boolean" use="optional"/>
                </xsd:complexType>
                 */

                writer.writeEmptyElement(QStringLiteral("a:lstStyle")); // <a:lstStyle/>

                writer.writeStartElement(QStringLiteral("a:p"));
                /*
                <xsd:complexType name="CT_TextParagraph">
                    <xsd:sequence>
                        <xsd:element    name="pPr"          type="CT_TextParagraphProperties" minOccurs="0" maxOccurs="1"/>
                        <xsd:group      ref="EG_TextRun"    minOccurs="0" maxOccurs="unbounded"/>
                        <xsd:element    name="endParaRPr"   type="CT_TextCharacterProperties" minOccurs="0"
                        maxOccurs="1"/>
                    </xsd:sequence>
                </xsd:complexType>
                 */

                    // <a:pPr lvl="0">
                    writer.writeStartElement(QStringLiteral("a:pPr"));

                        writer.writeAttribute(QStringLiteral("lvl"), QStringLiteral("0"));

                        // <a:defRPr b="0"/>
                        writer.writeStartElement(QStringLiteral("a:defRPr"));

                            writer.writeAttribute(QStringLiteral("b"), QStringLiteral("0"));

                        writer.writeEndElement();  // a:defRPr

                    writer.writeEndElement();  // a:pPr

                /*
                <xsd:group name="EG_TextRun">
                    <xsd:choice>
                        <xsd:element name="r"   type="CT_RegularTextRun"/>
                        <xsd:element name="br"  type="CT_TextLineBreak"/>
                        <xsd:element name="fld" type="CT_TextField"/>
                    </xsd:choice>
                </xsd:group>
                */

                writer.writeStartElement(QStringLiteral("a:r"));
                /*
                <xsd:complexType name="CT_RegularTextRun">
                    <xsd:sequence>
                        <xsd:element name="rPr" type="CT_TextCharacterProperties" minOccurs="0" maxOccurs="1"/>
                        <xsd:element name="t"   type="xsd:string" minOccurs="1" maxOccurs="1"/>
                    </xsd:sequence>
                </xsd:complexType>
                 */

                    // <a:t>chart name</a:t>
                    writer.writeTextElement(QStringLiteral("a:t"), chartTitle);

                writer.writeEndElement();  // a:r

                writer.writeEndElement();  // a:p

            writer.writeEndElement();  // c:rich

        writer.writeEndElement();  // c:tx

        // <c:overlay val="0"/>
        writer.writeStartElement(QStringLiteral("c:overlay"));
            writer.writeAttribute(QStringLiteral("val"), QStringLiteral("0"));
        writer.writeEndElement();  // c:overlay

    writer.writeEndElement();  // c:title
}
// }}

void ChartPrivate::saveXmlPieChart(QXmlStreamWriter &writer) const
{
    QString name = chartType == Chart::CT_PieChart ? QStringLiteral("c:pieChart") : QStringLiteral("c:pie3DChart");

    writer.writeStartElement(name);

    //Do the same behavior as Excel, Pie prefer varyColors
    writer.writeEmptyElement(QStringLiteral("c:varyColors"));
    writer.writeAttribute(QStringLiteral("val"), QStringLiteral("1"));

    for (int i=0; i<seriesList.size(); ++i)
        saveXmlSer(writer, seriesList[i].data(), i);

    writer.writeEndElement(); //pieChart, pie3DChart
}

void ChartPrivate::saveXmlBarChart(QXmlStreamWriter &writer) const
{
    QString name = chartType == Chart::CT_BarChart ? QStringLiteral("c:barChart") : QStringLiteral("c:bar3DChart");

    writer.writeStartElement(name);

    writer.writeEmptyElement(QStringLiteral("c:barDir"));
    writer.writeAttribute(QStringLiteral("val"), QStringLiteral("col"));

    for ( int i = 0 ; i < seriesList.size() ; ++i )
    {
        saveXmlSer(writer, seriesList[i].data(), i);
    }

    if ( axisList.isEmpty() )
    {
        const_cast<ChartPrivate*>(this)->axisList.append(
                    QSharedPointer<XlsxAxis>(
                        new XlsxAxis( XlsxAxis::T_Cat, XlsxAxis::Bottom, 0, 1, axisNames[XlsxAxis::Bottom] )));

        const_cast<ChartPrivate*>(this)->axisList.append(
                    QSharedPointer<XlsxAxis>(
                        new XlsxAxis( XlsxAxis::T_Val, XlsxAxis::Left, 1, 0, axisNames[XlsxAxis::Left] )));
    }

    //Note: Bar3D have 2~3 axes
    Q_ASSERT(axisList.size()==2 || (axisList.size()==3 && chartType==Chart::CT_Bar3DChart));

    for ( int i = 0 ; i < axisList.size() ; ++i )
    {
        writer.writeEmptyElement(QStringLiteral("c:axId"));
        writer.writeAttribute(QStringLiteral("val"), QString::number(axisList[i]->axisId));
    }

    writer.writeEndElement(); //barChart, bar3DChart
}

void ChartPrivate::saveXmlLineChart(QXmlStreamWriter &writer) const
{
    QString name = chartType==Chart::CT_LineChart ? QStringLiteral("c:lineChart") : QStringLiteral("c:line3DChart");

    writer.writeStartElement(name);

    // writer.writeEmptyElement(QStringLiteral("grouping")); // dev22

    for (int i=0; i<seriesList.size(); ++i)
        saveXmlSer(writer, seriesList[i].data(), i);

    if (axisList.isEmpty())
    {
        const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Cat, XlsxAxis::Bottom, 0, 1, axisNames[XlsxAxis::Bottom] )));
        const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Val, XlsxAxis::Left, 1, 0, axisNames[XlsxAxis::Left] )));
        if (chartType==Chart::CT_Line3DChart)
            const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Ser, XlsxAxis::Bottom, 2, 0)));
    }

    Q_ASSERT((axisList.size()==2||chartType==Chart::CT_LineChart)|| (axisList.size()==3 && chartType==Chart::CT_Line3DChart));

    for (int i=0; i<axisList.size(); ++i) {
        writer.writeEmptyElement(QStringLiteral("c:axId"));
        writer.writeAttribute(QStringLiteral("val"), QString::number(axisList[i]->axisId));
    }

    writer.writeEndElement(); //lineChart, line3DChart
}

void ChartPrivate::saveXmlScatterChart(QXmlStreamWriter &writer) const
{
    const QString name = QStringLiteral("c:scatterChart");

    writer.writeStartElement(name);

    writer.writeEmptyElement(QStringLiteral("c:scatterStyle"));

    for (int i=0; i<seriesList.size(); ++i)
        saveXmlSer(writer, seriesList[i].data(), i);

    if (axisList.isEmpty())
    {
        const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Val, XlsxAxis::Bottom, 0, 1, axisNames[XlsxAxis::Bottom] )));
        const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Val, XlsxAxis::Left, 1, 0, axisNames[XlsxAxis::Left] )));
    }

    Q_ASSERT(axisList.size()==2);

    for (int i=0; i<axisList.size(); ++i)
    {
        writer.writeEmptyElement(QStringLiteral("c:axId"));
        writer.writeAttribute(QStringLiteral("val"), QString::number(axisList[i]->axisId));
    }

    writer.writeEndElement(); //c:scatterChart
}

void ChartPrivate::saveXmlAreaChart(QXmlStreamWriter &writer) const
{
    QString name = chartType==Chart::CT_AreaChart ? QStringLiteral("c:areaChart") : QStringLiteral("c:area3DChart");

    writer.writeStartElement(name);

    // writer.writeEmptyElement(QStringLiteral("grouping")); // dev22

    for (int i=0; i<seriesList.size(); ++i)
        saveXmlSer(writer, seriesList[i].data(), i);

    if (axisList.isEmpty())
    {
        const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Cat, XlsxAxis::Bottom, 0, 1)));
        const_cast<ChartPrivate*>(this)->axisList.append(QSharedPointer<XlsxAxis>(new XlsxAxis(XlsxAxis::T_Val, XlsxAxis::Left, 1, 0)));
    }

    //Note: Area3D have 2~3 axes
    Q_ASSERT(axisList.size()==2 || (axisList.size()==3 && chartType==Chart::CT_Area3DChart));

    for (int i=0; i<axisList.size(); ++i)
    {
        writer.writeEmptyElement(QStringLiteral("c:axId"));
        writer.writeAttribute(QStringLiteral("val"), QString::number(axisList[i]->axisId));
    }

    writer.writeEndElement(); //lineChart, line3DChart
}

void ChartPrivate::saveXmlDoughnutChart(QXmlStreamWriter &writer) const
{
    QString name = QStringLiteral("c:doughnutChart");

    writer.writeStartElement(name);

    writer.writeEmptyElement(QStringLiteral("c:varyColors"));
    writer.writeAttribute(QStringLiteral("val"), QStringLiteral("1"));

    for (int i=0; i<seriesList.size(); ++i)
        saveXmlSer(writer, seriesList[i].data(), i);

    writer.writeStartElement(QStringLiteral("c:holeSize"));
    writer.writeAttribute(QStringLiteral("val"), QString::number(50));

    writer.writeEndElement();
}

void ChartPrivate::saveXmlSer(QXmlStreamWriter &writer, XlsxSeries *ser, int id) const
{
    writer.writeStartElement(QStringLiteral("c:ser"));
    writer.writeEmptyElement(QStringLiteral("c:idx"));
    writer.writeAttribute(QStringLiteral("val"), QString::number(id));
    writer.writeEmptyElement(QStringLiteral("c:order"));
    writer.writeAttribute(QStringLiteral("val"), QString::number(id));

    if (!ser->axDataSource_numRef.isEmpty()) {
        if (chartType == Chart::CT_ScatterChart || chartType == Chart::CT_BubbleChart)
            writer.writeStartElement(QStringLiteral("c:xVal"));
        else
            writer.writeStartElement(QStringLiteral("c:cat"));
        writer.writeStartElement(QStringLiteral("c:numRef"));
        writer.writeTextElement(QStringLiteral("c:f"), ser->axDataSource_numRef);
        writer.writeEndElement();//c:numRef
        writer.writeEndElement();//c:cat or c:xVal
    }

    if (!ser->numberDataSource_numRef.isEmpty()) {
        if (chartType == Chart::CT_ScatterChart || chartType == Chart::CT_BubbleChart)
            writer.writeStartElement(QStringLiteral("c:yVal"));
        else
            writer.writeStartElement(QStringLiteral("c:val"));
        writer.writeStartElement(QStringLiteral("c:numRef"));
        writer.writeTextElement(QStringLiteral("c:f"), ser->numberDataSource_numRef);
        writer.writeEndElement();//c:numRef
        writer.writeEndElement();//c:val or c:yVal
    }

    writer.writeEndElement();//c:ser
}

bool ChartPrivate::loadXmlAxis(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name().endsWith(QLatin1String("Ax")));
    QString name = reader.name().toString();

    XlsxAxis* axis = new XlsxAxis();

    if (name == QLatin1String("valAx")) { axis->type = XlsxAxis::T_Val; }
    else if (name == QLatin1String("catAx")) { axis->type = XlsxAxis::T_Cat; }
    else if (name == QLatin1String("serAx")) { axis->type = XlsxAxis::T_Ser; }
    else { axis->type = XlsxAxis::T_Date; }

    axisList.append(QSharedPointer<XlsxAxis>(axis));

    // TODO: load axis title : name == QLatin1String("valAx")

    while ( !reader.atEnd() )
    {
        reader.readNextStartElement();
        if ( reader.tokenType() == QXmlStreamReader::StartElement )
        {
            if ( reader.name() == QLatin1String("axPos") )
            {
                QXmlStreamAttributes attrs = reader.attributes();
                QStringRef pos = attrs.value(QLatin1String("val"));
                if ( pos == QLatin1String("l") ) axis->axisPos = XlsxAxis::Left;
                else if ( pos == QLatin1String("r") ) axis->axisPos = XlsxAxis::Right;
                else if ( pos == QLatin1String("b") ) axis->axisPos = XlsxAxis::Bottom;
                else if ( pos == QLatin1String("t") ) axis->axisPos = XlsxAxis::Top;
                else axis->axisPos = XlsxAxis::None;
            }
            else if ( reader.name() == QLatin1String("axId") )
            {
                axis->axisId = reader.attributes().value(QLatin1String("val")).toString().toInt();
            }
            else if ( reader.name() == QLatin1String("crossAx") )
            {
                axis->crossAx = reader.attributes().value(QLatin1String("val")).toString().toInt();
            }
        }
        else if ( reader.tokenType() == QXmlStreamReader::EndElement
                  && reader.name() == name )
        {
            break;
        }
    }

    return true;
}


void ChartPrivate::saveXmlAxes(QXmlStreamWriter &writer) const
{
    for ( int i = 0 ; i < axisList.size() ; ++i )
    {
        XlsxAxis* axis = axisList[i].data();

        QString name;
        switch (axis->type)
        {
            case XlsxAxis::T_Cat :  name = QStringLiteral("c:catAx"); break;
            case XlsxAxis::T_Val :  name = QStringLiteral("c:valAx"); break;
            case XlsxAxis::T_Ser :  name = QStringLiteral("c:serAx"); break;
            case XlsxAxis::T_Date : name = QStringLiteral("c:dateAx"); break;
            default: break;
        }

        QString pos;
        switch (axis->axisPos)
        {
            case XlsxAxis::Top :    pos = QStringLiteral("t"); break;
            case XlsxAxis::Bottom : pos = QStringLiteral("b"); break;
            case XlsxAxis::Left :   pos = QStringLiteral("l"); break;
            case XlsxAxis::Right :  pos = QStringLiteral("r"); break;
            default: break; // ??
        }

        writer.writeStartElement(name); // catAx valAx serAx dateAx

        // dev22 {{

        QString strAxisName;
        strAxisName.clear();
        if ( pos == "t" || pos == "b" || pos == "l" || pos == "r" )
        {
            strAxisName = axis->axisNames[ axis->axisPos ];
        }

        if ( name == "c:valAx" &&
             false == strAxisName.isEmpty() )
        {
            writer.writeStartElement("c:title");
             writer.writeStartElement("c:tx");

              writer.writeStartElement("c:rich");
               writer.writeEmptyElement(QStringLiteral("a:bodyPr"));
               writer.writeEmptyElement(QStringLiteral("a:lstStyle"));

               writer.writeStartElement("a:p");

                writer.writeStartElement("a:pPr");
                writer.writeAttribute(QStringLiteral("lvl"), QString::number(0));
                  writer.writeStartElement("a:defRPr");
                  writer.writeAttribute(QStringLiteral("b"), QString::number(0));
                  writer.writeEndElement(); // a:defRPr
                writer.writeEndElement(); // a:pPr

                writer.writeStartElement("a:r");
                writer.writeTextElement(QStringLiteral("a:t"), strAxisName );
                writer.writeEndElement(); // a:r

               writer.writeEndElement(); // a:p

              writer.writeEndElement(); // c:rich
             writer.writeEndElement(); // c:tx

             writer.writeStartElement("c:overlay");
              writer.writeAttribute(QStringLiteral("val"), QString::number(0));
             writer.writeEndElement(); // c:overlay

            writer.writeEndElement(); // c:title
        }
        // }} dev22

        writer.writeEmptyElement(QStringLiteral("c:axId"));
        writer.writeAttribute(QStringLiteral("val"), QString::number(axis->axisId));

        writer.writeStartElement(QStringLiteral("c:scaling"));
            writer.writeEmptyElement(QStringLiteral("c:orientation"));
            writer.writeAttribute(QStringLiteral("val"), QStringLiteral("minMax"));
        writer.writeEndElement();//c:scaling

        writer.writeEmptyElement(QStringLiteral("c:axPos"));
        writer.writeAttribute(QStringLiteral("val"), pos);

        writer.writeEmptyElement(QStringLiteral("c:crossAx"));
        writer.writeAttribute(QStringLiteral("val"), QString::number(axis->crossAx));

        writer.writeEndElement();//name
    }
}

QT_END_NAMESPACE_XLSX

// xlsxchartsheet.cpp

#include "xlsxchartsheet.h"

#include "xlsxchart.h"
#include "xlsxchartsheet_p.h"
#include "xlsxdrawing_p.h"
#include "xlsxdrawinganchor_p.h"
#include "xlsxutility_p.h"
#include "xlsxworkbook.h"

#include <QDir>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QtGlobal>

QT_BEGIN_NAMESPACE_XLSX

ChartsheetPrivate::ChartsheetPrivate(Chartsheet *p, Chartsheet::CreateFlag flag)
    : AbstractSheetPrivate(p, flag)
    , chart(nullptr)
{
}

ChartsheetPrivate::~ChartsheetPrivate()
{
}

/*!
  \class Chartsheet
  \inmodule QtXlsx
  \brief Represent one chartsheet in the workbook.
*/

/*!
 * \internal
 */
Chartsheet::Chartsheet(const QString &name, int id, Workbook *workbook, CreateFlag flag)
    : AbstractSheet(name, id, workbook, new ChartsheetPrivate(this, flag))
{
    setSheetType(ST_ChartSheet);

    if (flag == Chartsheet::F_NewFromScratch) {
        d_func()->drawing = std::make_shared<Drawing>(this, flag);

        DrawingAbsoluteAnchor *anchor =
            new DrawingAbsoluteAnchor(drawing(), DrawingAnchor::Picture);

        anchor->pos = QPoint(0, 0);
        anchor->ext = QSize(9293679, 6068786);

        QSharedPointer<Chart> chart = QSharedPointer<Chart>(new Chart(this, flag));
        chart->setChartType(Chart::CT_BarChart);
        anchor->setObjectGraphicFrame(chart);

        d_func()->chart = chart.data();
    }
}

/*!
 * \internal
 *
 * Make a copy of this sheet.
 */

Chartsheet *Chartsheet::copy(const QString &distName, int distId) const
{
    //: Todo
    Q_UNUSED(distName)
    Q_UNUSED(distId)
    return nullptr;
}

/*!
 * Destroys this workssheet.
 */
Chartsheet::~Chartsheet()
{
}

/*!
 * Returns the chart object of the sheet.
 */
Chart *Chartsheet::chart()
{
    Q_D(Chartsheet);

    return d->chart;
}

void Chartsheet::saveToXmlFile(QIODevice *device) const
{
    Q_D(const Chartsheet);
    d->relationships->clear();

    QXmlStreamWriter writer(device);

    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeDefaultNamespace(
        QStringLiteral("http://schemas.openxmlformats.org/spreadsheetml/2006/main"));
    writer.writeNamespace(
        QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships"),
        QStringLiteral("r"));
    writer.writeStartElement(QStringLiteral("chartsheet"));

    writer.writeStartElement(QStringLiteral("sheetViews"));
    writer.writeEmptyElement(QStringLiteral("sheetView"));
    writer.writeAttribute(QStringLiteral("workbookViewId"), QString::number(0));
    writer.writeAttribute(QStringLiteral("zoomToFit"), QStringLiteral("1"));
    writer.writeEndElement(); // sheetViews

    int idx = d->workbook->drawings().indexOf(d->drawing.get());
    d->relationships->addWorksheetRelationship(
        QStringLiteral("/drawing"), QStringLiteral("../drawings/drawing%1.xml").arg(idx + 1));

    writer.writeEmptyElement(QStringLiteral("drawing"));
    writer.writeAttribute(QStringLiteral("r:id"),
                          QStringLiteral("rId%1").arg(d->relationships->count()));

    writer.writeEndElement(); // chartsheet
    writer.writeEndDocument();
}

bool Chartsheet::loadFromXmlFile(QIODevice *device)
{
    Q_D(Chartsheet);

    QXmlStreamReader reader(device);
    while (!reader.atEnd()) {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement) {
            if (reader.name() == QLatin1String("drawing")) {
                QString rId  = reader.attributes().value(QStringLiteral("r:id")).toString();
                QString name = d->relationships->getRelationshipById(rId).target;

                const auto parts = splitPath(filePath());
                QString path     = QDir::cleanPath(parts.first() + QLatin1String("/") + name);

                d->drawing = std::make_shared<Drawing>(this, F_LoadFromExists);
                d->drawing->setFilePath(path);
            }
        }
    }

    return true;
}

QT_END_NAMESPACE_XLSX

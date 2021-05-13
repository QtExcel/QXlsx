// xlsxworksheet.h

#ifndef XLSXWORKSHEET_H
#define XLSXWORKSHEET_H

#include <QtGlobal>
#include <QObject>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QPointF>
#include <QSharedPointer>
#include <QIODevice>
#include <QDateTime>
#include <QUrl>
#include <QImage>

#include "xlsxabstractsheet.h"
#include "xlsxcell.h"
#include "xlsxcellrange.h"
#include "xlsxcellreference.h"
#include "xlsxcelllocation.h"

class WorksheetTest;

QT_BEGIN_NAMESPACE_XLSX

class DocumentPrivate;
class Workbook;
class Format;
class Drawing;
class DataValidation;
class ConditionalFormatting;
class CellRange;
class RichString;
class Relationships;
class Chart;

class WorksheetPrivate;
class Worksheet : public AbstractSheet
{
    Q_DECLARE_PRIVATE(Worksheet)

private:
    friend class DocumentPrivate;
    friend class Workbook;
    friend class ::WorksheetTest;
    Worksheet(const QString &sheetName, int sheetId, Workbook *book, CreateFlag flag);
    Worksheet *copy(const QString &distName, int distId) const;

public:
    ~Worksheet();

public:

    enum PrintPageOrder
    {
        DownThenOver,
        OverThenDown
    };

    enum PrintOrientation
    {
        Default,
        Landscape,
        Portrait
    };

    enum PrintCellComments
    {
        None,
        AsDisplayed,
        AtEnd
    };

    enum PrintErrors
    {
        Displayed,
        Blank,
        Dash,
        NA
    };

    // pageMargins
    double printLeftMargin() const;
    void setPrintLeftMargin(double margin);
    double printRightMargin() const;
    void setPrintRightMargin(double margin);
    double printTopMargin() const;
    void setPrintTopMargin(double margin);
    double printBottomMargin() const;
    void setPrintBottomMargin(double margin);
    double printHeaderMargin() const;
    void setPrintHeaderMargin(double margin);
    double printFooterMargin() const;
    void setPrintFooterMargin(double margin);

    // pageSetup
    quint32 printPaperSize() const;
    void setPrintPaperSize(quint32 size);
    quint32 printScale() const;
    void setPrintScale(quint32 scale);
    quint32 printFirstPageNumber() const;
    void setPrintFirstPageNumber(quint32 firstPage);
    quint32 printFitToWidth() const;
    void setPrintFitToWidth(quint32 fitToWidth);
    quint32 printFitToHeight() const;
    void setPrintFitToHeight(quint32 fitToHeight);
    PrintPageOrder printPageOrder() const;
    void setPrintPageOrder(PrintPageOrder pageOrder);
    PrintOrientation printOrientation() const;
    void setPrintOrientation(PrintOrientation orientation);
    bool isPrintBlackAndWhite() const;
    void setPrintBlackAndWhite(bool blackAndWhite);
    bool isPrintDraft() const;
    void setPrintDraft(bool isDraft);
    PrintCellComments printCellComments() const;
    void setPrintCellComments(PrintCellComments cellComments);
    bool isPrintUseFirstPageNumber() const;
    void setPrintUseFirstPageNumber(bool useFirstPage);
    PrintErrors printErrors() const;
    void setPrintErrors(PrintErrors errors);
    quint32 printHorizontalDpi() const;
    void setPrintHorizontalDpi(quint32 dpi);
    quint32 printVerticalDpi() const;
    void setprintVerticalDpi(quint32 dpi);
    quint32 printCopies() const;
    void setPrintCopies(quint32 copies);

    bool write(const CellReference &row_column, const QVariant &value, const Format &format=Format());
    bool write(int row, int column, const QVariant &value, const Format &format=Format());

    QVariant read(const CellReference &row_column) const;
    QVariant read(int row, int column) const;

    bool writeString(const CellReference &row_column, const QString &value, const Format &format=Format());
    bool writeString(int row, int column, const QString &value, const Format &format=Format());
    bool writeString(const CellReference &row_column, const RichString &value, const Format &format=Format());
    bool writeString(int row, int column, const RichString &value, const Format &format=Format());

    bool writeInlineString(const CellReference &row_column, const QString &value, const Format &format=Format());
    bool writeInlineString(int row, int column, const QString &value, const Format &format=Format());

    bool writeNumeric(const CellReference &row_column, double value, const Format &format=Format());
    bool writeNumeric(int row, int column, double value, const Format &format=Format());

    bool writeFormula(const CellReference &row_column, const CellFormula &formula, const Format &format=Format(), double result=0);
    bool writeFormula(int row, int column, const CellFormula &formula, const Format &format=Format(), double result=0);

    bool writeBlank(const CellReference &row_column, const Format &format=Format());
    bool writeBlank(int row, int column, const Format &format=Format());

    bool writeBool(const CellReference &row_column, bool value, const Format &format=Format());
    bool writeBool(int row, int column, bool value, const Format &format=Format());

    bool writeDateTime(const CellReference &row_column, const QDateTime& dt, const Format &format=Format());
    bool writeDateTime(int row, int column, const QDateTime& dt, const Format &format=Format());

    // dev67
    bool writeDate(const CellReference &row_column, const QDate& dt, const Format &format=Format());
    bool writeDate(int row, int column, const QDate& dt, const Format &format=Format());

    bool writeTime(const CellReference &row_column, const QTime& t, const Format &format=Format());
    bool writeTime(int row, int column, const QTime& t, const Format &format=Format());

    bool writeHyperlink(const CellReference &row_column, const QUrl &url, const Format &format=Format(), const QString &display=QString(), const QString &tip=QString());
    bool writeHyperlink(int row, int column, const QUrl &url, const Format &format=Format(), const QString &display=QString(), const QString &tip=QString());

    bool addDataValidation(const DataValidation &validation);
    bool addConditionalFormatting(const ConditionalFormatting &cf);

    Cell *cellAt(const CellReference &row_column) const;
    Cell *cellAt(int row, int column) const;

    int insertImage(int row, int column, const QImage &image);
    bool getImage(int imageIndex, QImage& img);
    uint getImageCount();

    Chart *insertChart(int row, int column, const QSize &size);

    bool mergeCells(const CellRange &range, const Format &format=Format());
    bool unmergeCells(const CellRange &range);
    QList<CellRange> mergedCells() const;

    bool setColumnWidth(const CellRange& range, double width);
    bool setColumnFormat(const CellRange& range, const Format &format);
    bool setColumnHidden(const CellRange& range, bool hidden);
    bool setColumnWidth(int colFirst, int colLast, double width);
    bool setColumnFormat(int colFirst, int colLast, const Format &format);
    bool setColumnHidden(int colFirst, int colLast, bool hidden);

    double columnWidth(int column);
    Format columnFormat(int column);
    bool isColumnHidden(int column);

    bool setRowHeight(int rowFirst,int rowLast, double height);
    bool setRowFormat(int rowFirst,int rowLast, const Format &format);
    bool setRowHidden(int rowFirst,int rowLast, bool hidden);

    double rowHeight(int row);
    Format rowFormat(int row);
    bool isRowHidden(int row);

    bool groupRows(int rowFirst, int rowLast, bool collapsed = true);
    bool groupColumns(int colFirst, int colLast, bool collapsed = true);
    bool groupColumns(const CellRange &range, bool collapsed = true);
    CellRange dimension() const;

    bool isWindowProtected() const;
    void setWindowProtected(bool protect);
    bool isFormulasVisible() const;
    void setFormulasVisible(bool visible);
    bool isGridLinesVisible() const;
    void setGridLinesVisible(bool visible);
    bool isRowColumnHeadersVisible() const;
    void setRowColumnHeadersVisible(bool visible);
    bool isZerosVisible() const;
    void setZerosVisible(bool visible);
    bool isRightToLeft() const;
    void setRightToLeft(bool enable);
    bool isSelected() const;
    void setSelected(bool select);
    bool isRulerVisible() const;
    void setRulerVisible(bool visible);
    bool isOutlineSymbolsVisible() const;
    void setOutlineSymbolsVisible(bool visible);
    bool isWhiteSpaceVisible() const;
    void setWhiteSpaceVisible(bool visible);
 	bool setStartPage(int spagen); //add by liufeijin20181028

    QVector<CellLocation> getFullCells(int* maxRow, int* maxCol);

private:
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
};

QT_END_NAMESPACE_XLSX
#endif // XLSXWORKSHEET_H

#include "excelmodel.h"

#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QMetaType>
#include <QBrush>
#include <QColor>
#include <QLocale>
#include <memory>

// QXlsx headers
#include <xlsxdocument.h>
#include <xlsxcellrange.h>
#include <xlsxcell.h>
#include <xlsxformat.h>
#include <xlsxworksheet.h>

using namespace QXlsx;

ExcelModel::ExcelModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

// Detect type of QVariant to determine cell category
ExcelModel::CellType ExcelModel::detectCellType(const QVariant &v)
{
    if (!v.isValid() || v.isNull())
        return CellType::Empty;

    const int typeId = v.metaType().id();

    if (typeId == QMetaType::Int ||
        typeId == QMetaType::LongLong ||
        typeId == QMetaType::UInt ||
        typeId == QMetaType::ULongLong ||
        typeId == QMetaType::Double)
    {
        return CellType::Number;
    }

    if (typeId == QMetaType::QDate ||
        typeId == QMetaType::QTime ||
        typeId == QMetaType::QDateTime)
    {
        return CellType::DateTime;
    }

    if (typeId == QMetaType::Bool)
        return CellType::Bool;

    if (typeId == QMetaType::QString)
        return CellType::String;

    return CellType::Other;
}

bool ExcelModel::loadFromXlsx(const QString &filePath, const QString &sheetName)
{
    Document xlsx(filePath);

    if (!xlsx.isLoadPackage())
    {
        qWarning() << "Failed to load xlsx:" << filePath;
        return false;
    }

    if (!sheetName.isEmpty())
    {
        if (!xlsx.selectSheet(sheetName))
        {
            qWarning() << "Failed to select sheet:" << sheetName;
            return false;
        }
    }

    CellRange range = xlsx.dimension();
    int firstRow = range.firstRow();
    int lastRow = range.lastRow();
    int firstCol = range.firstColumn();
    int lastCol = range.lastColumn();

    if (firstRow == 0 && lastRow == 0 && firstCol == 0 && lastCol == 0)
    {
        // Empty sheet
        beginResetModel();
        m_rowCount = 0;
        m_columnCount = 0;
        m_cells.clear();
        m_spans.clear();
        endResetModel();
        return true;
    }

    int newRowCount = lastRow - firstRow + 1;
    int newColCount = lastCol - firstCol + 1;

    beginResetModel();

    m_rowCount = newRowCount;
    m_columnCount = newColCount;
    m_cells.clear();
    m_cells.resize(m_rowCount);

    // Clear previous spans
    m_spans.clear();

    // 1) Load cell values, types, styles, and number formats
    for (int r = 0; r < m_rowCount; ++r)
    {
        m_cells[r].resize(m_columnCount);

        for (int c = 0; c < m_columnCount; ++c)
        {
            int excelRow = firstRow + r;
            int excelCol = firstCol + c;

            CellData cellData;

            std::shared_ptr<QXlsx::Cell> cellObj = xlsx.cellAt(excelRow, excelCol);
            QVariant v;
            QXlsx::Format fmt;

            if (cellObj)
            {
                // Use readValue() so that date/time cells are returned as QDate/QTime/QDateTime.
                v = cellObj->readValue();
                fmt = cellObj->format();
            }
            else
            {
                // Fallback: read value only
                v = xlsx.read(excelRow, excelCol);
            }

            cellData.value = v;
            cellData.type = detectCellType(v);

            // If format is valid, extract style and number format info
            if (!fmt.isEmpty())
            {
                // Number format info
                cellData.number_format       = fmt.numberFormat();
                cellData.number_format_index = fmt.numberFormatIndex();
                cellData.has_number_format   =
                    (!cellData.number_format.isEmpty() || cellData.number_format_index >= 0);

                // Font
                QFont font = fmt.font();
                cellData.font = font;
                cellData.hasFont = true;

                // Text color
                QColor fontColor = fmt.fontColor();
                if (fontColor.isValid())
                {
                    cellData.foreground = fontColor;
                    cellData.hasForeground = true;
                }

                // Background / fill color
                QColor bg = fmt.patternBackgroundColor();
                if (!bg.isValid())
                {
                    bg = fmt.patternForegroundColor();
                }
                if (bg.isValid())
                {
                    cellData.background = bg;
                    cellData.hasBackground = true;
                }

                // Alignment from Excel if specified
                Qt::Alignment a;

                // Horizontal alignment
                switch (fmt.horizontalAlignment())
                {
                case QXlsx::Format::AlignLeft:
                    a |= Qt::AlignLeft;
                    break;
                case QXlsx::Format::AlignHCenter:
                    a |= Qt::AlignHCenter;
                    break;
                case QXlsx::Format::AlignRight:
                    a |= Qt::AlignRight;
                    break;
                case QXlsx::Format::AlignHJustify:
                case QXlsx::Format::AlignHDistributed:
                    a |= Qt::AlignJustify;
                    break;
                default:
                    break;
                }

                // Vertical alignment
                switch (fmt.verticalAlignment())
                {
                case QXlsx::Format::AlignTop:
                    a |= Qt::AlignTop;
                    break;
                case QXlsx::Format::AlignVCenter:
                    a |= Qt::AlignVCenter;
                    break;
                case QXlsx::Format::AlignBottom:
                    a |= Qt::AlignBottom;
                    break;
                case QXlsx::Format::AlignVJustify:
                case QXlsx::Format::AlignVDistributed:
                    a |= Qt::AlignVCenter;
                    break;
                default:
                    break;
                }

                if (a != Qt::Alignment())
                {
                    cellData.alignment = a;
                    cellData.hasAlignment = true;
                }
            }

            m_cells[r][c] = cellData;
        }
    }

    // 2) Build span info from merged cells (from current worksheet)
    QXlsx::Worksheet *ws = xlsx.currentWorksheet();
    if (ws)
    {
        const QList<CellRange> merged = ws->mergedCells();

        for (const CellRange &cr : merged)
        {
            int top    = cr.firstRow();    // 1-based Excel row
            int left   = cr.firstColumn(); // 1-based Excel column
            int bottom = cr.lastRow();
            int right  = cr.lastColumn();

            int modelRow = top - firstRow;     // convert to 0-based model index
            int modelCol = left - firstCol;

            int rowSpan = bottom - top + 1;
            int colSpan = right - left + 1;

            // Skip invalid ranges outside dimension
            if (modelRow < 0 || modelRow >= m_rowCount ||
                modelCol < 0 || modelCol >= m_columnCount)
            {
                continue;
            }

            SpanInfo si;
            si.row = modelRow;
            si.column = modelCol;
            si.rowSpan = rowSpan;
            si.columnSpan = colSpan;
            m_spans.push_back(si);
        }
    }

    endResetModel();
    return true;
}

// Format numeric value using Excel number format information
QString ExcelModel::formatNumber(const CellData &cell) const
{
    bool ok = false;
    double v = cell.value.toDouble(&ok);
    if (!ok)
        return cell.value.toString();

    QLocale loc;   // use system locale (for decimal separator, grouping, currency symbol)
    QString fmt = cell.number_format;

    // Split into up to 4 sections: positive;negative;zero;text
    QStringList sections = fmt.split(';');
    QString positiveSection = sections.value(0);
    QString negativeSection = sections.value(1);
    QString zeroSection     = sections.value(2);

    // Detect negative formatting hints in negativeSection
    bool negativeParentheses = negativeSection.contains('(') || negativeSection.contains(')');
    bool negativeRedHint =
        negativeSection.contains("[Red]", Qt::CaseInsensitive) ||
        negativeSection.contains("[Color", Qt::CaseInsensitive); // generic color hint

    // Detect decimals from format string (e.g. "0.00", "#,##0.000")
    auto inferDecimals = [&]() -> int {
        QString s = fmt;
        if (!s.isEmpty())
        {
            int dot = s.indexOf('.');
            if (dot >= 0)
            {
                int count = 0;
                for (int i = dot + 1; i < s.size(); ++i)
                {
                    QChar ch = s.at(i);
                    if (ch == '0' || ch == '#')
                        ++count;
                    else
                        break;
                }
                if (count > 0)
                    return count;
            }
        }

        // Fallback from built-in number format id (OOXML spec)
        switch (cell.number_format_index)
        {
        case 0:  // General
        case 1:  // "0"
        case 3:  // "#,##0"
        case 9:  // "0%"
            return 0;

        case 2:  // "0.00"
        case 4:  // "#,##0.00"
        case 10: // "0.00%"
        case 11: // "0.00E+00"
        case 48: // "##0.0E+0"
            return 2;

        default:
            break;
        }
        return 2; // safe default
    };

    bool isPercent = false;
    bool isScientific = false;
    bool isCurrencyOrAccounting = false;

    // Detect by format string
    if (fmt.contains('%'))
        isPercent = true;
    if (fmt.contains('E') || fmt.contains('e'))
        isScientific = true;
    if (fmt.contains('$')
        || fmt.contains(QChar(0x20AC))  // €
        || fmt.contains(QChar(0x00A5))  // ¥
        || fmt.contains(QChar(0x20A9))) // ₩
    {
        isCurrencyOrAccounting = true;
    }

    // Detect by built-in number format index
    switch (cell.number_format_index)
    {
    case 9:  // "0%"
    case 10: // "0.00%"
        isPercent = true;
        break;

    case 11: // "0.00E+00"
    case 48: // "##0.0E+0"
        isScientific = true;
        break;

    case 5:  // currency
    case 6:
    case 7:
    case 8:
    case 37: // accounting-style
    case 38:
    case 39:
    case 40:
        isCurrencyOrAccounting = true;
        break;

    default:
        break;
    }

    int decimals = inferDecimals();

    // Percentage: Excel stores 0.12 for 12%, so multiply by 100.
    if (isPercent)
    {
        double p = v * 100.0;

        // Zero section handling
        if (qFuzzyIsNull(v) && !zeroSection.isEmpty())
        {
            // For simplicity: show "0" or "0%" depending on section
            return loc.toString(0.0, 'f', decimals) + QLatin1Char('%');
        }

        QString base = loc.toString(p, 'f', decimals);
        if (v < 0.0 && negativeParentheses)
        {
            double mag = -p;
            base = loc.toString(mag, 'f', decimals);
            base = QLatin1Char('(') + base + QLatin1Char(')');
        }
        return base + QLatin1Char('%');
    }

    // Scientific notation
    if (isScientific)
    {
        // Zero section handling
        if (qFuzzyIsNull(v) && !zeroSection.isEmpty())
        {
            return loc.toString(0.0, 'e', decimals);
        }

        if (v < 0.0 && negativeParentheses)
        {
            double mag = -v;
            QString base = loc.toString(mag, 'e', decimals);
            return QLatin1Char('(') + base + QLatin1Char(')');
        }

        return loc.toString(v, 'e', decimals);
    }

    // Currency / Accounting
    if (isCurrencyOrAccounting)
    {
        // Zero section handling
        if (qFuzzyIsNull(v) && !zeroSection.isEmpty())
        {
            // In accounting formats, zero is often displayed as "-" or similar.
            // Here we simply show 0 with currency formatting.
            return loc.toCurrencyString(0.0, QString(), decimals);
        }

        if (v < 0.0 && negativeParentheses)
        {
            double mag = -v;
            QString base = loc.toCurrencyString(mag, QString(), decimals);
            return QLatin1Char('(') + base + QLatin1Char(')');
        }

        return loc.toCurrencyString(v, QString(), decimals);
    }

    // Default numeric with fixed decimals (e.g. "0.00" or "#,##0.000")
    if (qFuzzyIsNull(v) && !zeroSection.isEmpty())
    {
        return loc.toString(0.0, 'f', decimals);
    }

    if (v < 0.0 && negativeParentheses)
    {
        double mag = -v;
        QString base = loc.toString(mag, 'f', decimals);
        return QLatin1Char('(') + base + QLatin1Char(')');
    }

    return loc.toString(v, 'f', decimals);
}

int ExcelModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_rowCount;
}

int ExcelModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_columnCount;
}

QVariant ExcelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    const int col = index.column();

    if (row < 0 || row >= m_rowCount || col < 0 || col >= m_columnCount)
        return QVariant();

    const CellData &cell = m_cells[row][col];

    // Display text based on type
    if (role == Qt::DisplayRole)
    {
        switch (cell.type)
        {
        case CellType::Empty:
            return QVariant();

        case CellType::Number:
            if (cell.has_number_format)
                return formatNumber(cell);
            else
                return cell.value.toString();

        case CellType::DateTime:
        {
            if (cell.value.metaType().id() == QMetaType::QDate)
                return cell.value.toDate().toString("yyyy-MM-dd");

            if (cell.value.metaType().id() == QMetaType::QTime)
                return cell.value.toTime().toString("HH:mm:ss");

            return cell.value.toDateTime().toString("yyyy-MM-dd HH:mm:ss");
        }

        case CellType::String:
            return cell.value.toString();

        case CellType::Bool:
            return cell.value.toBool() ? "TRUE" : "FALSE";

        case CellType::Other:
            return cell.value.toString();
        }
    }

    // Alignment: prefer Excel alignment if present, otherwise type-based default
    if (role == Qt::TextAlignmentRole)
    {
        if (cell.hasAlignment)
            return static_cast<int>(cell.alignment);

        Qt::Alignment align;

        switch (cell.type)
        {
        case CellType::Number:
            align = Qt::AlignVCenter | Qt::AlignRight;
            break;

        case CellType::DateTime:
            align = Qt::AlignVCenter | Qt::AlignHCenter;
            break;

        case CellType::String:
            align = Qt::AlignVCenter | Qt::AlignLeft;
            break;

        case CellType::Bool:
            align = Qt::AlignVCenter | Qt::AlignHCenter;
            break;

        case CellType::Empty:
        case CellType::Other:
            align = Qt::AlignVCenter | Qt::AlignLeft;
            break;
        }

        return static_cast<int>(align);
    }

    // Tooltip: show type, raw value, and number format (for debugging)
    if (role == Qt::ToolTipRole)
    {
        QString typeText;

        switch (cell.type)
        {
        case CellType::Empty:   typeText = "Empty"; break;
        case CellType::Number:  typeText = "Number"; break;
        case CellType::DateTime:typeText = "Date/Time"; break;
        case CellType::String:  typeText = "String"; break;
        case CellType::Bool:    typeText = "Boolean"; break;
        case CellType::Other:   typeText = "Other"; break;
        }

        QString fmtInfo;
        if (cell.has_number_format)
        {
            fmtInfo = QString("\nNumber format: %1 (index=%2)")
            .arg(cell.number_format.isEmpty()
                     ? QStringLiteral("<built-in>")
                     : cell.number_format)
                .arg(cell.number_format_index);
        }

        return QString("Type: %1\nRaw Value: %2%3")
            .arg(typeText,
                 cell.value.toString(),
                 fmtInfo);
    }

    // Text color: prefer Excel font color, otherwise simple type-based color.
    // Also, if number format suggests [Red] for negative values, honor that.
    if (role == Qt::ForegroundRole)
    {
        // Negative red hint from number format
        bool negativeRedHint = false;
        if (cell.has_number_format && cell.type == CellType::Number)
        {
            QString fmt = cell.number_format;
            QStringList sections = fmt.split(';');
            QString negativeSection = sections.value(1);
            negativeRedHint =
                negativeSection.contains("[Red]", Qt::CaseInsensitive) ||
                negativeSection.contains("[Color", Qt::CaseInsensitive);

            bool ok = false;
            double v = cell.value.toDouble(&ok);
            if (ok && v < 0.0 && negativeRedHint)
            {
                return QBrush(Qt::red);
            }
        }

        if (cell.hasForeground)
            return QBrush(cell.foreground);

        if (cell.type == CellType::Number)
            return QBrush(QColor(0, 100, 0));   // dark green for numbers

        if (cell.type == CellType::DateTime)
            return QBrush(QColor(0, 0, 160));   // dark blue for dates

        return QVariant();
    }

    // Background color from Excel
    if (role == Qt::BackgroundRole)
    {
        if (cell.hasBackground)
            return QBrush(cell.background);
    }

    // Font: use Excel font if we have it
    if (role == Qt::FontRole)
    {
        if (cell.hasFont)
            return cell.font;
    }

    return QVariant();
}

Qt::ItemFlags ExcelModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

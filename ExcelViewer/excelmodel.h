#ifndef EXCELMODEL_H
#define EXCELMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QVariant>
#include <QFont>
#include <QColor>
#include <QString>
#include <Qt>

class ExcelModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ExcelModel(QObject *parent = nullptr);

    // Load xlsx file and a specific sheet, and rebuild the model
    bool loadFromXlsx(const QString &filePath, const QString &sheetName);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Span info for merged cells (for QTableView::setSpan)
    struct SpanInfo
    {
        int row = 0;        // model row (0-based)
        int column = 0;     // model column (0-based)
        int rowSpan = 1;
        int columnSpan = 1;
    };

    const QVector<SpanInfo> &spans() const { return m_spans; }

private:
    // Cell type enum
    enum class CellType
    {
        Empty,
        Number,
        DateTime,
        String,
        Bool,
        Other
    };

    // Structure that stores value, detected type and style
    struct CellData
    {
        QVariant value;
        CellType type = CellType::Empty;

        QFont font;
        QColor foreground;   // text color
        QColor background;   // fill color

        Qt::Alignment alignment = Qt::Alignment();

        bool hasFont = false;
        bool hasForeground = false;
        bool hasBackground = false;
        bool hasAlignment = false;

        // Number format information (for currency, accounting, percentage, etc.)
        QString number_format;      // raw Excel number format string (e.g. "0.00%", "$#,##0.00")
        int     number_format_index = -1; // built-in number format id
        bool    has_number_format = false;
    };

    int m_rowCount = 0;
    int m_columnCount = 0;

    // Matrix data: [row][column]
    QVector<QVector<CellData>> m_cells;

    // Merged cell spans (model coordinates)
    QVector<SpanInfo> m_spans;

    // Helper: determine Excel cell type from QVariant
    static CellType detectCellType(const QVariant &v);

    // Helper: format numeric cell using Excel number format (currency, percentage, etc.)
    QString formatNumber(const CellData &cell) const;
};

#endif // EXCELMODEL_H

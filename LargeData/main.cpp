#include <QCoreApplication>
#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QDebug>
#include <QDateTime>

#include "xlsxdocument.h"
#include "xlsxformat.h"

using namespace QXlsx;

// Generate deterministic cell content
static QVariant make_cell_value(int row, int col)
{
    // Even columns → integer, odd columns → string
    if (col % 2 == 0) {
        return row * 1000 + col;
    } else {
        return QStringLiteral("R%1C%2").arg(row).arg(col);
    }
}

// Verify several sample cells inside the generated XLSX file
static bool verify_sample_cells(Document &doc, int row_count, int col_count)
{
    QList<QPair<int,int>> samples = {
        {1, 1},
        {row_count / 2, col_count / 2},
        {row_count, col_count}
    };

    for (const auto &rc : samples) {
        int r = qBound(1, rc.first, row_count);
        int c = qBound(1, rc.second, col_count);

        QVariant expected = make_cell_value(r, c);

               // cellAt now returns std::shared_ptr<Cell>
        auto cell = doc.cellAt(r, c);
        if (!cell) {
            qWarning() << "[verify] null cell at" << r << c;
            return false;
        }

        QVariant actual = cell->value();

        if (actual != expected) {
            qWarning() << "[verify] mismatch at" << r << c
                       << "expected =" << expected
                       << "actual =" << actual;
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("LargeData");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription(
        "QXlsx Large Data Example - Generates and reads a large XLSX file."
        );

    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption rows_opt({"r", "rows"},
                                "Number of rows (default: 100000)", "rows", "100000");
    QCommandLineOption cols_opt({"c", "cols"},
                                "Number of columns (default: 10)", "cols", "10");
    QCommandLineOption use_style_opt({"s", "use-style"},
                                     "Apply a simple cell formatting style");
    QCommandLineOption sheet_rows_opt({"S", "sheet-rows"},
                                      "Maximum rows per sheet (0 = single sheet)", "sheetRows", "0");

    parser.addOption(rows_opt);
    parser.addOption(cols_opt);
    parser.addOption(use_style_opt);
    parser.addOption(sheet_rows_opt);
    parser.process(app);

    int row_count = parser.value(rows_opt).toInt();
    int col_count = parser.value(cols_opt).toInt();
    bool use_style = parser.isSet(use_style_opt);
    int sheet_rows = parser.value(sheet_rows_opt).toInt();

    qInfo() << "[LargeData] rows =" << row_count
            << "cols =" << col_count
            << "use_style =" << use_style
            << "sheet_rows =" << sheet_rows;

    QString file_name = QStringLiteral("large_data_%1x%2.xlsx")
                            .arg(row_count)
                            .arg(col_count);

    Document xlsx;

           // Cell formatting (optional)
    Format data_format;
    if (use_style) {
        data_format.setFontName("Calibri");
        data_format.setFontSize(10);
        data_format.setBorderStyle(Format::BorderThin);
    }

    QElapsedTimer timer;

           // ---------------------------------------------------------
           // 1) Write a large dataset
           // ---------------------------------------------------------
    qInfo() << "[LargeData] writing...";
    timer.start();

    int current_sheet_index = 1;
    int current_sheet_row_start = 1;

           // Manage sheet switching when a sheet row limit is provided
    auto ensure_sheet_for_row = [&](int row) {
        if (sheet_rows <= 0) {
            if (xlsx.currentWorksheet() == nullptr)
                xlsx.addSheet("Sheet1");
            return;
        }

        if (xlsx.currentWorksheet() == nullptr) {
            xlsx.addSheet(QStringLiteral("Sheet%1").arg(current_sheet_index));
            current_sheet_row_start = 1;
            return;
        }

        if (row - current_sheet_row_start >= sheet_rows) {
            ++current_sheet_index;
            xlsx.addSheet(QStringLiteral("Sheet%1").arg(current_sheet_index));
            current_sheet_row_start = row;
        }
    };

           // Progress reporting every 0.1%
    const double progress_step = 0.1;
    double next_progress = progress_step;

    for (int row = 1; row <= row_count; ++row) {

        ensure_sheet_for_row(row);

        for (int col = 1; col <= col_count; ++col) {
            QVariant value = make_cell_value(row, col);
            if (use_style)
                xlsx.write(row - current_sheet_row_start + 1, col, value, data_format);
            else
                xlsx.write(row - current_sheet_row_start + 1, col, value);
        }

               // Progress + timestamp (yyyy-MM-dd hh:mm:ss.zzz)
        double percent =
            (static_cast<double>(row) * 100.0) /
            static_cast<double>(row_count);

        if (percent + 1e-9 >= next_progress) {

            QString timestamp =
                QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

            qInfo().noquote()
                << "[" + timestamp + "]"
                << "[LargeData] progress:"
                << QString::number(percent, 'f', 1) + "%";

            while (next_progress <= percent)
                next_progress += progress_step;
        }
    }

    if (!xlsx.saveAs(file_name)) {
        qCritical() << "[LargeData] failed to save file:" << file_name;
        return 1;
    }

    double write_sec = timer.elapsed() / 1000.0;
    qInfo() << "[LargeData] write finished:" << write_sec << "seconds";

           // ---------------------------------------------------------
           // 2) Read file back and verify sample cells
           // ---------------------------------------------------------
    qInfo() << "[LargeData] reading & verifying...";
    timer.restart();

    Document verify_doc(file_name);

    if (!verify_doc.isLoadPackage()) {
        qCritical() << "[LargeData] failed to open file:" << file_name;
        return 1;
    }

    bool verified = verify_sample_cells(verify_doc, row_count, col_count);
    double read_sec = timer.elapsed() / 1000.0;

    qInfo() << "[LargeData] read finished:" << read_sec << "seconds";
    qInfo() << "[LargeData] verify result =" << (verified ? "OK" : "FAILED");
    qInfo() << "[LargeData] output file:" << file_name;

    return verified ? 0 : 1;
}

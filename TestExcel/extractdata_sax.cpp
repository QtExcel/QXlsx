
#include <QtCore>
#include <QtCore/QFileInfo>
#include <QtCore/QRandomGenerator>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QDebug>

#include "xlsxdocument.h"

QXLSX_USE_NAMESPACE

void dump_all_sheets_sax(QXlsx::Document& doc);
void create_xlsx(QString xlsxPath);
QString make_random_ascii_string(int length);

int testReadSax()
{
    const QString xlsx_path = QString::fromLocal8Bit("sample.xlsx");

    create_xlsx(xlsx_path);

    QXlsx::Document doc(xlsx_path);

    // Load and print all sheets and cells, using sax type
    dump_all_sheets_sax(doc);

    // Wait to check RAM usage
    // while(true){
    //    QThread::sleep(std::chrono::seconds{1});
    // }

    QString saveAsXslxName = QString::fromLocal8Bit("sample2.xlsx");
    doc.saveAs(saveAsXslxName);

    return 0;
}


// Generate a random ASCII string (randomized so that compression is not effective)
QString make_random_ascii_string(int length)
{
    QByteArray buf;
    buf.resize(length);

    static const char table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:,.<>/?";

    constexpr int table_len = static_cast<int>(sizeof(table) - 1);

    auto* rng = QRandomGenerator::global();
    for (int i = 0; i < length; ++i) {
        buf[i] = table[rng->bounded(table_len)];
    }

           // Convert to Latin1 (1-byte per character, easy to predict string size)
    return QString::fromLatin1(buf);
}

void create_xlsx(QString xlsx_path)
{
    using namespace QXlsx;

    // const qint64 target_size = 100LL * 1024LL * 1024LL; // 100MB
    const qint64 target_size = 100LL;
    const int rows = 10;
    const int cols = 15;
    const int str_len = 16;

    Document doc; // New document

           // Includes the default sheet. If the size is insufficient, add more sheets while filling.
    int sheet_index = 0;

    while (true) {
        // Select current sheet (first is default, then addSheet and selectSheet for others)
        const QString sheet_name = (sheet_index == 0)
                                       ? doc.sheetNames().value(0)
                                       : QString("Sheet_%1").arg(sheet_index + 1);

        if (sheet_index > 0) {
            doc.addSheet(sheet_name);
            doc.selectSheet(sheet_name);
        } else {
            doc.selectSheet(sheet_name);
        }

               // Fill the sheet: put a unique random string in each cell to increase file size.
               // (sharedStrings table grows, and randomness prevents compression, so file gets bigger)
        for (int r = 1; r <= rows; ++r) {
            for (int c = 1; c <= cols; ++c) {
                // Mix coordinates to make each cell completely unique.
                // (If there are many duplicates, sharedStrings shrinks and compression works well, making the file smaller.)
                const QString payload = QString("R%1C%2_").arg(r).arg(c) + make_random_ascii_string(str_len);
                doc.write(r, c, payload);
            }
        }

               // After saving, check the actual file size
        if (!doc.saveAs(xlsx_path)) {
            // If saving fails, exit immediately (you can change to exception/error handling if needed)
            return;
        }

        const QFileInfo fi(xlsx_path);
        const qint64 file_size = fi.size();

        if (file_size >= target_size) {
            // Target achieved
            break;
        }

               // If still too small, add another sheet and keep growing.
               // Limit the number of sheets to avoid excessive RAM usage.
        ++sheet_index;
        if (sheet_index >= 6) {
            // Create up to 6 sheets max (adjust number if needed)
            break;
        }
    }
}

void dump_all_sheets_sax(QXlsx::Document& doc)
{
    QXlsx::sax_options opt;
    opt.resolve_shared_strings = true;     // If there are many strings, set to false to save more RAM (but sharedString index may be output instead)
    opt.read_formulas_as_text  = true;     // Output formula as string instead of result value (set false if not needed)
    opt.stop_on_empty_sheetdata = false;   // Continue even if sheetData is empty

    const QStringList sheets = doc.sheetNames();
    qInfo() << "sheet count:" << sheets.size();

    for (const QString& sheet_name : sheets) {
        qInfo().noquote() << "\n=== SHEET:" << sheet_name << "===";

        const bool ok = doc.read_sheet_sax(
            sheet_name,
            opt,
            [&](const QXlsx::sax_cell& cell) -> bool {
                qDebug().noquote()
                << QString("%1!R%2C%3 = %4")
                        .arg(cell.sheet_name)
                        .arg(cell.row)
                        .arg(cell.col)
                        .arg(cell.value.toString());
                return true; // continue
            });

        qInfo() << "sheet done:" << sheet_name << "ok=" << ok;
    }
}

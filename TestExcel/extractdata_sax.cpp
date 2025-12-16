
#include <QtCore>
#include <QDebug>

#include "xlsxdocument.h"

QXLSX_USE_NAMESPACE

void dump_all_sheets_sax(QXlsx::Document& doc);

int testReadSax()
{
    const QString xlsx_path = QString::fromLocal8Bit("c:/workspace/sample.xlsx");

    QXlsx::Document doc(xlsx_path);
    dump_all_sheets_sax(doc);

    // Wait for checking RAM size
    // while(true){
    //    QThread::sleep(std::chrono::seconds{1});
    // }

    return 0;
}

void dump_all_sheets_sax(QXlsx::Document& doc)
{
    QXlsx::sax_options opt;
    opt.resolve_shared_strings = true;     // 문자열이 많으면 false로 바꾸면 RAM 더 절약(대신 sharedString 인덱스가 출력될 수 있음)
    opt.read_formulas_as_text  = true;     // 수식은 결과값 대신 수식 문자열로 출력(필요 없으면 false)
    opt.stop_on_empty_sheetdata = false;   // sheetData가 비어도 계속 진행

    const QStringList sheets = doc.sheetNames();
    qInfo() << "sheet count:" << sheets.size();

    for (const QString& sheet_name : sheets) {
        qInfo().noquote() << "\n=== SHEET:" << sheet_name << "===";

        const bool ok = doc.read_sheet_sax(sheet_name, opt,
                                           [&](const QXlsx::sax_cell& cell) -> bool {
            qDebug().noquote()
            << QString("%1!R%2C%3 = %4")
                    .arg(cell.sheet_name)
                    .arg(cell.row)
                    .arg(cell.col)
                    .arg(cell.value.toString());
            return true; // 계속
        });

        qInfo() << "sheet done:" << sheet_name << "ok=" << ok;
    }
}

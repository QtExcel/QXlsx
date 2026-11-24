#include <QCoreApplication>
#include <QDebug>
#include <QString>

#include "xlsxcell.h"
#include "xlsxcellrange.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxworksheet.h"

using namespace QXlsx;

namespace {

bool check(bool condition, const char *description)
{
    if (!condition)
        qCritical() << "FAIL:" << description;
    else
        qInfo() << "PASS:" << description;

    return condition;
}

} // namespace

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    const QString outputPath =
        (argc > 1) ? QString::fromLocal8Bit(argv[1])
                   : QStringLiteral("pr472_feature_test.xlsx");

    bool ok = true;

    // Create a new workbook and configure the features added in the PR.
    {
        Document document;
        Worksheet *sheet = document.currentWorksheet();

        if (!sheet) {
            qCritical() << "FAIL: current worksheet is unavailable";
            return 1;
        }

        // The first row is the title/header, and the rows below are test data.
        sheet->write(1, 1, QStringLiteral("Name"));
        sheet->write(1, 2, QStringLiteral("Value"));
        sheet->write(1, 3, QStringLiteral("Formula"));

        sheet->write(2, 1, QStringLiteral("Editable cell"));
        sheet->write(2, 2, 123.45);

        Format editableFormat;
        editableFormat.setLocked(false);
        sheet->write(2, 3, QStringLiteral("Unlocked"), editableFormat);

        Format hiddenFormulaFormat;
        hiddenFormulaFormat.setLocked(true);
        hiddenFormulaFormat.setHidden(true);
        sheet->write(3, 3, QStringLiteral("Locked and hidden"), hiddenFormulaFormat);

        // Write a date so number/date format save-and-load can also be verified simply.
        Format dateFormat;
        dateFormat.setNumberFormat(QStringLiteral("m/d/yy"));
        sheet->write(4, 1, QDate(2026, 11, 24), dateFormat);

        sheet->freezeFirstRow();
        sheet->setAutoFilter(CellRange(QStringLiteral("A1:C4")));
        sheet->setSheetProtected(true);

        ok &= check(sheet->isFirstRowFrozen(), "first row is frozen before save");
        ok &= check(sheet->autoFilter() == CellRange(QStringLiteral("A1:C4")),
                    "autofilter range is set before save");
        ok &= check(sheet->isSheetProtected(), "sheet protection is enabled before save");

        if (!document.saveAs(outputPath)) {
            qCritical() << "FAIL: could not save" << outputPath;
            return 1;
        }
    }

    // Open the saved file in a new Document and verify that the settings are restored.
    {
        Document loaded(outputPath);
        if (!loaded.load()) {
            qCritical() << "FAIL: could not reload" << outputPath;
            return 1;
        }

        Worksheet *sheet = loaded.currentWorksheet();
        if (!sheet) {
            qCritical() << "FAIL: reloaded worksheet is unavailable";
            return 1;
        }

        ok &= check(sheet->isFirstRowFrozen(), "first-row freeze survives save/load");
        ok &= check(sheet->autoFilter() == CellRange(QStringLiteral("A1:C4")),
                    "autofilter range survives save/load");
        ok &= check(sheet->isSheetProtected(), "sheet protection survives save/load");

        const auto editableCell = sheet->cellAt(2, 3);
        ok &= check(editableCell && !editableCell->format().locked(),
                    "unlocked cell format survives save/load");

        const auto hiddenCell = sheet->cellAt(3, 3);
        ok &= check(hiddenCell && hiddenCell->format().locked()
                        && hiddenCell->format().hidden(),
                    "locked/hidden cell format survives save/load");

        const auto dateCell = sheet->cellAt(4, 1);
        ok &= check(dateCell && dateCell->isDateTime(),
                    "date cell is recognized after save/load");
    }

    if (!ok) {
        qCritical() << "Some checks failed. Test file:" << outputPath;
        return 1;
    }

    qInfo() << "All checks passed. Test file:" << outputPath;
    return 0;
}

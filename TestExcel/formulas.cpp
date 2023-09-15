// formulas.cpp

#include "xlsxcellformula.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxworksheet.h"

#include <QDebug>
#include <QtCore>
#include <QtGlobal>

QXLSX_USE_NAMESPACE

int formula()
{
    //![0]
    Document xlsx;
    //![0]

    //![1]
    xlsx.setColumnWidth(1, 2, 40);
    Format rAlign;
    rAlign.setHorizontalAlignment(Format::AlignRight);
    Format lAlign;
    lAlign.setHorizontalAlignment(Format::AlignLeft);
    xlsx.write("B3", 40, lAlign);
    xlsx.write("B4", 30, lAlign);
    xlsx.write("B5", 50, lAlign);
    xlsx.write("A7", "SUM(B3:B5)=", rAlign);
    xlsx.write("B7", "=SUM(B3:B5)", lAlign);
    xlsx.write("A8", "AVERAGE(B3:B5)=", rAlign);
    xlsx.write("B8", "=AVERAGE(B3:B5)", lAlign);
    xlsx.write("A9", "MAX(B3:B5)=", rAlign);
    xlsx.write("B9", "=MAX(B3:B5)", lAlign);
    xlsx.write("A10", "MIN(B3:B5)=", rAlign);
    xlsx.write("B10", "=MIN(B3:B5)", lAlign);
    xlsx.write("A11", "COUNT(B3:B5)=", rAlign);
    xlsx.write("B11", "=COUNT(B3:B5)", lAlign);

    xlsx.write("A13", "IF(B7>100,\"large\",\"small\")=", rAlign);
    xlsx.write("B13", "=IF(B7>100,\"large\",\"small\")", lAlign);

    xlsx.write("A15", "SQRT(25)=", rAlign);
    xlsx.write("B15", "=SQRT(25)", lAlign);
    xlsx.write("A16", "RAND()=", rAlign);
    xlsx.write("B16", "=RAND()", lAlign);
    xlsx.write("A17", "2*PI()=", rAlign);
    xlsx.write("B17", "=2*PI()", lAlign);

    xlsx.write("A19", "UPPER(\"qtxlsx\")=", rAlign);
    xlsx.write("B19", "=UPPER(\"qtxlsx\")", lAlign);
    xlsx.write("A20", "LEFT(\"ubuntu\",3)=", rAlign);
    xlsx.write("B20", "=LEFT(\"ubuntu\",3)", lAlign);
    xlsx.write("A21", "LEN(\"Hello Qt!\")=", rAlign);
    xlsx.write("B21", "=LEN(\"Hello Qt!\")", lAlign);
    //![1]

    //![2]
    xlsx.addSheet("ArrayFormula");
    Worksheet *sheet = xlsx.currentWorksheet();

    for (int row = 2; row < 20; ++row) {
        sheet->write(row, 2, row * 2); // B2:B19
        sheet->write(row, 3, row * 3); // C2:C19
    }
    sheet->writeFormula("D2", CellFormula("B2:B19+C2:C19", "D2:D19", CellFormula::ArrayType));
    sheet->writeFormula("E2",
                        CellFormula("=CONCATENATE(\"The total is \",D2:D19,\" units\")",
                                    "E2:E19",
                                    CellFormula::ArrayType));
    //![2]

    //![21]
    xlsx.addSheet("SharedFormula");
    sheet = xlsx.currentWorksheet();

    for (int row = 2; row < 20; ++row) {
        sheet->write(row, 2, row * 2); // B2:B19
        sheet->write(row, 3, row * 3); // C2:C19
    }
    sheet->writeFormula("D2", CellFormula("=B2+C2", "D2:D19", CellFormula::SharedType));
    sheet->writeFormula("E2",
                        CellFormula("=CONCATENATE(\"The total is \",D2,\" units\")",
                                    "E2:E19",
                                    CellFormula::SharedType));

    //![21]

    //![3]
    xlsx.saveAs("formula1.xlsx");
    //![3]

    // Make sure that read/write works well.
    Document xlsx2("formula1.xlsx");
    Worksheet *sharedFormulaSheet = dynamic_cast<Worksheet *>(xlsx2.sheet("SharedFormula"));
    for (int row = 2; row < 20; ++row) {
        qDebug() << sharedFormulaSheet->read(row, 4);
    }

    xlsx2.saveAs("formula2.xlsx");

    return 0;
}

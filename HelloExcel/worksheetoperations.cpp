#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxabstractsheet.h"

QTXLSX_USE_NAMESPACE

int main()
{
    //![Create a xlsx file]
    Document xlsx;

    for (int i=1; i<20; ++i) {
        for (int j=1; j<15; ++j)
            xlsx.write(i, j, QString("R %1 C %2").arg(i).arg(j));
    }
    xlsx.addSheet();
    xlsx.write(2, 2, "Hello Qt Xlsx");
    xlsx.addSheet();
    xlsx.write(3, 3, "This will be deleted...");

    xlsx.addSheet("HiddenSheet");
    xlsx.currentSheet()->setHidden(true);
    xlsx.write("A1", "This sheet is hidden.");

    xlsx.addSheet("VeryHiddenSheet");
    xlsx.sheet("VeryHiddenSheet")->setSheetState(AbstractSheet::SS_VeryHidden);
    xlsx.write("A1", "This sheet is very hidden.");

    xlsx.save();//Default name is "Book1.xlsx"
    //![Create a xlsx file]

    Document xlsx2("Book1.xlsx");
    //![add_copy_move_delete]
    xlsx2.renameSheet("Sheet1", "TheFirstSheet");

    xlsx2.copySheet("TheFirstSheet", "CopyOfTheFirst");

    xlsx2.selectSheet("CopyOfTheFirst");
    xlsx2.write(25, 2, "On the Copy Sheet");

    xlsx2.deleteSheet("Sheet3");

    xlsx2.moveSheet("Sheet2", 0);
    //![add_copy_move_delete]

    //![show_hidden_sheets]
    xlsx2.sheet("HiddenSheet")->setVisible(true);
    xlsx2.sheet("VeryHiddenSheet")->setVisible(true);
    //![show_hidden_sheets]

    xlsx2.saveAs("Book2.xlsx");
    return 0;
}

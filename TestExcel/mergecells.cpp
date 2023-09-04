// mergecells.cpp

#include "xlsxdocument.h"
#include "xlsxformat.h"

#include <QDebug>
#include <QtGlobal>

QXLSX_USE_NAMESPACE

int mergecells()
{
    Document xlsx;

    //![0]
    Format format;
    format.setHorizontalAlignment(Format::AlignHCenter);
    format.setVerticalAlignment(Format::AlignVCenter);
    //![0]

    //![1]
    xlsx.write("B4", "Hello Qt!");
    xlsx.mergeCells("B4:F6", format);
    xlsx.write("B8", 1);
    xlsx.mergeCells("B8:C21", format);
    xlsx.write("E8", 2);
    xlsx.mergeCells("E8:F21", format);
    //![1]

    //![2]

    // mergedCells

    //![2]

    xlsx.saveAs("mergecells.xlsx");

    return 0;
}

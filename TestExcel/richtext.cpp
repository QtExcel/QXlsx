// richtext.cpp

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <QtCore>
#include <QtGlobal>

int richtext()
{
    //![0]
    QXlsx::Document xlsx;
    //![0]

    //![1]
    QXlsx::Format blue;
    blue.setFontColor(Qt::blue);
    QXlsx::Format red;
    red.setFontColor(Qt::red);
    red.setFontSize(15);
    QXlsx::Format bold;
    bold.setFontBold(true);

    QXlsx::RichString rich;
    rich.addFragment("Hello ", blue);
    rich.addFragment("Qt ", red);
    rich.addFragment("Xlsx", bold);
    xlsx.write("B2", rich);

    xlsx.workbook()->setHtmlToRichStringEnabled(true);
    xlsx.write("B4", "<b>Hello</b> <font color=\"red\">Qt</font> <i>Xlsx</i>");

    xlsx.write("B6", "<font color=\"red\"><b><u><i>Qt Xlsx</i></u></b></font>");

    //![1]

    //![2]
    xlsx.saveAs("richtext1.xlsx");
    //![2]

    QXlsx::Document("richtext1.xlsx");
    xlsx.saveAs("richtext2.xlsx");

    return 0;
}

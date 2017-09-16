#include <QtCore>
#include "xlsxdocument.h"

int main()
{
    //![0]
    QXlsx::Document xlsx;
    //![0]

    //![1]
    xlsx.write("A1", "http://qt-project.org");
    xlsx.write("A2", "http://qt-project.org/wiki#0f68b904e33d9ac04605aecc958bcf52");
    xlsx.write("A3", "mailto:info@qt-project.org");
    xlsx.write("A4", "file:///C:/User/test/abc.txt");
    //![1]

    //![2]
    xlsx.save();
    //![2]

    QXlsx::Document xlsx2("Book1.xlsx");
    xlsx2.saveAs("Book2.xlsx");

    return 0;
}

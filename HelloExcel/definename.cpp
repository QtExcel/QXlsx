#include <QtCore>
#include "xlsxdocument.h"

QTXLSX_USE_NAMESPACE

int main()
{
    //![0]
    Document xlsx;
    for (int i=1; i<=10; ++i) {
        xlsx.write(i, 1, i);
        xlsx.write(i, 2, i*i);
        xlsx.write(i, 3, i*i*i);
    }
    //![0]
    //![1]
    xlsx.defineName("MyCol_1", "=Sheet1!$A$1:$A$10");
    xlsx.defineName("MyCol_2", "=Sheet1!$B$1:$B$10", "This is comments");
    xlsx.defineName("MyCol_3", "=Sheet1!$C$1:$C$10", "", "Sheet1");
    xlsx.defineName("Factor", "=0.5");
    //![1]
    //![2]
    xlsx.write(11, 1, "=SUM(MyCol_1)");
    xlsx.write(11, 2, "=SUM(MyCol_2)");
    xlsx.write(11, 3, "=SUM(MyCol_3)");
    xlsx.write(12, 1, "=SUM(MyCol_1)*Factor");
    xlsx.write(12, 2, "=SUM(MyCol_2)*Factor");
    xlsx.write(12, 3, "=SUM(MyCol_3)*Factor");
    //![2]

    xlsx.save();
    return 0;
}

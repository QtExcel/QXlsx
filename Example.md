# QXlsx Examples

## [HelloWorld](https://github.com/QtExcel/QXlsx/tree/master/HelloWorld)

- Hello world example

```cpp
// main.cpp

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDebug>

#include <iostream>
using namespace std;

// [0] include QXlsx headers 
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // [1]  Writing excel file(*.xlsx)
    QXlsx::Document xlsxW;
    xlsxW.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsxW.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'

    // [2] Reading excel file(*.xlsx)
    Document xlsxR("Test.xlsx"); 
    if (xlsxR.load()) // load excel file
    { 
        int row = 1; int col = 1;
        Cell* cell = xlsxR.cellAt(row, col); // get cell pointer.
        if ( cell != NULL )
        {
            QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
            qDebug() << var; // display value. it is 'Hello Qt!'.
        }
    }

    return 0;
}
```

## [TestExcel](https://github.com/QtExcel/QXlsx/tree/master/TestExcel)

- :zap: Basic examples (based on QtXlsx examples)
    - calendar
    - chart
    - chart sheet
    - data validation
    - demo
    - document property
    - extract data
    - formula
    - hyperlink
    - image
    - merge cells
    - number format
    - page margins
    - read style
    - richtext
    - row column
    - style
    - worksheet operations

![](markdown.data/testexcel.png)

## [HelloAndroid](https://github.com/QtExcel/QXlsx/tree/master/HelloAndroid)

- See 'HelloAndroid' example using QML and native C++.

- Qt 5.11.1 / QtCreator 4.6.2 / gcc 4.9 / Android x86 (using Emulator [Android Oreo]) / Android Studio 3.1.3 (Android NDK 17.1)

![](markdown.data/android.jpg)

## [WebServer](https://github.com/QtExcel/QXlsx/tree/master/WebServer)
- Load xlsx file and display on Web.
- Connect to `http://127.0.0.1:3001`
- C++ 14 is required. Old compilers is not supported.(based on recurse)

![](markdown.data/webserver.png)

## [ShowConsole](https://github.com/QtExcel/QXlsx/tree/master/ShowConsole)
- Load xlsx file and display in console.
  - [Usage] ShowConsole *.xlsx
- C++ 11 is required. Old compilers is not supported. (based on libfort)

![](markdown.data/show-console.jpg)

## [ReadColor](https://github.com/QtExcel/QXlsx/tree/master/ReadColor) 
- Read cell color

![](markdown.data/read-color.jpg)

## XlsxFactory 
- Load xlsx file and display on Qt widgets. 
- Moved to personal repository for advanced app.

![](markdown.data/copycat.png)
![](markdown.data/copycat2.jpg)

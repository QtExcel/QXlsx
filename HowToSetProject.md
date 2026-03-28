
## How to setup QXlsx project

> *Read this in other languages: [English](HowToSetProject.md), :kr: [한국어](HowToSetProject.ko.md), :cn: [简体中文](HowToSetProject.zh-CN.md)*

- Here's an easy way to apply QXlsx.
- This works only with qmake, for cmake look at [the other doc](HowToSetProject-cmake.md).
- Describes when to apply to Windows.
- The method of applying it on Linux or Mac is similar, and I will write help if there is an additional request.
- * Hi! I'm j2doll. My native language is not English and my English is not fluent. Please understand. :-)

## Steps to set

:one: Clone source code from github

```sh
git clone https://github.com/j2doll/QXlsx.git
```

![](markdown.data/01.jpg)

<br /><br />

:two: Execute QtCreator

![](markdown.data/02.jpg)

* If you don't know use QtCreator, see Qt Company site. [https://www.qt.io/qt-features-libraries-apis-tools-and-ide/](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/)

<br /><br />

:three: Create your own Qt Project.

![](markdown.data/03.jpg)

<br /><br />

:four: Sample is console application.

![](markdown.data/04.jpg)

<br /><br />

:five: Set project name. Current project name is HelloQXlsx.  

![](markdown.data/05.jpg)

<br /><br />

:six: HelloQXlsx project has been created.

![](markdown.data/06.jpg)

<br /><br />

:seven: Current directory for project

![](markdown.data/07.jpg)

<br /><br />

:eight: Copy QXlsx code to your app project  

![](markdown.data/08.jpg)

```cmd
xcopy c:\workspace\github\QXlsx\QXlsx c:\workspace\HelloQXlsx /s /e
```

<br /><br />

:nine: Current directories and files for project

![](markdown.data/09.jpg)

<br /><br />

:keycap_ten: Append code for QXlxs library on your Qt project(*.pro)

![](markdown.data/10.jpg)

```qmake
# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)
```

<br /><br />

:one::one: Set header files and namespace for sample. Then append hello world code.

![](markdown.data/11.jpg)

```cpp
// main.cpp

#include <QCoreApplication>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsx.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'

    return 0;
    // return a.exec();
}
```

<br /><br />

:one::two: Build and Run a project

![](markdown.data/12.jpg)

<br /><br />

:one::three: A execute file(*.exe) and a excel file(xlsx) is created.

![](markdown.data/13.jpg)

<br /><br />




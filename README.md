# QXlsx

> *Read this in other languages: [English](README.md), [한국어](README.ko.md)*

![](markdown.data/IMG_0016.PNG)

## Excel reader/writer library
* QXlsx is excel file(*.xlsx) reader/writer library.
  * Because QtXlsx is no longer supported, I created a new project that os based on QtXlsx.
  * Development language of QXlsx is C++.
  * It is written for static library using Qt 5.x. (2017)
  
<img src="./markdown.data/qt-64.png" width="64" height="64" /> <img src="./markdown.data/XLSX-64.png" width="64" height="64" /> <img src="./markdown.data/cxx.pngg" width="64" height="64" />
  
## License
* QXlsx is licensed under the MIT License https://opensource.org/licenses/MIT
* QtXlsx License (See Debao Zhang (2014) site) : https://github.com/dbzhang800/QtXlsxWriter
* Qt License (See Qt Company site) : https://www.qt.io/

## Sample (Hello excel)

### Writing excel file
```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
xlsx.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'
```

### Reading excel file
```cpp
Document xlsx("Test.xlsx"); // load excel file
if (!xlsx.isLoadPackage()) { // failed to load excel 		
	return;
}
int row = 1; int col = 2;
Cell* cell = xlsx.cellAt(row, col); // get cell pointer. (row is 1. column is 2.)
if ( cell == NULL )
	continue; // cell vaule is not set
QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
qint32 styleNo = cell->styleNumber(); // read cell style number
if ( styleNo >= 0 )
	qDebug() << row << " " << var << " , style:" << styleNo;
else
	qDebug() << row << " " << var;
```

## How to build
* Install Qt 5 from [Qt Company](https://www.qt.io) (2017-)
* Clone github source code
```sh
  git clone https://github.com/j2doll/QXlsx.git
```
* Build QXlsx project 
```sh
  cd QXlsx
  qmake QXlsx.pro
  make
```
* Build HelloExample
```sh
  cd HelloExcel
    Fix HelloExcel.pro for your own build environment 
  qmake HelloExcel.pro
  make
```
* Run HelloExample
```sh
 ./HelloExample
```

## Test environment
Test Environment is below.
- 5.9.2 (MingW/Windows 32bit)
- Qt 5.9.1 (Visual Studio 2017/Windows 64bit)
- Qt 5.9.1 (Visual Studio 2017/Windows 32bit)
- Qt 5.9.1 (MingW/Windows 32bit)
- Qt 5.9.1 (Ubuntu 16/Linux x64)
- Qt 5.6.0 (MingW/Windows 32bit)
- Qt 5.5.1 (MingW/Windows 32bit)
- Qt 5.5.0 (Ubuntu 17/Linux i686)
- Qt 5.2.0 (Ubuntu 14/Linux x64)
- Qt 5.0.1 (MingW/Windows 32bit)

## To Test
The following tests should be performed.
- Microsoft Excel 
- Google Spreadsheet
- LibreOffice Calc Spreasheet

![](markdown.data/LibreOffice-Google-XLSX.png)

## Contacts
* [j2doll@gmail.com](mailto:j2doll@gmail.com)
* Hi! I'm j2doll. My native language is not English and my English is not fluent. Please, use EASY English. :-)

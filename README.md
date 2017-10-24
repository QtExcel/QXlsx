# QXlsx

> *Read this in other languages: [English](README.md), [한국어](README.ko.md)*

![](etc/IMG_0016.PNG)

## Excel reader/writer library

* QXlsx is excel file(*.xlsx) reader/writer library.
* It is written for static library using Qt 5.

## License
* QXlsx is licensed under the GPL License https://www.gnu.org/licenses/gpl-3.0.en.html
* Clone of QtXlsx Debao Zhang(2014) : https://github.com/dbzhang800/QtXlsxWriter
* Qt License (see Qt Company site) : https://www.qt.io/

## Hello excel
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
* see https://github.com/j2doll/QXlsx/wiki

## Test environment
* see https://github.com/j2doll/QXlsx/wiki/Test-Environment

## To test
The following tests should be performed.
- testing Microsoft Office(Excel) Online
- testing Google Docs(Spreadsheet)
- testing LibreOffice

## Contact
* [j2doll@gmail.com](mailto:j2doll@gmail.com)
* Hi! My native language is not English. My English is not fluent. Please use EASY English. :-)

# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

<p align="center"><img src="https://github.com/j2doll/QXlsx/raw/master/markdown.data/QXlsx2.jpg"></p>

![](markdown.data/qxlsx-badge1.png)

- QXlsx is excel file(*.xlsx) reader/writer library.
- Because QtXlsx is no longer supported(2014), I created a new project that is based on QtXlsx. (2017-)
- Development language of QXlsx is C++. (with Qt)
- You don't need to use static library or dynamic shared object using QXlsx.

## How to use
- See samples 
	- TestExcel : basic samples based on QtXlsx samples
	- HelloAndroid : read xlsx on Android
	- SpreadsheetExample : simple sample

## Sample (Hello excel)

### :one: Writing excel file(*.xlsx)

```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
xlsx.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'
```

### :two: Reading excel file(*.xlsx)

```cpp
Document xlsx("Test.xlsx"); // load excel file
if (!xlsx.isLoadPackage()) { 
	return; // failed to load excel
}
int row = 1; int col = 2;
Cell* cell = xlsx.cellAt(row, col); // get cell pointer. (row is 1. column is 2.)
if ( cell == NULL )
	continue; // cell vaule is not set
QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
qDebug() << var; // display value
```

## How to set up
- See [How to setup QXlsx project](HowToSetProject.md)

## Test environment

- See [Tested environments](TestEnv.md)

## To Test
- The following tests should be performed. 
	- Microsoft Excel, Google Spreadsheet, LibreOffice Calc Spreasheet
- Unicode test (filename :cloud:, filepath :cloud:, data value :sunny:)

## To Upgrade
- Develop the encryption function of xlsx

## License and links
- ![](markdown.data/mit-license.png) QXlsx is under MIT License. [https://github.com/j2doll/QXlsx](https://github.com/j2doll/QXlsx)
- ![](markdown.data/mit-license.png) QtXlsx License : See Debao Zhang (2014) site. [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
- Qt License (See Qt Company site) [https://www.qt.io/](https://www.qt.io/) 

mark: - 1:fix the problems that pictures，footer,header,pagesetting losing when save the excel file by QXlsx.
      - 2:Add a method for changing the picture in shape 
      - 3:Add a methode for changing starting page number for each sheet (excel rev. 2010 above)
      -
       - to be fixed  shareformula losing after writing excel.

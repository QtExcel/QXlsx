# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

<p align="center"><img src="https://github.com/j2doll/QXlsx/raw/master/markdown.data/QXlsx-Desktop.png"></p>

Linux | Windows
----- | -------
[![Build Status](https://travis-ci.com/j2doll/QXlsx.svg?branch=master)](https://travis-ci.com/j2doll/QXlsx) | [![Build status](https://ci.appveyor.com/api/projects/status/jkod8257gg66vm6e?svg=true)](https://ci.appveyor.com/project/j2doll/qxlsx)

- QXlsx is excel file(*.xlsx) reader/writer library.
- Because QtXlsx is no longer supported(2014), I created a new project that is based on QtXlsx. (2017-)
- Development language of QXlsx is C++. (with Qt)
- You don't need to use static library or dynamic shared object using QXlsx.

## How to use
- See [examples](Example.md)
	- HelloWorld : Hello world example (The most basic structure)
	- TestExcel : basic samples based on QtXlsx samples
	- HelloAndroid : read xlsx on Android using QML
	- Copycat : load xlsx file and display on widget. print xlsx file. (TODO: save xlsx)
	- WebServer : load xlsx and display to web (`http://127.0.0.1:3001`)

## How to set up (Installation)

- See [how to setup QXlsx project](HowToSetProject.md)	
		
## Example (Hello excel)

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

## Tested environment

- See [tested environments](TestEnv.md)

## To Do

- [To test](ToTest.md)

- [What to upgrade](ToUpgrade.md).

## Contributions

- See [contributors](https://github.com/j2doll/QXlsx/graphs/contributors).

## License and links
- QXlsx is under MIT license. [https://github.com/j2doll/QXlsx](https://github.com/j2doll/QXlsx)
- QtXlsx is under MIT license. [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
- Qt-Table-Printer is under BSD 3-Clause license. [https://github.com/T0ny0/Qt-Table-Printer](https://github.com/T0ny0/Qt-Table-Printer) 
- recurse is under MIT license. [https://github.com/pkoretic/recurse](https://github.com/pkoretic/recurse)
- Qt is under LGPL v3 license or Commercial license. [https://www.qt.io/](https://www.qt.io/) 

## :email: Contact
- Hi! I'm j2doll (aka Jay Two). My name is Korean and it is difficult for foreigners to pronounce it. Call me j2doll.
- Leave me a issue. [https://github.com/j2doll/QXlsx/issues](https://github.com/j2doll/QXlsx/issues)
	- If you are interested in participating in the project, please contact us by issue.
	- My native language is not English and my English is not fluent. Please, use EASY English. :-)
- If you would like to translate README.md into your native language, please contact me.
	- You can either raise an issue or use a pull request. (such as README.ko.md)
	
## Similar projects

### :star: <b>Qxlnt</b> [https://github.com/j2doll/Qxlnt](https://github.com/j2doll/Qxlnt)

<p align="center"><img src="https://github.com/j2doll/Qxlnt/raw/master/markdown-data/Concept-QXlnt.jpg"></p>

- Qxlnt is a helper project that allows xlnt to be used in Qt.
- xlnt is a excellent C++ library for using xlsx Excel files. :+1:
- I was looking for a way to make it easy to use in Qt. Of course, cmake is compatible with Qt, but it is not convenient to use. So I created Qxlnt.

### :star: <b>Qlibxlsxwriter</b> [https://github.com/j2doll/Qlibxlsxwriter](https://github.com/j2doll/Qlibxlsxwriter)

<p align="center"><img src="https://github.com/j2doll/Qlibxlsxwriter/raw/master/markdown.data/logo.png"></p>

- Qlibxlsxwriter is a helper project that allows libxlsxwriter to be used in Qt.
- libxlsxwriter is a C library for creating Excel XLSX files.

### :star: <b>QSimpleXlsxWriter</b> [https://github.com/j2doll/QSimpleXlsxWriter](https://github.com/j2doll/QSimpleXlsxWriter)

- Use SimpleXlsxWriter in Qt.
- SimpleXlsxWriter is C++ library for creating XLSX files for MS Excel 2007 and above.

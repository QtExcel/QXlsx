# QXlsx

> *Read this in other languages: [English](README.md), :kr: [Korean](README.ko.md), :ru: [Russian](README.RU.md), :cn: [Simplified Chinese](README.zh-CN.md)*

<p align="center"><img src="https://raw.githubusercontent.com/QtExcel/QXlsx/master/markdown.data/QXlsx-Desktop.png"></p>

- `QXlsx` is excel file(`*.xlsx`) reader/writer library.
  - Because QtXlsxWriter is no longer supported, I created a new project that is based on QtXlsx. (2017-)
- Development language of QXlsx is C++. (with Qt)
- You don't need to use static library or dynamic shared object using QXlsx.
  - You can also use it as a static library.

## How to use
- See [examples](Example.md)
- See [wiki](https://github.com/QtExcel/QXlsx/wiki)
- See [FAQ](https://github.com/QtExcel/QXlsx/wiki/FAQ)

## How to set up (Installation)

- See [how to setup QXlsx project (qmake)](HowToSetProject.md)	
- See [how to setup QXlsx project (cmake)](HowToSetProject-cmake.md)	

## Github Actions

[![qmake](https://github.com/QtExcel/QXlsx/actions/workflows/windows.yml/badge.svg)](https://github.com/QtExcel/QXlsx/actions/workflows/windows.yml) [![CMake](https://github.com/QtExcel/QXlsx/actions/workflows/cmake.yml/badge.svg)](https://github.com/QtExcel/QXlsx/actions/workflows/cmake.yml)

- See [tested environments](https://github.com/QtExcel/QXlsx/actions) for more information.

## Contributions

<a href="https://github.com/QtExcel/QXlsx/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=QtExcel/QXlsx" />
</a>

## License and links
- QXlsx is under MIT license. [https://github.com/QtExcel/QXlsx](https://github.com/QtExcel/QXlsx)
- Thank you for creating the following amazing projects. :+1:
  - Qt is under LGPL v3 license or Commercial license. [https://www.qt.io/](https://www.qt.io/) 
  - QtXlsxWriter is under MIT license. :+1: [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
  - Qt-Table-Printer is under BSD 3-Clause license. [https://github.com/T0ny0/Qt-Table-Printer](https://github.com/T0ny0/Qt-Table-Printer) 
  - recurse is under MIT license. [https://github.com/pkoretic/recurse](https://github.com/pkoretic/recurse)
  - libfort is under MIT license. [https://github.com/seleznevae/libfort](https://github.com/seleznevae/libfort)
  - colorprintf is under MIT license. [https://github.com/VittGam/colorprintf](https://github.com/VittGam/colorprintf)
  - HelloActions-Qt is under MIT license. [https://github.com/jaredtao/HelloActions-Qt](https://github.com/jaredtao/HelloActions-Qt)  

## :email: Contact
- Leave me a issue. [https://github.com/QtExcel/QXlsx/issues](https://github.com/QtExcel/QXlsx/issues)
	- If you are interested in participating in the project, please contact us by issue.
	- My native language is not English and my English is not fluent. Please, use EASY English. :-)
- If you would like to translate README.md into your native language, please contact me.
	- You can either raise an issue or use a pull request. (such as README.ko.md)
	
## Similar projects

### :star: <b>Qxlnt</b> [https://github.com/QtExcel/Qxlnt](https://github.com/QtExcel/Qxlnt)

<p align="center"><img src="https://github.com/QtExcel/Qxlnt/raw/master/markdown-data/Concept-QXlnt.jpg"></p>

- Qxlnt is a helper project that allows xlnt to be used in Qt.
- xlnt is a excellent C++ library for using xlsx Excel files.
- I was looking for a way to make it easy to use in Qt. Of course, cmake is compatible with Qt, but it is not convenient to use. So I created Qxlnt.

### :star: <b>Qlibxlsxwriter</b> [https://github.com/QtExcel/Qlibxlsxwriter](https://github.com/QtExcel/Qlibxlsxwriter)

<p align="center"><img src="https://github.com/QtExcel/Qlibxlsxwriter/raw/master/markdown.data/logo.png"></p>

- Qlibxlsxwriter is a helper project that allows libxlsxwriter to be used in Qt.
- libxlsxwriter is a C library for creating Excel XLSX files.

### :star: <b>QSimpleXlsxWriter</b> [https://github.com/QtExcel/QSimpleXlsxWriter](https://github.com/QtExcel/QSimpleXlsxWriter)

- Use SimpleXlsxWriter in Qt.
- SimpleXlsxWriter is C++ library for creating XLSX files for MS Excel 2007 and above.

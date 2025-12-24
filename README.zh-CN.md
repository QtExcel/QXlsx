# QXlsx

> *以其他语言阅读: [English](README.md), :cn: [简体中文](README.zh-CN.md)*

<p align="center"><img src="https://raw.githubusercontent.com/QtExcel/QXlsx/master/markdown.data/QXlsx-Desktop.png"></p>

- QXlsx 是 Excel 文件（`*.xlsx`）的读取/写入库。
  - 由于 QtXlsxWriter 不再受支持，我创建了一个基于 QtXlsx 的新项目。 (2017-)
- QXlsx 使用 C++（结合 Qt 框架）开发。
- QXlsx 可以直接集成到项目中，无需依赖额外的静态库或动态库。
  - 您也可以将其用作静态库。

## 如何使用
- 查看 [示例](Example.md)
- 查看 [Wiki 文档](https://github.com/QtExcel/QXlsx/wiki)
- 查看 [常见问题解答](https://github.com/QtExcel/QXlsx/wiki/FAQ)

## 如何设置（安装）

- 查看 [如何设置 QXlsx 项目 (qmake)](HowToSetProject.md)	
- 查看 [如何设置 QXlsx 项目 (cmake)](HowToSetProject-cmake.md)	

## Github Actions

[![qmake](https://github.com/QtExcel/QXlsx/actions/workflows/windows.yml/badge.svg)](https://github.com/QtExcel/QXlsx/actions/workflows/windows.yml) [![CMake](https://github.com/QtExcel/QXlsx/actions/workflows/cmake.yml/badge.svg)](https://github.com/QtExcel/QXlsx/actions/workflows/cmake.yml)

- 请参阅 [测试环境](https://github.com/QtExcel/QXlsx/actions) 以了解更多信息。

## 贡献

<a href="https://github.com/QtExcel/QXlsx/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=QtExcel/QXlsx" />
</a>

## ❤️ 感谢以下优秀项目的支持
- QXlsx 遵循 MIT 许可证。 [https://github.com/QtExcel/QXlsx](https://github.com/QtExcel/QXlsx)
- 感谢您创建以下精彩的项目。 :+1:
  - Qt 采用 LGPL v3 许可证或商业许可证。 [https://www.qt.io/](https://www.qt.io/) 
  - QtXlsxWriter 采用 MIT 许可证。 :+1: [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
  - Qt-Table-Printer 遵循 BSD 3-Clause 许可证。 [https://github.com/T0ny0/Qt-Table-Printer](https://github.com/T0ny0/Qt-Table-Printer) 
  - recurse 已获得 MIT 许可。 [https://github.com/pkoretic/recurse](https://github.com/pkoretic/recurse)
  - libfort 采用 MIT 许可证。 [https://github.com/seleznevae/libfort](https://github.com/seleznevae/libfort)
  - colorprintf 已获得 MIT 许可。 [https://github.com/VittGam/colorprintf](https://github.com/VittGam/colorprintf)
  - HelloActions-Qt 采用 MIT 许可证。 [https://github.com/jaredtao/HelloActions-Qt](https://github.com/jaredtao/HelloActions-Qt)  

## :email: 联系方式
- 提出 Issue（问题反馈）. [https://github.com/QtExcel/QXlsx/issues](https://github.com/QtExcel/QXlsx/issues)
	- 如果您有兴趣参与该项目，请通过 Issue 与我们联系。
	- 我的母语非英语，英语水平有限，请尽量使用简明英文。:-)
- 如果您想将 README.md 翻译成您的母语，请联系我。
	- 您可以提出 Issue 或使用拉取请求。（例如 README.ko.md）
	
## 类似项目

### :star: <b>Qxlnt</b> [https://github.com/QtExcel/Qxlnt](https://github.com/QtExcel/Qxlnt)

<p align="center"><img src="https://github.com/QtExcel/Qxlnt/raw/master/markdown-data/Concept-QXlnt.jpg"></p>

- Qxlnt 是一个辅助项目，允许在 Qt 中使用 xlnt。
- xlnt 是一个用于使用 xlsx Excel 文件的优秀 C++ 库。
- 我一直在寻找一种在 Qt 中易于使用的方法。当然，cmake 与 Qt 兼容，但使用起来不太方便。所以我创建了 Qxlnt。

### :star: <b>Qlibxlsxwriter</b> [https://github.com/QtExcel/Qlibxlsxwriter](https://github.com/QtExcel/Qlibxlsxwriter)

<p align="center"><img src="https://github.com/QtExcel/Qlibxlsxwriter/raw/master/markdown.data/logo.png"></p>

- Qlibxlsxwriter 是一个辅助项目，允许在 Qt 中使用 libxlsxwriter。
- libxlsxwriter 是一个用于创建 Excel XLSX 文件的 C 库。

### :star: <b>QSimpleXlsxWriter</b> [https://github.com/QtExcel/QSimpleXlsxWriter](https://github.com/QtExcel/QSimpleXlsxWriter)

- 在 Qt 环境中使用 SimpleXlsxWriter。
- SimpleXlsxWriter 是用于为 MS Excel 2007 及更高版本创建 XLSX 文件的 C++ 库。

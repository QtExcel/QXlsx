# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md), [Russian](README.RU.md)*

<p align="center"><img src="https://raw.githubusercontent.com/QtExcel/QXlsx/master/markdown.data/QXlsx-Desktop.png"></p>

- QXlsx - это библиотека чтения / записи файлов Excel (*. Xlsx).
   - Поскольку QtXlsx больше не поддерживается (2014 г.), я создал новый проект, основанный на QtXlsx. (2017-)
- Язык разработки QXlsx - C ++. (с Qt)
- Вам не нужно использовать статическую библиотеку или динамический общий объект с помощью QXlsx.
   - Вы также можете использовать его как статическую библиотеку.

## Как использовать
- См. [Примеры](Example.md)
- См. [Wiki](https://github.com/QtExcel/QXlsx/wiki)
- См. [FAQ](https://github.com/QtExcel/QXlsx/wiki/FAQ).

## Как настроить (Установка)

-: Рекомендуется: 
- См. [Как настроить проект QXlsx (qmake)](HowToSetProject.md)
- См. [Как настроить проект QXlsx (cmake)](HowToSetProject-cmake.md)	

## Tested environment

| Travis CI (Linux) | AppVeyor (Windows) | CodeFactor | Github Actions <br> Linux/Win/Mac | iOS / Android  |
| :---------------: | :----------------: | :--------: | :------------------------: | :----------------------------: |
| [![Build Status](https://travis-ci.com/QtExcel/QXlsx.svg?branch=master)](https://travis-ci.com/QtExcel/QXlsx) | [![Build status](https://ci.appveyor.com/api/projects/status/jkod8257gg66vm6e?svg=true)](https://ci.appveyor.com/project/QtExcel/qxlsx) | [![CodeFactor](https://www.codefactor.io/repository/github/qtexcel/qxlsx/badge)](https://www.codefactor.io/repository/github/qtexcel/qxlsx) | [![Ubuntu](https://github.com/QtExcel/QXlsx/workflows/Ubuntu/badge.svg)](https://github.com/QtExcel/QXlsx/actions/Ubuntu)  [![MacOS](https://github.com/QtExcel/QXlsx/workflows/MacOS/badge.svg)](https://github.com/QtExcel/QXlsx/actions/MacOS)  [![Windows](https://github.com/QtExcel/QXlsx/workflows/Windows/badge.svg)](https://github.com/QtExcel/QXlsx/actions/Windows) | [![IOS](https://github.com/QtExcel/QXlsx/workflows/IOS/badge.svg)](https://github.com/QtExcel/QXlsx/actions/IOS)  [![Android](https://github.com/QtExcel/QXlsx/workflows/Android/badge.svg)](https://github.com/QtExcel/QXlsx/actions/Android) |  


- См. [Протестированные среды](TestEnv.md)

## Делать
- [Проверить](ToTest.md)
- [Что обновлять](ToUpgrade.md).
- [Vision](Vision.md)

## Вклады
- См. [Участники] (https://github.com/QtExcel/QXlsx/graphs/contributors).

## Лицензия и ссылки
- QXlsx находится под лицензией MIT. [https://github.com/QtExcel/QXlsx] (https://github.com/QtExcel/QXlsx)
- Спасибо за создание следующих замечательных проектов. : +1:
  - Qt находится под лицензией LGPL v3 или коммерческой лицензией. [https://www.qt.io/]] (https://www.qt.io/)
  - QtXlsxWriter находится под лицензией MIT. : +1: [https://github.com/dbzhang800/QtXlsxWriter] (https://github.com/dbzhang800/QtXlsxWriter)
  - Qt-Table-Printer находится под лицензией BSD 3-Clause. [https://github.com/T0ny0/Qt-Table-Printer] (https://github.com/T0ny0/Qt-Table-Printer)
  - рекурсивно под лицензией MIT. [https://github.com/pkoretic/recurse] (https://github.com/pkoretic/recurse)
  - libfort находится под лицензией MIT. [https://github.com/seleznevae/libfort] (https://github.com/seleznevae/libfort)
  - colorprintf находится под лицензией MIT. [https://github.com/VittGam/colorprintf] (https://github.com/VittGam/colorprintf)
  - HelloActions-Qt находится под лицензией MIT. [https://github.com/jaredtao/HelloActions-Qt] (https://github.com/jaredtao/HelloActions-Qt)

##: email: Контакт
- Оставь мне вопрос. [https://github.com/QtExcel/QXlsx/issues] (https://github.com/QtExcel/QXlsx/issues)
- Если вы заинтересованы в участии в проекте, обращайтесь к нам по вопросам.
- Мой родной язык не английский, и я плохо владею английским. Пожалуйста, используйте ЛЕГКИЙ английский. :-)
- Если вы хотите перевести README.md на свой родной язык, свяжитесь со мной.
- Вы можете поднять вопрос или использовать запрос на вытягивание. (например, README.ko.md)

## Похожие проекты

### :star: <b>Qxlnt</b> [https://github.com/QtExcel/Qxlnt](https://github.com/QtExcel/Qxlnt)

<p align="center"><img src="https://github.com/QtExcel/Qxlnt/raw/master/markdown-data/Concept-QXlnt.jpg"></p>

- Qxlnt - это вспомогательный проект, который позволяет использовать xlnt в Qt.
- xlnt - отличная библиотека C ++ для использования файлов Excel xlsx.
- Я искал способ упростить использование в Qt. Конечно, cmake совместим с Qt, но пользоваться им неудобно. Итак, я создал Qxlnt.

### :star: <b>Qlibxlsxwriter</b> [https://github.com/QtExcel/Qlibxlsxwriter](https://github.com/QtExcel/Qlibxlsxwriter)

<p align="center"><img src="https://github.com/QtExcel/Qlibxlsxwriter/raw/master/markdown.data/logo.png"></p>

- Qlibxlsxwriter - это вспомогательный проект, который позволяет использовать libxlsxwriter в Qt.
- libxlsxwriter - это библиотека C для создания файлов Excel XLSX.

### :star: <b>QSimpleXlsxWriter</b> [https://github.com/QtExcel/QSimpleXlsxWriter](https://github.com/QtExcel/QSimpleXlsxWriter)

- Используйте SimpleXlsxWriter в Qt.
- SimpleXlsxWriter - это библиотека C ++ для создания файлов XLSX для MS Excel 2007 и выше.

### This Document
- Written by @NikkiKurashov (github)
- Thank you. I am sorry to forget merge your branch and file. 

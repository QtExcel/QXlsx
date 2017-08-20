# QtXlsxWriter-Static

*Read this in other languages: [English](README.md), [한국어](README.ko.md)*

## QtXlsxWriter static library project

<img src="https://github.com/j2doll/j2doll-container/blob/master/images/qt-icon.png" width="48" height="48" /> <img src="https://github.com/j2doll/j2doll-container/blob/master/images/excel-icon.png" width="48" height="48" />

* Microsoft Excel file reader/writer for Qt5
* Use static library of QtXlsx.
* Some bug issue is fixed.

## Test environment
* Qt 5.9.1 (MingW/Windows 32bit) 
* Qt 5.9.1 (Ubuntu 16/Linux x64) 
* Qt 5.5.1 (MingW/Windows 32bit)
* Qt 5.6.0 (MingW/Windows 32bit) 
* Qt 5.5.0 (Ubuntu 17/Linux i686)
* Qt 5.2.0 (Ubuntu 14/Linux x64)
* Qt 5.0.1 (MingW/Windows 32bit) 

## Hello excel
```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!");
xlsx.saveAs("Test.xlsx");
```

## Copyright
* MIT License
* original source code from Debao Zhang(2014) : [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
* The Qt Company : 
   [https://www.qt.io/developers/](https://www.qt.io/developers/)
   
## About
* [https://github.com/j2doll](https://github.com/j2doll)
* [j2doll@gmail.com](mailto:j2doll@gmail.com)
* Hi! My native language is not English. My English is not fluent. Please use EASY English. :-) 




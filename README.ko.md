# QtXlsxWriter-Static

*Read this in other languages: [English](README.md), [한국어](README.ko.md)*

## QtXlsxWriter static library project

* 엑셀 파일(.xlsx) 읽기/쓰기 
* 정적 라이브러리 (Qt5)

## 테스트 환경
* Qt 5.9.1 (MingW/Windows 32bit) 
* Qt 5.9.1 (Ubuntu 16/Linux x64) 
* Qt 5.5.1 (MingW/Windows 32bit)
* Qt 5.6.0 (MingW/Windows 32bit) 
* Qt 5.5.0 (Ubuntu 17/Linux i686)
* Qt 5.2.0 (Ubuntu 14/Linux x64)
* Qt 5.0.1 (MingW/Windows 32bit) 

## 활용예제 Hello excel
```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!");
xlsx.saveAs("Test.xlsx");
```

## 빌드하는 방법
참조: https://github.com/j2doll/QtXlsxWriter-Static/wiki

## 라이선스
* MIT License
* 기반 소스코드 출처 Debao Zhang(2014) : [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
* The Qt Company : 
   [https://www.qt.io/developers/](https://www.qt.io/developers/)
   
## 배포/문의
* [https://github.com/j2doll](https://github.com/j2doll)
* [mailto:j2doll@gmail.com](mailto:j2doll@gmail.com)

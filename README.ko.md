# QtXlsx

*Read this in other languages: [English](README.md), [한국어](README.ko.md)*

## 엑셀 읽기/쓰기 정적 라이브러리

* QtXlsx는 엑셀 파일(*.xlsx) 읽기/쓰기 라이브러리입니다.
* QtXlsx는 Qt5를 사용하는 정적 라이브러리로 제작되었습니다.
* 원본 소스코드의 출처는 다음과 같습니다. Debao Zhang(2014) : https://github.com/dbzhang800/QtXlsxWriter

## 테스트 환경
* Qt 5.9.1 (MingW/Windows 32bit) 
* Qt 5.9.1 (Ubuntu 16/Linux x64) 
* Qt 5.5.1 (MingW/Windows 32bit)
* Qt 5.6.0 (MingW/Windows 32bit) 
* Qt 5.5.0 (Ubuntu 17/Linux i686)
* Qt 5.2.0 (Ubuntu 14/Linux x64)
* Qt 5.0.1 (MingW/Windows 32bit) 

## 활용예제 Hello excel (엑셀 파일 쓰기)
```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!");
xlsx.saveAs("Test.xlsx");
```

## 빌드하는 방법
참조: https://github.com/j2doll/QtXlsx/wiki

## 라이선스
* MIT License
* The Qt Company : 
   https://www.qt.io/developers/
   
## 문의
* https://github.com/j2doll
* mailto:j2doll@gmail.com

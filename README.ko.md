# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

<p align="center"><img src="https://github.com/j2doll/QXlsx/raw/master/markdown.data/QXlsx-Desktop.png"></p>

Linux | Windows
----- | -------
[![Build Status](https://travis-ci.com/j2doll/QXlsx.svg?branch=master)](https://travis-ci.com/j2doll/QXlsx) | [![Build status](https://ci.appveyor.com/api/projects/status/jkod8257gg66vm6e?svg=true)](https://ci.appveyor.com/project/j2doll/qxlsx)

- QXlsx는 엑셀 파일(*.xlsx)을 읽고 쓰는 라이브러리입니다.
- QtXlsx가 더이상 지원되지 않기 때문에(2014), QtXlsx에 기반한 새로운 프로젝트를 만들었습니다. (2017-)
- QXlsx는 개발언어로 C++를 사용합니다. (Qt 사용)
- QXlsx는 정적 또는 동적 라이브러리를 사용하지 않아도 되도록 제작되었습니다.

## 사용하는 방법
- [예제](Example.md)를 보세요
	- HelloWorld : 헬로우 월드 예제 (가장 기본적인 구조)
	- TestExcel : 기본 예제 (QtXlsx 예제 기반)
	- HelloAndroid : QML을 사용한 안드로이드에서 xlsx 파일 열기
	- Copycat : xlsx 파일을 읽어 위젯으로 표시. xlsx 파일 인쇄. (할일: xlsx 파일로 저장)
	- WebServer : xlsx 파일을 읽어 웹으로 표시 (`http://127.0.0.1:3001`)	

## 설정하는 방법 (설치)

- [QXlsx 프로젝트 설정하는 방법](HowToSetProject.ko.md) 참조

## 활용 예제 (Hello excel)

### :one: 엑셀(xlsx) 파일 쓰기

```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!"); // 셀(A,1)에 'Hello Qt!'값을 설정. 공유 문자열 타입으로 설정됨.
xlsx.saveAs("Test.xlsx"); // 'Test.xlsx'라는 이름으로 엑셀 파일을 저장.
```

### :two: 엑셀(xlsx) 파일 읽기

```cpp
Document xlsx("Test.xlsx"); // 엑셀 파일 읽기
if (!xlsx.isLoadPackage()) { 
	return; // 엑셀 파일 읽기 실패
}
int row = 1; int col = 2;
Cell* cell = xlsx.cellAt(row, col); // Cell의 pointer를 얻음 (행(row)는 1번째, 열(column)은 2번째)
if ( cell == NULL )
	continue; // 해당 행렬의 cell값이 설정되어 있지 않음
QVariant var = cell->readValue(); // 셀값을 읽음 (숫자(double), 날자(QDateTime), 문자열(QString) ...)
qDebug() << var; // 값 표시
```

## 테스트 환경

- [테스트된 환경](TestEnv.md) 참조

## 할 일

- [테스트 할 일](ToTest.md)

- [업그레드 할 일](ToUpgrade.md)

## 컨트리뷰터
- [컨트리뷰터](https://github.com/j2doll/QXlsx/graphs/contributors) 참조.

## 라이센스와 링크
- QXlsx 는 MIT 라이센스 입니다. [https://github.com/j2doll/QXlsx](https://github.com/j2doll/QXlsx)
- QtXlsx 는 MIT 라이센스 입니다. [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
- Qt-Table-Printer 는 BSD 3-Clause 라이센스 입니다. [https://github.com/T0ny0/Qt-Table-Printer](https://github.com/T0ny0/Qt-Table-Printer) 
- recurse 는 MIT 라이센스 입니다. [https://github.com/pkoretic/recurse](https://github.com/pkoretic/recurse)
- Qt 는 LGPL v3 라이센스 또는 상업용 라이센스 입니다. [https://www.qt.io/](https://www.qt.io/)

## :email: 문의
- 이슈를 남겨 주세요. [https://github.com/j2doll/QXlsx/issues](https://github.com/j2doll/QXlsx/issues)
- 프로젝트 참여에 관심이 있으신 분은 이슈로 연락주세요.
- README.md를 모국어로 번역하려면 저에게 연락하십시오.
	- 이슈(issue)를 제기하거나 pull request를 사용하시면 됩니다. (예: README.ko.md)

## 유사한 프로젝트

### :star: <b>Qxlnt</b> [https://github.com/j2doll/Qxlnt](https://github.com/j2doll/Qxlnt)

<p align="center"><img src="https://github.com/j2doll/Qxlnt/raw/master/markdown-data/Concept-QXlnt.jpg"></p>

- Qxlnt는 xlnt가 Qt에서 사용될 수있게 해주는 도우미 프로젝트입니다.
- xlnt는 xlsx Excel 파일을 사용하기에 훌륭한 C++ 라이브러리입니다. :+1:
- xlnt를 Qt에서 사용하기 쉬운 방법을 찾고 있었습니다. 물론 cmake는 Qt와 호환되지만 사용하기가 쉽지 않습니다. 그래서 Qxlnt를 만들었습니다.

### :star: <b>Qlibxlsxwriter</b> [https://github.com/j2doll/Qlibxlsxwriter](https://github.com/j2doll/Qlibxlsxwriter)

<p align="center"><img src="https://github.com/j2doll/Qlibxlsxwriter/raw/master/markdown.data/logo.png"></p>

- Qlibxlsxwriter는 libxlsxwriter를 Qt에서 사용할 수있는 도우미 프로젝트입니다.
- libxlsxwriter는 Excel XLSX 파일을 만들기위한 C 라이브러리 입니다.	

### :star: <b>QSimpleXlsxWriter</b> [https://github.com/j2doll/QSimpleXlsxWriter](https://github.com/j2doll/QSimpleXlsxWriter)

- SimpleXlsxWriter를 Qt에서 사용하세요.
- SimpleXlsxWriter는 MS 엑셀 2007 이상 버전에서 사용 가능한 XLSX 파일을 생성할 수 있는 C++ 라이브러리입니다.

# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

<p align="center"><img src="https://github.com/j2doll/QXlsx/raw/master/markdown.data/QXlsx2.jpg"></p>

![](markdown.data/qxlsx-badge1.png)

- QXlsx는 엑셀 파일(*.xlsx)을 읽고 쓰는 라이브러리입니다.
- QtXlsx가 더이상 지원되지 않기 때문에(2014), QtXlsx에 기반한 새로운 프로젝트를 만들었습니다. (2017-)
- QXlsx는 개발언어로 C++를 사용합니다. (Qt 사용)
- QXlsx는 정적 또는 동적 라이브러리를 사용하지 않아도 되도록 제작되었습니다.

## 활용하는 방법
- 예제를 보세요
	- TestExcel : 기본 예제 (QtXlsx 예제 기반)
	- HelloAndroid : QML을 사용한 안드로이드에서 xlsx 파일 열기
	- Copycat : xlsx 파일을 읽어 위젯으로 표시. xlsx 파일 인쇄. (할일: xlsx 파일로 저장)

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

## 설정하는 방법
* [QXlsx 프로젝트 설정하는 방법](HowToSetProject.ko.md)을 참조하세요.

## 테스트 환경

- [테스트된 환경](TestEnv.md)을 참조하세요.

## 테스트 할 일
- 다음과 같은 테스트들이 수행되어야 합니다.
	- 마이크로소프트 엑셀, 구글 스프레드쉬트, 리브레오피스 캘크 스프레드시트
- 유니코드 테스트 (파일 이름 :cloud:, 파일 경로 :cloud:, 자료값 :sunny:)

## 업그레이드 할 일
- xlsx의 암복호화 기능 개발

## 라이센스와 링크
- ![](markdown.data/mit-license.png) QXlsx는 MIT 라이센스 입니다. [https://github.com/j2doll/QXlsx](https://github.com/j2doll/QXlsx)
- ![](markdown.data/mit-license.png) QtXlsx는 MIT 라이센스 입니다. [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
- Qt-Table-Printer 는 BSD 3-Clause 라이센스 입니다. [https://github.com/T0ny0/Qt-Table-Printer](https://github.com/T0ny0/Qt-Table-Printer) 
- Qt 는 LGPL v3 라이센스 또는 상업용 라이센스 입니다. [https://www.qt.io/](https://www.qt.io/) 

## :email: 문의
- 이슈를 남겨 주세요. [https://github.com/j2doll/QXlsx/issues](https://github.com/j2doll/QXlsx/issues)
- 프로젝트 참여에 관심이 있으신 분은 이슈로 연락주세요.

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

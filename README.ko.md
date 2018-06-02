# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

![](markdown.data/IMG_0016.PNG)

## 엑셀(xlsx) 읽기/쓰기 라이브러리
* QXlsx는 엑셀 파일(*.xlsx)을 읽고 쓰는 라이브러리입니다.
  * QtXlsx가 더이상 지원되지 않기 때문에(2014), QtXlsx에 기반한 새로운 프로젝트를 만들었습니다. (2017-)
  * QXlsx는 개발언어로 C++를 사용합니다. (Qt 5.x 사용)
  * QXlsx는 정적 또는 동적 라이브러리를 사용하지 않아도 되도록 제작되었습니다.

![](markdown.data/comp.png)

## 라이센스
* QXlsx는 MIT 라이센스를 사용합니다 : https://opensource.org/licenses/MIT
* QtXlsx 라이센스는 Debao Zhang(2014) 싸이트를 참조하십시오.  https://github.com/dbzhang800/QtXlsxWriter
* Qt 라이센스는 Qt Company 싸이트를 참조하십시오. https://www.qt.io/developers/

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
if (!xlsx.isLoadPackage()) { // 엑셀 파일 읽기 실패
	return;
}
int row = 1; int col = 2;
Cell* cell = xlsx.cellAt(row, col); // Cell의 pointer를 얻음 (행(row)는 1번째, 열(column)은 2번째)
if ( cell == NULL )
	continue; // 해당 행렬의 cell값이 설정되어 있지 않음
QVariant var = cell->readValue(); // 셀값을 읽음 (숫자(double), 날자(QDateTime), 문자열(QString) ...)
qint32 styleNo = cell->styleNumber(); // 셀의 스타일 번호를 읽음
if ( styleNo >= 0 )
	qDebug() << row << " " << var << " , style:" << styleNo;
else
	qDebug() << row << " " << var;
```

## 설정하는 방법
* [QXlsx 프로젝트 설정하는 방법](HowToSetProject.ko.md)을 참조하세요.

## 테스트 환경
테스트된 환경은 다음과 같습니다.
- Qt 5.10.1 (MingW/Windows 32bit)
- Qt 5.9.2 (MingW/Windows 32bit)
- Qt 5.9.1 (Visual Studio 2017/Windows 64bit)
- Qt 5.9.1 (Visual Studio 2017/Windows 32bit)
- Qt 5.9.1 (MingW/Windows 32bit)
- Qt 5.9.1 (Ubuntu 16/Linux x64)
- Qt 5.6.0 (MingW/Windows 32bit)
- Qt 5.5.1 (MingW/Windows 32bit)
- Qt 5.5.0 (Ubuntu 17/Linux i686)
- Qt 5.2.0 (Ubuntu 14/Linux x64)
- Qt 5.0.1 (MingW/Windows 32bit)

## 테스트 할 일
다음과 같은 테스트들이 수행되어야 합니다.
- 마이크로소프트 엑셀
- 구글 스프레드쉬트
- 리브레오피스 캘크 스프레드시트

![](markdown.data/LibreOffice-Google-XLSX.png)

## 문의
* [https://github.com/j2doll/QXlsx](https://github.com/j2doll/QXlsx)
* :email: [j2doll@gmail.com](mailto:j2doll@gmail.com)

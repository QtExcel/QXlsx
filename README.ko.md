# QXlsx

> *Read this in other languages: [English](README.md), [한국어](README.ko.md)*

![](etc/IMG_0016.PNG)

## 엑셀 읽기/쓰기 라이브러리

* QXlsx는 엑셀 파일(*.xlsx) 읽기/쓰기 라이브러리입니다.
* QXlsx는 Qt 5.x를 사용하는 정적 라이브러리로 제작되었습니다.

## 라이센스
* QXlsx는 GPL 라이센스를 준수합니다. : https://www.gnu.org/licenses/gpl-3.0.en.html
* 최초 소스코드 출처: Debao Zhang(2014) : https://github.com/dbzhang800/QtXlsxWriter
* Qt 라이센스는 Qt Company 싸이트를 참조하십시오. : https://www.qt.io/developers/

## 활용 예제 Hello excel
### 엑셀 파일 쓰기 예제
```cpp
QXlsx::Document xlsx;
xlsx.write("A1", "Hello Qt!"); // 셀(A,1)에 'Hello Qt!'값을 설정. 공유 문자열 타입으로 설정됨.
xlsx.saveAs("Test.xlsx"); // 'Test.xlsx'라는 이름으로 엑셀 파일을 저장.
```
### 엑셀 파일 읽기 예제
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

## 빌드하는 방법
* 참조: https://github.com/j2doll/QXlsx/wiki

## 테스트 환경
* 참조: https://github.com/j2doll/QXlsx/wiki/Test-Environment

## 테스트할 것
다음과 같은 테스트들이 수행되어야 합니다
- 마이크로소프트 오피스(엑셀) 온라인 테스트
- 구글 닥스(스프레드쉬트) 테스트
- 리브레오피스

## 문의
* j2doll@gmail.com

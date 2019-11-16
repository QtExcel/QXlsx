# QXlsx

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

<p align="center"><img src="https://raw.githubusercontent.com/QtExcel/QXlsx/master/markdown.data/QXlsx-Desktop.png"></p>

- QXlsx는 엑셀 파일(*.xlsx)을 읽고 쓰는 라이브러리입니다.
  - QtXlsx가 더 이상 지원되지 않기 때문에(2014), QtXlsx에 기반한 새로운 프로젝트를 만들었습니다. (2017-)
- QXlsx는 개발언어로 C++을 사용합니다. (Qt 사용)
- QXlsx는 정적 또는 동적 라이브러리를 사용하지 않아도 되도록 제작되었습니다.
  - 물론 정적 라이브러리(static library)로 사용할 수도 있습니다.

## 사용하는 방법
- [예제](Example.md) 또는 [위키](https://github.com/QtExcel/QXlsx/wiki) 를 참조하세요.
	- HelloWorld : 헬로우 월드 예제 (가장 기본적인 구조)
	- TestExcel : QtXlsx 예제에 기반한 기본 예제
	- HelloAndroid : 안드로이드에서 xlsx 파일 열기
	- WebServer : xlsx 파일을 읽어 웹으로 표시	
	- ShowConsole : xlsx 파일을 읽어 콘솔에 표시

## 설정하는 방법 (설치)

- [QXlsx 프로젝트 설정하는 방법](HowToSetProject.ko.md) 참조

## 테스트 환경

Travis CI | AppVeyor  | CodeFactor
:-------: | :-------: | :--------:
[![Build Status](https://travis-ci.com/QtExcel/QXlsx.svg?branch=master)](https://travis-ci.com/QtExcel/QXlsx) | [![Build status](https://ci.appveyor.com/api/projects/status/jkod8257gg66vm6e?svg=true)](https://ci.appveyor.com/project/QtExcel/qxlsx) | [![CodeFactor](https://www.codefactor.io/repository/github/qtexcel/qxlsx/badge)](https://www.codefactor.io/repository/github/qtexcel/qxlsx)

- [테스트된 환경](TestEnv.md) 참조

## 할 일
- [테스트 할 일](ToTest.md)
- [업그레이드 할 일](ToUpgrade.md)
- [비전](Vision.md)

## 컨트리뷰터
- [컨트리뷰터](https://github.com/QtExcel/QXlsx/graphs/contributors) 참조.

## 라이센스와 링크
- QXlsx 는 MIT 라이센스 입니다. [https://github.com/QtExcel/QXlsx](https://github.com/QtExcel/QXlsx)
- QtXlsx 는 MIT 라이센스 입니다. [https://github.com/dbzhang800/QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)
- Qt-Table-Printer 는 BSD 3-Clause 라이센스 입니다. [https://github.com/T0ny0/Qt-Table-Printer](https://github.com/T0ny0/Qt-Table-Printer) 
- recurse 는 MIT 라이센스 입니다. [https://github.com/pkoretic/recurse](https://github.com/pkoretic/recurse)
- libfort 는 MIT 라이센스 입니다. [https://github.com/seleznevae/libfort](https://github.com/seleznevae/libfort)
- colorprintf 는 MIT 라이센스 입니다. [https://github.com/VittGam/colorprintf](https://github.com/VittGam/colorprintf)
- Qt 는 LGPL v3 라이센스 또는 상업용 라이센스 입니다. [https://www.qt.io/](https://www.qt.io/)

## :email: 문의
- 이슈를 남겨 주세요. [https://github.com/QtExcel/QXlsx/issues](https://github.com/QtExcel/QXlsx/issues)
- 프로젝트 참여에 관심이 있으신 분은 이슈로 연락주세요.
- README.md를 모국어로 번역하려면 저에게 연락하십시오.
	- 이슈(issue)를 제기하거나 pull request를 사용하시면 됩니다. (예: README.ko.md)

## 유사한 프로젝트

### :star: <b>Qxlnt</b> [https://github.com/QtExcel/Qxlnt](https://github.com/QtExcel/Qxlnt)

<p align="center"><img src="https://github.com/QtExcel/Qxlnt/raw/master/markdown-data/Concept-QXlnt.jpg"></p>

- Qxlnt는 xlnt가 Qt에서 사용될 수있게 해주는 도우미 프로젝트입니다.
- xlnt는 xlsx Excel 파일을 사용하기에 훌륭한 C++ 라이브러리입니다.
- xlnt를 Qt에서 사용하기 쉬운 방법을 찾고 있었습니다. 물론 cmake는 Qt와 호환되지만 사용하기가 쉽지 않습니다. 그래서 Qxlnt를 만들었습니다.

### :star: <b>Qlibxlsxwriter</b> [https://github.com/QtExcel/Qlibxlsxwriter](https://github.com/QtExcel/Qlibxlsxwriter)

<p align="center"><img src="https://github.com/QtExcel/Qlibxlsxwriter/raw/master/markdown.data/logo.png"></p>

- Qlibxlsxwriter는 libxlsxwriter를 Qt에서 사용할 수있는 도우미 프로젝트입니다.
- libxlsxwriter는 Excel XLSX 파일을 만들기 위한 C 라이브러리 입니다.	

### :star: <b>QSimpleXlsxWriter</b> [https://github.com/QtExcel/QSimpleXlsxWriter](https://github.com/QtExcel/QSimpleXlsxWriter)

- SimpleXlsxWriter를 Qt에서 사용하세요.
- SimpleXlsxWriter는 MS 엑셀 2007 이상 버전에서 사용 가능한 XLSX 파일을 생성할 수 있는 C++ 라이브러리입니다.

## cmake 사용하기

> *Read this in other languages: [English](HowToSetProject-cmake.md), :kr: [한국어](HowToSetProject-cmake.ko.md)*

:one: 아래와 같은 명령어들읋 입력하세요.

:two: MingW 사용하기

- QXlsx 라이브러리

```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..\QXlsx\
mingw32-make
```

- HelloWorld

```
mkdir build2
cd build2
cmake -G "MinGW Makefiles" ..\HelloWorld\
mingw32-make
```

:three: Linux/Mac/Unix 사용하기

- QXlsx 라이브러리

```
mkdir build
cd build
cmake -G "Unix Makefiles" ../QXlsx/
make
```

- HelloWorld

```
mkdir build2
cd build2
cmake -G "Unix Makefiles" ..\HelloWorld\
make
```


## cmake 사용하기

> *Read this in other languages: [English](HowToSetProject-cmake.md), :kr: [한국어](HowToSetProject-cmake.ko.md)*

- 다음과 같은 명령어들을 입력하세요. 

:one: MingW 사용하기

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

:two: Visual Studio 사용하기

- QXlsx 라이브러리 (Release Build)

```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..\QXlsx\
MSBuild /nologo /t:Build /p:Configuration=Release QXlsx.vcxproj
```

- HelloWorld (Release Build)

```
mkdir build2
cd build2
cmake -G "Visual Studio 16 2019" ..\HelloWorld\
MSBuild /nologo /t:Build /p:Configuration=Release HelloWorld.vcxproj 
```

- 또는, *.sln/*.vcxproj 파일들을 Visual Studio IDE에서 열어도 됩니다.

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
cmake -G "Unix Makefiles" ../HelloWorld/
make
```


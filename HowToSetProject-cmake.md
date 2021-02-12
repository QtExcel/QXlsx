## Using cmake 

> *Read this in other languages: [English](HowToSetProject-cmake.md), :kr: [한국어](HowToSetProject-cmake.ko.md)*

:one: Enter the command as shown below.

:two: Using Mingw

```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..\QXlsx\
mingw32-make
```

:three: Using Linux/Mac/Unix

```
mkdir build
cd build
cmake -G "Unix Makefiles" ../QXlsx/
make
```

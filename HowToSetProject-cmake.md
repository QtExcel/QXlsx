## Using cmake 

> *Read this in other languages: [English](HowToSetProject-cmake.md), :kr: [한국어](HowToSetProject-cmake.ko.md)*

:one: Enter the command as shown below.

:two: Using MingW

- QXlsx library

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


:three: Using Linux/Mac/Unix

- QXlsx library

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



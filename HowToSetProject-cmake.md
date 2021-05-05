## Using cmake 

> *Read this in other languages: [English](HowToSetProject-cmake.md), :kr: [한국어](HowToSetProject-cmake.ko.md)*

- Enter the command as shown below.

:one: Using MingW

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

:two: Using Visual Studio

- QXlsx library (Release Build)

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

- Or, You may open *.sln/*.vcxproj files in Visual Studio IDE.

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
cmake -G "Unix Makefiles" ../HelloWorld/
make
```



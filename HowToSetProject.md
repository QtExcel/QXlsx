
## How to setup QXlsx project

> *Read this in other languages: [English](HowToSetProject.md), :kr: [한국어](HowToSetProject.ko.md)*

- Here's an easy way to apply QXlsx.
- Describes when to apply to Windows.
- The method of applying it on Linux or Mac is similar, and I will write help if there is an additional request.
- * Hi! I'm j2doll. My native language is not English and my English is not fluent. Please understand. :-)

## Steps by QtCreator

:one: Clone source code from github

```sh
git clone https://github.com/j2doll/QXlsx.git
```

![](markdown.data/01.jpg)

<br /><br />

:two: Execute QtCreator

![](markdown.data/02.jpg)

* If you don't know use QtCreator, see Qt Company site. [https://www.qt.io/qt-features-libraries-apis-tools-and-ide/](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/)

<br /><br />

:three: Create your own Qt Project.

![](markdown.data/03.jpg)

<br /><br />

:four: Sample is console application.

![](markdown.data/04.jpg)

<br /><br />

:five: Set project name. Current project name is HelloQXlsx.  

![](markdown.data/05.jpg)

<br /><br />

:six: HelloQXlsx project has been created.

![](markdown.data/06.jpg)

<br /><br />

:seven: Current directory for project

![](markdown.data/07.jpg)

<br /><br />

:eight: Copy QXlsx code to your app project  

![](markdown.data/08.jpg)

```cmd
xcopy c:\workspace\github\QXlsx\QXlsx c:\workspace\HelloQXlsx /s /e
```

<br /><br />

:nine: Current directories and files for project

![](markdown.data/09.jpg)

<br /><br />

:keycap_ten: Append code for QXlxs library on your Qt project(*.pro)

![](markdown.data/10.jpg)

```qmake
# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)
```

<br /><br />

:one::one: Set heaer files and namespace for sample. Then append hello world code.

![](markdown.data/11.jpg)

```cpp
// main.cpp

#include <QCoreApplication>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsx.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'

    return 0;
    // return a.exec();
}
```

<br /><br />

:one::two: Build and Run a project

![](markdown.data/12.jpg)

<br /><br />

:one::three: A execute file(*.exe) and a excel file(xlsx) is created.

![](markdown.data/13.jpg)

<br /><br />

## Steps by CMake
+ Use cmake
  + CMAKE parameter：
    - [MUST] Qt5_DIR: qt install postion(default $QT_ROOT/lib/cmake/Qt5).
                   See：https://doc.qt.io/qt-5/cmake-get-started.html
    - [Optional] CMAKE_INSTALL_PREFIX: install prefix
  + linux

        mkdir build
        cd build
        cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/install \
             -DCMAKE_BUILD_TYPE=Release \
             -DQt5_DIR=${QT_ROOT}/lib/cmake/Qt5
        cmake --build . --config Release --target install
        
  + windows

        mkdir build
        cd build
        cmake .. -DCMAKE_INSTALL_PREFIX=%CD%/install ^
            -DCMAKE_BUILD_TYPE=Release ^
            -DQt5_DIR=${QT_ROOT}/lib/cmake/Qt5 
        cmake --build . --config Release --target install
  
  + android
    - The host is linux
      + Compile
      
            cd build
            cmake .. -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_INSTALL_PREFIX=`pwd`/android-build \
                -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
                -DANDROID_ABI="armeabi-v7a with NEON" \
                -DANDROID_PLATFORM=android-18 \
                -DQt5_DIR= 
            cmake --build . --config Release --target install

      + Install
        - Install library
        
              cmake --build . --config Release --target install/strip
                 
    - The host is windows
      + Compile
      
            cd build
            cmake .. -G"Unix Makefiles" ^
                -DCMAKE_BUILD_TYPE=Release ^
                -DCMAKE_INSTALL_PREFIX=`pwd`/android-build ^
                -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake ^
                -DCMAKE_MAKE_PROGRAM=${ANDROID_NDK}/prebuilt/windows-x86_64/bin/make.exe ^
                -DANDROID_PLATFORM=android-18 ^
                -DANDROID_ABI=arm64-v8a ^
                -DANDROID_ARM_NEON=ON ^
                -DQt5_DIR= 
            cmake --build . --config Release --target install
      
      + Install
        - Install library
          
              cmake --build . --config Release --target install/strip
                   
    + Parameter Description: https://developer.android.google.cn/ndk/guides/cmake
      + ANDROID_ABI: The following values can be taken:
         Goal ABI. If the target ABI is not specified, CMake uses armeabi-v7a by default.
         Valid ABI are:
        + armeabi：CPU with software floating point arithmetic based on ARMv5TE
        + armeabi-v7a：ARMv7-based device with hardware FPU instructions (VFP v3 D16)
        + armeabi-v7a with NEON：Same as armeabi-v7a, but with NEON floating point instructions enabled. This is equivalent to setting -DANDROID_ABI=armeabi-v7a and -DANDROID_ARM_NEON=ON.
        + arm64-v8a：ARMv8 AArch64 Instruction Set
        + x86：IA-32 Instruction Set
        + x86_64 - x86-64 Instruction Set
      + ANDROID_NDK <path> The path of installed ndk in host
      + ANDROID_PLATFORM: For a full list of platform names and corresponding Android system images, see the [Android NDK Native API] (https://developer.android.google.com/ndk/guides/stable_apis.html)
      + ANDROID_ARM_MODE
      + ANDROID_ARM_NEON
      + ANDROID_STL: Specifies the STL that CMake should use. 
        - c++_shared: The shared library variant of libc++.
        - c++_static: The static library variant of libc++.
        - none: No C++ standard library suport.
        - system: The system STL

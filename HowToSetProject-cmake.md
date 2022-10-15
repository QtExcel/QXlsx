## Using cmake 

> *Read this in other languages: [English](HowToSetProject-cmake.md), :kr: [한국어](HowToSetProject-cmake.ko.md)*

### To install QXlsx

Enter the command as shown below.

```sh
mkdir build
cd build
cmake ../QXlsx/ -DCMAKE_INSTALL_PREFIX=... -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install .
```

### To use in your application

In your CMakeLists.txt:

```cmake
find_package(QXlsxQt5 REQUIRED) # or QXlsxQt6
target_link_libraries(myapp PRIVATE QXlsx::QXlsx)
```

### To use in your application without installation

In your CMakeLists.txt:

```cmake
add_subdirectory(QXlsx)
target_link_libraries(myapp PRIVATE QXlsx::QXlsx)
```

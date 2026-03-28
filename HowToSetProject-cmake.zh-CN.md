## 使用 cmake

> *以其他语言阅读: [English](HowToSetProject-cmake.md), [한국어](HowToSetProject-cmake.ko.md), [简体中文](HowToSetProject.zh-CN.md)*

### 安装 QXlsx

执行以下命令:

```sh
mkdir build
cd build
cmake ../QXlsx/ -DCMAKE_INSTALL_PREFIX=... -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install .
```

### 项目中使用已安装的 QXlsx

在 CMakeLists.txt 中:

```cmake
find_package(QXlsxQt5 REQUIRED) # or QXlsxQt6
target_link_libraries(myapp PRIVATE QXlsx::QXlsx)
```

### 免安装的情况下使用 QXlsx

有两种方法可以在项目中直接集成 QXlsx:

1) 使用子目录方式:

```cmake
add_subdirectory(QXlsx)
target_link_libraries(myapp PRIVATE QXlsx::QXlsx)
```

2) 使用 FetchContent 拉取源码:

```cmake
FetchContent_Declare(
  QXlsx
  GIT_REPOSITORY https://github.com/QtExcel/QXlsx.git
  GIT_TAG        sha-of-the-commit
  SOURCE_SUBDIR  QXlsx
)
FetchContent_MakeAvailable(QXlsx)
target_link_libraries(myapp PRIVATE QXlsx::QXlsx)
```

如果未设置 `QT_VERSION_MAJOR`，QXlsx 的 CMakeLists.txt 会自动尝试查找 Qt 版本（5 或 6）。


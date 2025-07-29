# MultiLog 日志系统

一个轻量级、高性能的 C++ 日志系统，支持多级别日志输出、异步文件写入、批量 IO 优化，适用于中小型项目的日志记录需求。

## 核心特性

* **多日志级别** ：支持 `TRACE`/`DEBUG`/`INFO`/`WARNING`/`ERROR`/`FATAL`/`CRITICAL` 7 级日志。
* **异步输出** ：日志写入通过后台线程异步处理，避免阻塞主线程。
* **批量 IO 优化** ：日志事件积累到指定数量后批量写入文件，减少磁盘 IO 次数。
* **线程安全** ：通过线程局部存储和互斥锁保证多线程环境下的日志安全。
* **简洁易用** ：通过宏定义（`LOGINFO`/`LOGERROR` 等）简化日志调用。

## 快速上手

### 环境要求

* 编译器：支持C++11及以上标准
* 操作系统：Linux

### 编译和安装

#### 安装到本地

1. 克隆到本地

```bash
git clone https://gitee.com/Fighter-CTN/multilog.git
cd multilog
```

2. 使用CMake构建

```bash
mkdir build && cd build
cmake ..
sudo make install
# 生成库文件 libmultilog.a（静态库）
```

3. 集成到你的项目

* 包含头文件目录（include/）
* 链接生成的库文件（-lmultilog）

#### 集成项目中

1. 克隆到项目中

```bash
git clone https://gitee.com/Fighter-CTN/multilog.git
```

2. 主项目的 CMakeLists.txt 配置

```cmake
# 添加日志项目作为子目录
# 这会自动编译multilog静态库
add_subdirectory(third_party/multilog)

# 链接日志库
target_link_libraries(main_app PRIVATE multilog Threads::Threads)

# 包含日志库的头文件目录
target_include_directories(main_app PRIVATE 
    third_party/multilog/include
)

# 可选：关闭日志库的测试程序编译（如果不需要）
set(BUILD_TESTS OFF CACHE BOOL "Build multilog tests" FORCE)
```

## 使用说明

在代码中直接使用日志宏输出不同级别的日志：

```C++
#include "logger.h"

int main() {
    // 输出不同级别的日志
    LOGTRACE << "This is a trace message";
    LOGDEBUG << "Debugging variable x = " << 42;
    LOGINFO << "Program started successfully";
    LOGWARN << "Low memory warning";
    LOGERROR << "File not found: example.txt";
    LOGFATAL << "Critical error: division by zero";
    LOGCRIT << "System crash imminent!";

    return 0;
}
```

编译并运行后，日志会写入日志文件，内容类似：

```plaintext
[TRACE][main.cpp:5]This is a trace message
[DEBUG][main.cpp:6]Debugging variable x = 42
[INFO][main.cpp:7]Program started successfully
...
```

## 注意事项

* 线程安全：多线程环境下可安全使用，无需额外加锁。
* 日志丢失风险：程序异常退出时，未达到批量阈值的日志可能丢失（可通过添加退出钩子优化）。
* 自定义类型支持：如需输出自定义类，需在 log_utils.h 中为该类型特化 format_specifier。

## 软件架构

```plaintext
├── CMakeLists.txt
├── include
│   ├── appender_file.h
│   ├── appender.h
│   ├── log_event.h
│   ├── logger.h
│   ├── log_stream.h
│   ├── log_type.h
│   └── log_utils.h
├── LICENSE
├── README.en.md
├── README.md
├── src
│   ├── appender.cc
│   ├── appender_file.cc
│   ├── log_event.cc
│   ├── logger.cc
│   └── log_stream.cc
└── test
    ├── basic_test
    │   └── basic_test.cc
    ├── stress_test
    │   └── stress_test.cc
    └── thread_test
        └── thread_test.cc
```

## 开发计划

## 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request

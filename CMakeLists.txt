cmake_minimum_required(VERSION 3.10)
project(multilog VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    # 添加线程库链接标志
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# 查找线程库
find_package(Threads REQUIRED)

# 定义库的源文件 - 使用正则匹配所有.cc文件
file(GLOB MULTILOG_SOURCES "src/*.cc")

# 定义头文件目录
include_directories(include)

# 构建静态库 - 链接线程库
add_library(multilog STATIC ${MULTILOG_SOURCES})
target_link_libraries(multilog PRIVATE Threads::Threads)

# 安装配置 - 当用户安装库时
install(TARGETS multilog
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include/multilog
    FILES_MATCHING PATTERN "*.h"
)

# 测试程序配置
option(BUILD_TESTS "Build test programs" ON)

if(BUILD_TESTS)
    set(TEST_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

    # 基本测试
    add_executable(basic_test test/basic_test/basic_test.cc)
    target_link_libraries(basic_test PRIVATE multilog Threads::Threads)
    set_target_properties(basic_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}/basic_test
    )
    # 压力测试
    add_executable(stress_test test/stress_test/stress_test.cc)
    target_link_libraries(stress_test PRIVATE multilog Threads::Threads)
    set_target_properties(stress_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}/stress_test
    )
    
    # 线程测试
    add_executable(thread_test test/thread_test/thread_test.cc)
    target_link_libraries(thread_test PRIVATE multilog Threads::Threads)
    set_target_properties(thread_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}/thread_test
    )
endif()
    
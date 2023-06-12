cmake_minimum_required(VERSION 3.5)
project(workerManage)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
# 添加可执行文件
add_executable(main2 main.cpp  manager.cpp workermanage.cpp  employee.cpp)

# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 添加链接库
target_link_libraries(main2 ${CMAKE_THREAD_LIBS_INIT})

cmake_minimum_required(VERSION 3.10)
project(rpc)

#生成Debug版本，便于调试
set(CMAKE_BUILD_TYPE DEBUG)

#设置项目可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#设置项目的库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#设置项目编译头文件搜索路径 -I
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

#设置项目库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(example)
add_subdirectory(src)
cmake_minimum_required(VERSION 3.10)
project(protobuf_test)
# 查找 Protobuf 库
find_package(Protobuf REQUIRED)
include_directories(
    include
)
add_executable(test
main.cc
test.pb.cc
)
target_link_libraries(test ${Protobuf_LIBRARIES})
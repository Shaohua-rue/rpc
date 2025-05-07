find_package(Protobuf REQUIRED)

set(SRC_LIST 
calluserservice.cc
../public/user.pb.cc)

add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer rpc ${Protobuf_LIBRARIES})


set(SRC_CALL_FRIEND_LIST 
callfirendservice.cc
../public/friend.pb.cc)

add_executable(friendConsumer ${SRC_CALL_FRIEND_LIST})
target_link_libraries(friendConsumer rpc ${Protobuf_LIBRARIES})
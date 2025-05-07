set(SRC_LIST 
userservice.cc
../public/user.pb.cc)
find_package(Protobuf REQUIRED)
add_executable(provider ${SRC_LIST})
target_link_libraries(provider rpc ${Protobuf_LIBRARIES})

set(SRC_Friend_LIST 
friendservice
../public/friend.pb.cc)
add_executable(friend_provider ${SRC_Friend_LIST})
target_link_libraries(friend_provider rpc ${Protobuf_LIBRARIES})
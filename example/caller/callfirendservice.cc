#include <iostream>
#include "rpcapplication.h"
#include "friend.pb.h"
#include "rpcchannel.h"
#include "rpccontroller.h"
int main(int argc, char** argv)
{
    std::string config_file;
    if(argc < 2)
    {
        config_file =  "../config/defaultConfig.conf";
    }
    RpcApplication::Init(config_file);
    
    fixbug::FriendServiceRpc_Stub stub(new MRpcChannel);
    fixbug::GetFriendListsRequest request;
    request.set_userid(100);

    fixbug::GetFriendListsResponse response;
    RpcController controller;
    stub.GetFriendLists(&controller,&request,&response,nullptr);
    if(controller.Failed())
    {
        std::cout<<controller.ErrorText()<<std::endl;
    }
    else{
        if (0 == response.result().errcode())
        {
            std::cout << "rpc GetFriendsList response success!" << std::endl;
            int size = response.friends_size();
            for (int i=0; i < size; ++i)
            {
                std::cout << "index:" << (i+1) << " name:" << response.friends(i) << std::endl;
            }
        }
        else
        {
            std::cout << "rpc GetFriendsList response error : " << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}
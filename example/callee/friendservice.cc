#include <iostream>
#include <string>

#include "friend.pb.h"
#include "rpcapplication.h"
#include "rpcprovider.h"
#include "logger.h"
class FriendService : public fixbug::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendLists(uint32_t id)
    {
        std::cout << "do GetFriendsList service! userid:" << id << std::endl;
        std::vector<std::string> vec;
        vec.push_back("gao yang");
        vec.push_back("liu hong");
        vec.push_back("wang shuo");
        return vec;
    }
    void GetFriendLists(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendListsRequest* request,
                       ::fixbug::GetFriendListsResponse* response,
                       ::google::protobuf::Closure* done)override
    {
        uint32_t userid = request->userid();
        std::vector<std::string> friendList = GetFriendLists(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");

        for(std::string& name : friendList)
        {
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }
};

int main(int argc, char** argv)
{
    std::string config_file;
    if(argc < 2)
    {
        config_file =  "../config/defaultConfig.conf";
    }
    LOG_INFO("first logger");
    LOG_ERR("second logger: %s,%s,%d",__FILE__,__FUNCTION__,__LINE__);

    RpcApplication::Init(config_file);

    RpcProvider provider;
    provider.NotifySeriver(new FriendService());
    provider.Run();
}
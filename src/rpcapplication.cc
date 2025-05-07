#include "rpcapplication.h"

RpcConfig RpcApplication::config_;

void RpcApplication::Init(std::string str)
{
    config_.LoadConfigFile(str.c_str());
    std::cout << "rpcserverip:" << config_.Load("rpcserverip") << std::endl;
    std::cout << "rpcserverport:" << config_.Load("rpcserverport") << std::endl;
    std::cout << "zookeeperip:" << config_.Load("zookeeperip") << std::endl;
    std::cout << "zookeeperport:" << config_.Load("zookeeperport") << std::endl;
}
RpcApplication& RpcApplication::GetInstance()
{
    static RpcApplication app;
    return app;
}
RpcConfig& RpcApplication::GetConfig()
{
    return config_;
}
#include <iostream>
#include "rpcchannel.h"
#include "rpcapplication.h"
#include "user.pb.h"
int main(int argc,char** argv)
{
    std::string config_file;
    if(argc < 2)
    {
        config_file =  "../config/defaultConfig.conf";
    }
    RpcApplication::Init(config_file);

    //演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MRpcChannel());

    // rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;
    // 发起rpc方法的调用  同步的rpc调用过程  MprpcChannel::callmethod
    stub.Login(nullptr, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读调用的结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }


    //--------------------演示调用远程发布的rpc方法response
    fixbug::UserServiceRpc_Stub RegisterStub(new MRpcChannel());

    // rpc方法的请求参数
    fixbug::RegisterRequest registerRequest;
    registerRequest.set_id(12345);
    std::string name = "shaohua";
    std::string pwd = "kskdfhs";
    registerRequest.set_name(name.c_str());
    registerRequest.set_pwd(pwd.c_str());
    // rpc方法的响应
    fixbug::RegisterResponse registerResponse;
    // 发起rpc方法的调用  同步的rpc调用过程  MprpcChannel::callmethod
    RegisterStub.Register(nullptr, &registerRequest, &registerResponse, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读调用的结果
    if (0 == registerResponse.result().errcode())
    {
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    return 0;
}
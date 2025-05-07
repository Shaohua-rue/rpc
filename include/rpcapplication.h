#pragma once
#include "config.h"
#include "noncopyable.h"
class RpcApplication : public noncopyable
{
public:
    static void Init(std::string str);
    static RpcApplication& GetInstance();
    static RpcConfig& GetConfig();
private:
    static RpcConfig config_;
    RpcApplication(){}
};
#include <iostream>
#include <string>
#include "user.pb.h"
#include "rpcapplication.h"
#include "rpcprovider.h"

class UserService : public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout<<"doing local service: Login"<<std::endl;
        std::cout<<"name:"<< name <<" pwd:"<<pwd<<std::endl;
        return true;

    }
    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout <<"doing local service: Register"<<std::endl;
        std::cout << "id: "<< id <<"name: "<< name<<" pwd:"<<pwd<<std::endl;
        return true;
    }

    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)override
    {
        // 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务
        bool login_result = Login(name, pwd); 

        // 把响应写入  包括错误码、错误消息、返回值
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调操作   执行响应对象数据的序列化和网络发送（都是由框架来完成的）
        done->Run();
    }
    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)override
    {
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();
        bool ret = Register(id,name,pwd);

        response->mutable_result()->set_errmsg("");
        response->mutable_result()->set_errcode(0);
        response->set_success(ret);

        done->Run();
    }
private:

};

int main(int argc, char** argv)
{
    std::string config_file;
    if(argc < 2)
    {
        config_file =  "../config/defaultConfig.conf";
    }
    RpcApplication::Init(config_file);

    RpcProvider provider;
    provider.NotifySeriver(new UserService());
    provider.Run();

    return 0;

}
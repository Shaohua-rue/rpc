#pragma once
#include <string>
#include <google/protobuf/service.h>

class RpcController : public google::protobuf::RpcController
{
public:
    RpcController();
    void Reset()override;
    bool Failed()const override;
    std::string ErrorText() const override;
    void SetFailed(const std::string& reason)override;

    //目前没有具体实现的功能
    void StartCancel() override;
    bool IsCanceled() const override;
    void NotifyOnCancel(google::protobuf::Closure* callback) override;
private:
    bool m_failed;  //RPC方法执行过程中的状态
    std::string m_errText;  //RPC方法执行过程中的错误信息
};
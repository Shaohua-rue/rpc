#include "rpccontroller.h"

RpcController::RpcController()
{
    m_failed = false;
    m_errText = "";
}
void RpcController::Reset()
{
    m_failed = false;
    m_errText = "";
}
bool RpcController::Failed()const
{
    return m_failed;
}
std::string RpcController::ErrorText() const
{
    return m_errText;
}
void RpcController::SetFailed(const std::string& reason)
{
    m_failed = true;
    m_errText = reason;
}

//目前没有具体实现的功能
void RpcController::StartCancel()
{

}
bool RpcController::IsCanceled() const
{

}
void RpcController::NotifyOnCancel(google::protobuf::Closure* callback) 
{

}
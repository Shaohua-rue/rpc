#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include "rpcapplication.h"
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>

#include "rpcheader.pb.h"
#include "zookeeperutil.h"
class RpcProvider
{
public:
    void NotifySeriver(google::protobuf::Service* service);
    void Run();
private:

    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    // 已建立连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);
    void SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message *response);
private:
    struct ServiceInfo
    {
        google::protobuf::Service *m_service;//保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*>m_methodMap;
       
    };
    std::unordered_map<std::string, ServiceInfo>m_serviceMap;//存储注册成功的服务对象和其服务方法的所有信息
    muduo::net::EventLoop m_eventLoop;
};
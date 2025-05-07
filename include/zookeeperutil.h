#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>
#include "rpcapplication.h"
#include <iostream>
class ZKClient
{
public:
    ZKClient();
    ~ZKClient();
    void start();
    void create(const char* path,const char* data,int datalen,int state = 0);
    std::string getData(const char* path);
private:
    zhandle_t *m_zhandle;   //zk的客户节点
};
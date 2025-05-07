#pragma once
#include <time.h>
#include <thread>
#include <iostream>
#include "noncopyable.h"
#include "safelockqueue.h"

// 定义宏 LOG_INFO("xxx %d %s", 20, "xxxx")
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.setLogLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.setLogLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

enum LogLevel
{
    INFO,   //普通信息
    ERROR, //错误信息
};
class Logger:public noncopyable
{
public:
    static Logger& GetInstance();
    void setLogLevel(LogLevel level);
    void Log(std::string msg);
private:
    Logger();
    int m_loglevel;     //记录日志级别
    SafeLockQueue<std::string> m_lckQue;    //日志缓冲队列
};
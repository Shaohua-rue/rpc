#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class SafeLockQueue
{
public:
    void Push(const T& data)
    {
        std::lock_guard<std::mutex> lock(m_mutex_);
        m_queue.push(data);
        m_condition_variable.notify_one();
    }
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex_);
        while (m_queue.empty())
        {
            m_condition_variable.wait(lock);
        }
        T data = m_queue.front();
        m_queue.pop();
        return data;
        
    }
private:
   std::queue<T> m_queue;
   std::mutex m_mutex_;
   std::condition_variable m_condition_variable;
};

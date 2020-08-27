//
// Created by LENOVO on 2020/8/27.
//

#ifndef WEB_SERVER_THREAD_H
#define WEB_SERVER_THREAD_H

#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <functional>
#include <string>
#include <memory>
#include "noncopyable.h"
#include "CountDownLatch.h"

class Thread : noncopyable{
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc&, const std::string& name = std::string());
    ~Thread();
    void start();
    int join();
    bool started() const {
        return started_;
    }
    pid_t tid() const {
        return tid_;
    }
    const std::string& name() const { return name_; }

private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;
};


#endif //WEB_SERVER_THREAD_H

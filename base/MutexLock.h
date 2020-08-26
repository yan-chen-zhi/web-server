//
// Created by LENOVO on 2020/8/25.
//

#ifndef WEB_SERVER_MUTEXLOCK_H
#define WEB_SERVER_MUTEXLOCK_H

#include <pthread.h>
#include <cstdio>
#include "noncopyable.h"

class MutexLock :noncopyable {
public:
    MutexLock(){
        pthread_mutex_init(&mutex, MULL);   //初始化
    }
    ~MutexLock(){
        pthread_mutex_lock(&mutex);         //先阻塞，当锁使用完毕再销毁
        pthread_mutex_destroy(&mutex);
    }
    void lock(){
        pthread_mutex_lock(&mutex);
    }
    void unlock(){
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;

private:
    friend class Condition;
};

//构造加锁，析构解锁
class MutexLockGuard :noncopyable{
public:
    explicit MutexLockGuard(MutexLock &_mutex) :mutex(_mutex){
        mutex.lock();
    }
    ~MutexLockGuard(){
        mutex.unlock();
    }

private:
    MutexLock &mutex;
};
#endif //WEB_SERVER_MUTEXLOCK_H

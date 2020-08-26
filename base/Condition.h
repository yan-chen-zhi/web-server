//
// Created by LENOVO on 2020/8/25.
//

#ifndef WEB_SERVER_CONDITION_H
#define WEB_SERVER_CONDITION_H

#include <pthread.h>
#include "noncopyable.h"
#include "MutexLock.h"
#include <time.h>
#include <errno.h>

class Condition : noncopyable {
public:
    Condition(MutexLock& _mutex):mutex(_mutex) {
        pthread_cond_init(&cond, NULL);
    }
    ~Condition(){
        pthread_cond_destroy(&cond);
    }
    void wait(){
        pthread_cond_wait();
    }
    void notify(){
        pthread_cond_signal(&cond);
    }
    void notifyAll(){
        pthread_cond_broadcast(&cond);
    }
    bool waitForSeconds(int seconds){
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }

private:
    MutexLock& mutex;
    pthread_cond_t cond;
};
#endif //WEB_SERVER_CONDITION_H

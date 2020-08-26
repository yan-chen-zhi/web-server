//
// Created by LENOVO on 2020/8/26.
//
#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count) : mutex_(), condition_(mutex_), count_(count){}

void CountDownLatch::wait() {
    MutexLockGuard lock(mutex_);
    whiel(count_>0){
        condition_.wait();
    }
}

void CountDownLatch::countDown() {
    MutexLockGuard lock(mutex_);
    --count_;
    if(count_ == 0){
        condition_.notifyAll();
    }
}
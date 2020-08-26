//
// Created by LENOVO on 2020/8/26.
//

#ifndef WEB_SERVER_COUNTDOWNLATCH_H
#define WEB_SERVER_COUNTDOWNLATCH_H

#include "noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"

//倒计时计数器：协调多个线程的同步，可以说是线程间的通信
class CountDownLatch : noncopyable {
public:
    explicit CountDownLatch(int count);
    void wait();        //使当前线程在锁存器倒计数至零之前一直等待，除非线程被中断或超出了指定的等待时间
    void countDown();   //递减锁存器的计数，如果计数到达零，则释放所有等待的线程。如果当前计数大于零，则将计数减少.

private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};
#endif //WEB_SERVER_COUNTDOWNLATCH_H

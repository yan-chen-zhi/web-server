//
// Created by LENOVO on 2020/8/27.
//

#include "Thread.h"
#include <assert.h>
#include <errno.h>
#include <linux/unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <memory>
#include "CurrentThread.h"

#include <iostream>

using namespace std;

namespace CurrentThread {
	__thread int t_cacheTid = 0;
	__thread char t_tidString[32];
	__thread int t_tidStringLength = 6;
	__thread const char* t_threadName = "default";
}

pid_t gettid() {
	return static_cast<pid_t>(::syscall(SYS_gettid));
}

struct ThreadData {
	typedef Thread::ThreadFunc ThreadFunc;
	ThreadFunc func_;
	string name_;
	pid_t* tid_;
	CountDownLatch* latch_;
	
	ThreadData(const ThreadFunc& func, const string& name, pid_t* tid, CountDownLatch* latch) :func_(func), name_(name), tid_(tid), latch_(latch) {}
	
	void runInThread() {
		*tid_ = CurrentThread::tid();
		tid_ = NULL;
		latch_->countDown();
		latch_ = nullptr;

		CurrentThread::t_threadName = "finished";
	}
};

void *startThread(void* obj){
    auto data = static_cast<ThreadData*>(obj);
    data->runInThread();
    delete data;
    return nullptr;
}

Thread::Thread(const ThreadFunc &func, const string &n) : started_(false), joined_(false), pthreadId_(0), tid_(0), func_(func), name_(n), latch_(1){
    setDefaultName();
}

Thread::~Thread() {
    if(started_ && !joined_)
    {
        pthread_datach(pthreadId_);
    }
}

void Thread::setDefaultName() {
    if(name_.empty())
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "Thread");
        name_ = buf;
    }
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    ThreadData* data= new ThreadData(func_, name_, &tid_, &latch_);
    if(pthread_create(&pthreadId_, NULL, &startThread, data))
    {
        started_ = false
    }
}
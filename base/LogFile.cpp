//
// Created by LENOVO on 2020/8/26.
//

#include "LogFile.h"

using namespace std;

LogFile::LogFile(const std::string &basename, int flushInerval) : basename_(basename), flushInerval_(flushInerval), count_(0), mutex_(new MutexLock){
    file_.reset(new AppendFile(basename));
}

LogFile::~LogFile() {}

void LogFile::append(const char *logline, int len) {
    MutexLockGuard lock(*mutex_);
    append_unlocked(logline, len);
}

void LogFile::flush() {
    MutexLockGuard lock(*mutex_);
    file_->flush();
}

void LogFile::append_unlocked(const char *logline, int len) {
    file_->append(logline, len);
    ++count_;
    if(count_ >= flushInerval_){
        count_ = 0;
        file_->flush();
    }
}
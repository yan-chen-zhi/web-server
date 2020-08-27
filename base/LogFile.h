//
// Created by LENOVO on 2020/8/26.
//

#ifndef WEB_SERVER_LOGFILE_H
#define WEB_SERVER_LOGFILE_H

#include "noncopyable.h"
#include "MutexLock.h"
#include "FileUtil.h"
#include <string>

//封装FileUtil，通过设置循环次数，每flushInterval次，flush一下
class LogFile : noncopyable {
public:
    LogFile(const std::string& basename, int flushInerval = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    //bool rollFile();

private:
    void append_unlocked(const char* logline, int len);

    const std::string basename_;
    const int flushInerval_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
};
#endif //WEB_SERVER_LOGFILE_H

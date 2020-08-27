//
// Created by LENOVO on 2020/8/26.
//

#ifndef WEB_SERVER_ASYNCLOGGING_H
#define WEB_SERVER_ASYNCLOGGING_H

#include <string>
#include <vector>
#include "noncopyable.h"
#include "LogStream.h"

class AsyncLogging : noncopyable {
public:
    AsyncLogging(const std::string basename, int flushInterval = 2);
    ~AsyncLogging();

    void append(const char* logline, int len);

    void start();
    void stop();

private:
    void threadFunc();
    typedef FixedBuffer<kLargeBuffer> Buffer;
    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
    typedef std::shared_ptr<Buffer> BufferPtr;
    const int flushInterval_;
    bool running_;
    std::string basename_;
    Thread thread_;
};


#endif //WEB_SERVER_ASYNCLOGGING_H

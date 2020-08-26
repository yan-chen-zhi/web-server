//
// Created by LENOVO on 2020/8/26.
//

#ifndef WEB_SERVER_FILEUTIL_H
#define WEB_SERVER_FILEUTIL_H

#include <string>
#include "noncopyable.h"

class AppendFile : noncopyable {
public:
    explicit AppendFile(std::string filename);
    ~AppendFile();
    void append(const char* logline, const size_t len);
    void flush();

private:
    size_t write(const char* logline, const size_t len);
    FILE *fp_;
    char buffer_[64 * 1024];
};
#endif //WEB_SERVER_FILEUTIL_H

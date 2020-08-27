//
// Created by LENOVO on 2020/8/26.
//

#include "FileUtil.h"
#include <stdio.h>

using namespace std;

AppendFile::AppendFile(string filename) : fp_(fopen(filename.c_str(), "ae")){
    setbuffer(fp_, buffer_, sizeof(buffer_));   //设置文件流的缓冲区
}

AppendFile::~AppendFile() {
    fclose(fp_);
}

//往文件里
void AppendFile::append(const char *logline, const size_t len) {
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while(remain>0){
        size_t x = this->write(logline + n, remain);
        if(x == 0){
            int err = ferror(fp_);
            if(err){
                fprintf(stderr, "AppendFile append wrong!");
            }
            break;
        }
        n += x;
        remain = len - n;
    }
}

size_t AppendFile::write(const char* logline, size_t len) {
    return fwrite_unlocked(logline, l , len, fp_);
}

//将缓冲区冲刷干净
void AppendFile::flush() {
    fflush(fp_);
}
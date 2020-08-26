//
// Created by LENOVO on 2020/8/26.
//

#include "FileUtil.h"

AppendFile::AppendFile(std::string filename) : fp_(fopen(filename.c_str(), "ae")){
    setbuffer(fp_, buffer_, sizeof(buffer_));
}


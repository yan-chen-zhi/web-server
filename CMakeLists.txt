cmake_minimum_required(VERSION 3.13)
project(web_server)

set(CMAKE_CXX_STANDARD 11)

add_executable(web_server main.cpp base/noncopyable.h base/MutexLock.h base/Condition.h base/CountDownLatch.h base/CountDownLatch.cpp base/FileUtil.h base/FileUtil.cpp)
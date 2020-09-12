# web-server

本项目为C++11实现的Web服务器，解析get、head请求，支持HTTP长连接，实现了异步日志。


## Build

	./build.sh

## Usage

	./WebServer [-t thread_numbers] [-p port] [-l log_file_path(should begin with '/')]

技术细节：
1. Epoll实现的IO多路复用技术，采用reactor模型
2. 借鉴libevent实现基于小根堆的定时器关闭超时请求
3. one loop per thread，主线程accept请求，以round robin方式分发给其他IO线程，锁的争用只会出现在主线程和某特定线程中
4. 使用双缓存区技术实现了简单的异步日志系统
5. 状态机解析HTTP请求，支持管线化
6. 支持优雅关闭连接

并发模型：
Reactor+非阻塞IO+线程池，新连接round robin分配
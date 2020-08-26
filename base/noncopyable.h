//
// Created by LENOVO on 2020/8/25.
//

#ifndef WEB_SERVER_NONCOPYABLE_H
#define WEB_SERVER_NONCOPYABLE_H

class noncopyable {
protected:
    noncopyable();
    ~noncopyable();

private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};
#endif //WEB_SERVER_NONCOPYABLE_H

//
// Created by y00564656 on 2022/11/14.
//

#ifndef TEST_NEWHANDLERHOLDER_H
#define TEST_NEWHANDLERHOLDER_H

#include <new>

class NewHandlerHolder {
public:
    explicit NewHandlerHolder(std::new_handler nh) : handler(nh) {}
    ~NewHandlerHolder() {
        std::set_new_handler(handler);
    }
    NewHandlerHolder(const NewHandlerHolder &) = delete;

    NewHandlerHolder &operator=(const NewHandlerHolder &) = delete;
private:
    std::new_handler handler;
};


#endif //TEST_NEWHANDLERHOLDER_H

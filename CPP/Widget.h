//
// Created by y00564656 on 2022/11/14.
//

#ifndef TEST_WIDGET_H
#define TEST_WIDGET_H
#include <new>

class Widget {
public:
    static std::new_handler set_new_handler(std::new_handler p) noexcept;
    static void* operator new(std::size_t size) noexcept;
    static void *operator new[](std::size_t size) noexcept;
private:
    static std::new_handler currentHandler;
};


#endif //TEST_WIDGET_H

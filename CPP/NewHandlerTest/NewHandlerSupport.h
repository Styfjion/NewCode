//
// Created by y00564656 on 2022/11/15.
//

#ifndef TEST_NEWHANDLERSUPPORT_H
#define TEST_NEWHANDLERSUPPORT_H
#include <iostream>
#include <new>
#include "NewHandlerHolder.h"

template <typename T>
class NewHandlerSupport {
public:
    static std::new_handler set_new_handler(std::new_handler p) noexcept;
    static void* operator new(std::size_t size) noexcept;
    static void *operator new[](std::size_t size) noexcept;
private:
    static std::new_handler currentHandler;
};

template<typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) noexcept {
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

template<typename T>
void *NewHandlerSupport<T>::operator new(std::size_t size) noexcept {
    std::cout << "Using Widget::operator new" << std::endl;
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}

template<typename T>
void *NewHandlerSupport<T>::operator new[](std::size_t size) noexcept {
    std::cout << "Using Widget::operator new[]" << std::endl;
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new[](size);
}

template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = nullptr;


#endif //TEST_NEWHANDLERSUPPORT_H

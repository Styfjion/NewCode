#include <iostream>
#include "Widget.h"
#include "NewHandlerHolder.h"

std::new_handler Widget::set_new_handler(std::new_handler p) noexcept {
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

void *Widget::operator new(std::size_t size) noexcept {
    std::cout << "Using Widget::operator new" << std::endl;
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}

void *Widget::operator new[](std::size_t size) noexcept {
    std::cout << "Using Widget::operator new[]" << std::endl;
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new[](size);
}

std::new_handler Widget::currentHandler = nullptr;

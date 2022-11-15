#ifndef TEST_WIDGET_H
#define TEST_WIDGET_H

#include "NewHandlerSupport.h"

class Widget : public NewHandlerSupport<Widget> {
public:
    Widget() { std::cout << "Widget init" << std::endl; }
};


#endif //TEST_WIDGET_H

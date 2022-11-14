#include <iostream>
#include "Widget.h"

void outOfMem()
{
    std::cerr << "Unable to satisfy request for memory" << std::endl;
    std::abort();
}

int main()
{
    Widget::set_new_handler(outOfMem);
    auto* pw1 = new Widget;
    auto* pw2 = new Widget[1000000000000L];
    auto *ps1 = new std::string;
    delete pw1;
    delete[] pw2;
    delete ps1;
    return 0;
}

//Unable to satisfy request for memory
//Using Widget::operator new
//Using Widget::operator new[]





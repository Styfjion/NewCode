//
// Created by y00564656 on 2022/7/1.
//
#include <iostream>
#include <unistd.h>
#include "threadsafe_queue.h"

threadsafe_queue<int> queue;

void produce() {
    while (true) {
        queue.push(rand());
        sleep(1);
    }
}

void consume() {
    int value = 0;
    while (true) {
        queue.wait_and_pop(value);
        std::cout << value << std::endl;
        sleep(1);
    }
}

int main()
{
    std::thread tp(produce);
    std::thread tc(consume);
    tp.join();
    tc.join();
    return 0;
}
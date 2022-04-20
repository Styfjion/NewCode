//
// Created by yangf on 2022/3/18.
//

#include <iostream>
#include <atomic>
#include <thread>
#include <functional>

using namespace std;

class Foo {
    atomic<bool> a{ false };
    atomic<bool> b{ false };
public:
    void first(const function<void()>& printFirst) {
        printFirst();
        a = true;
    }

    void second(const function<void()>& printSecond) {
        while (!a)
            this_thread::sleep_for(chrono::milliseconds(1));
        printSecond();
        b = true;
    }

    void third(const function<void()>& printThird) {
        while (!b)
            this_thread::sleep_for(chrono::milliseconds(1));
        printThird();
    }
};

void printFirst() {
    cout << "printFirst" << endl;
}

void printSecond() {
    cout << "printSecond" << endl;
}

void printThird() {
    cout << "printThird" << endl;
}

int main()
{
    Foo foo;
    thread t1(&Foo::second, &foo, std::ref(printSecond));
    thread t2(&Foo::first, &foo, std::ref(printFirst));
    thread t3(&Foo::third, &foo, std::ref(printThird));
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
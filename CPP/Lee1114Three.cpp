//
// Created by yangf on 2022/3/18.
//
#include <semaphore.h>
#include <functional>
#include <thread>
#include <iostream>

using namespace std;

class Foo {
private:
    sem_t sem_1, sem_2;

public:
    Foo() {
        sem_init(&sem_1, 0, 0), sem_init(&sem_2, 0, 0);
    }

    void first(const function<void()>& printFirst) {
        printFirst();
        sem_post(&sem_1);
    }

    void second(const function<void()>& printSecond) {
        sem_wait(&sem_1);
        printSecond();
        sem_post(&sem_2);
    }

    void third(const function<void()>& printThird) {
        sem_wait(&sem_2);
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

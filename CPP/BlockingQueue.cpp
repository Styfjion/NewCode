//
// Created by y00564656 on 2022/5/20.
//

#include "BlockingQueue.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

void BlockingQueue::put(int data) {
    unique_lock<mutex> lock(cv_m);
    cout << "waiting consumer use data" << endl;
    pro_cv.wait(lock, [this](){return queueEntry.size() < 2;});
    cout << "begin to produce data " << data << endl;
    queueEntry.push(data);
    lock.unlock();
    con_cv.notify_all();
}

void BlockingQueue::pop() {
    unique_lock<mutex> lock(cv_m);
    cout << "waiting producer insert data" << endl;
    con_cv.wait(lock, [this](){return !queueEntry.empty() || flag;});
    if (flag) {
        cout << "consumer finished" << endl;
        lock.unlock();
        return;
    }
    cout << "begin to consume data" << endl;
    cout << "use" << queueEntry.front() << endl;
    queueEntry.pop();
    lock.unlock();
    pro_cv.notify_one();
}

void BlockingQueue::setFlag() {
    unique_lock<mutex> lock(cv_m);
    cout << "flag set finished" << endl;
    flag = true;
    lock.unlock();
    con_cv.notify_all();
}

bool BlockingQueue::getFlag() const {
    return flag;
}

void produce(BlockingQueue& blockingQueue)
{
    for (int i = 0; i < 10; i++) {
        blockingQueue.put(i);
    }
}

void consumer(BlockingQueue& blockingQueue)
{
    while(!blockingQueue.getFlag()) {
        blockingQueue.pop();
    }
}

void setFlag(BlockingQueue& blockingQueue)
{
    this_thread::sleep_for(chrono::seconds(10));
    blockingQueue.setFlag();
}

int main()
{
    BlockingQueue blockingQueue;
    thread t1(produce, ref(blockingQueue)), t2(consumer, ref(blockingQueue)), t3(consumer, ref(blockingQueue));
    thread t4(setFlag, ref(blockingQueue));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}

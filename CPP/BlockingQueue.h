//
// Created by y00564656 on 2022/5/20.
//

#ifndef TEST_BLOCKINGQUEUE_H
#define TEST_BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class BlockingQueue {
public:
    void put(int data);
    void pop();
    void setFlag();
    [[nodiscard]] bool getFlag() const;
private:
    queue<int> queueEntry;
    mutex cv_m;
    condition_variable pro_cv;
    condition_variable con_cv;
    bool flag = false;
};


#endif //TEST_BLOCKINGQUEUE_H

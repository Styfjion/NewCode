//
// Created by y00564656 on 2022/7/1.
//

#ifndef TEST_THREADSAFE_QUEUE_H
#define TEST_THREADSAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class threadsafe_queue {
public:
    threadsafe_queue() = default;
    ~threadsafe_queue() = default;

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(new_value));
        data_cond.notify_one();
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this](){return !this->data_queue.empty();});
        value = std::move(data_queue.front()); //移动临时值到引用赋值
        data_queue.pop();
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()) {
            return false;
        }
        value = std::move(data_queue.front());
        data_queue.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
};


#endif //TEST_THREADSAFE_QUEUE_H

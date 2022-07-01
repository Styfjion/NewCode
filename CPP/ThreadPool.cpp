#include <queue>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <atomic>
#include <unistd.h>

std::atomic<int> idx(0);

class ThreadPool {
private:
    struct InternalData {
        using Task = std::function<void()>;
        std::mutex mutex_;
        std::condition_variable condition_;
        bool stop_ = false;
        std::queue<Task> tasks_;
    };

public:
    explicit ThreadPool(size_t count = COUNT): data_(nullptr), count_(count){}
    ThreadPool(ThreadPool &&) = default;
    ~ThreadPool() {
        if (data_ != nullptr) {
            {
                std::lock_guard<std::mutex> lk(data_->mutex_);
                data_->stop_ = true;
            }
            data_->condition_.notify_all();
        }
    }
    void init();
    template<class F>
    void commit(F &&task) {
        {
            std::lock_guard<std::mutex> lk(data_->mutex_);
            data_->tasks_.emplace(std::forward<F>(task));
        }
        data_->condition_.notify_one();
    }
private:
    std::shared_ptr<InternalData> data_;
    size_t count_;
    static constexpr size_t COUNT = 8;
};

void ThreadPool::init() {
    data_ = std::make_shared<InternalData>();
    for (size_t i = 0; i < count_; i++) {
        std::thread([data = data_](){
            std::unique_lock<std::mutex> lk(data->mutex_);
            for(;;) {
                if (!data->tasks_.empty()) {
                    auto current = std::move(data->tasks_.front());
                    data->tasks_.pop();
                    lk.unlock();
                    current();
                    lk.lock();
                } else if (data->stop_) {
                    break;
                } else {
                    data->condition_.wait(lk);
                }
            }
        }).detach();
    }
}

void testWrite()
{
    std::string fileName = std::to_string(idx++) + ".txt";
    std::cout << fileName << std::endl;
    std::ofstream outStream;
    outStream.open(fileName, std::ios::out);
    if (outStream.is_open()) {
        outStream << "Hello, world" << std::endl;
        outStream.close();
    }
}

int main()
{
    ThreadPool threadPool;
    threadPool.init();
    for (int i = 0; i < 10; i++) {
        threadPool.commit(testWrite);
    }
    sleep(10);
    return 0;
}

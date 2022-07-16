#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

class QueryResultQueue {
public:
    void fetchNextQueryResult(std::vector<int>& input)
    {
        std::unique_lock<std::mutex> lock(dataMutex_);
        produceCond_.wait(lock, [this]() { return this->resultQueue_.size() <= 100; });

        size_t rowNumFetch = 0;
        while (!input.empty()) {
            resultQueue_.emplace(input.back());
            input.pop_back();
            ++rowNumFetch;
            if (rowNumFetch == 100) {
                std::cout << "produce full" << std::endl;
                break;
            }
        }

        if (input.empty()) {
            std::cout << "produce finished" << std::endl;
            produceFinished_ = true;
        }
        lock.unlock();
        consumerCond_.notify_all();
    }

    std::vector<int> consumeQueryResult(unsigned rowNum)
    {
        std::vector<int> result;
        std::unique_lock<std::mutex> lock(dataMutex_);
        consumerCond_.wait(lock, [this]() { return !this->resultQueue_.empty() || produceFinished_; });
        for (unsigned i = 0; i < rowNum; i++) {
            if (resultQueue_.empty()) {
                std::cout << "data is empty" << std::endl;
                break;
            }
            result.push_back(resultQueue_.front());
            resultQueue_.pop();
        }
        lock.unlock();
        produceCond_.notify_one();
        return result;
    }

    bool getProduceFlag() const
    {
        return produceFinished_;
    }

private:
    std::queue<int> resultQueue_ {};
    std::mutex dataMutex_;
    std::condition_variable produceCond_;
    std::condition_variable consumerCond_;
    bool produceFinished_ = false;
};

void consumeData(QueryResultQueue& queryResultQueueOp, int id)
{
    std::cout << "consume thread" << " " << id << std::endl;
    while (true) {
        auto result = queryResultQueueOp.consumeQueryResult(30);
        if (result.empty()) {
            std::cout << "thread is over" << std::endl;
            break;
        }
    }
}

void produceData(QueryResultQueue& queryResultQueueOp, std::vector<int>& primer)
{
    std::cout << "produce main thread" << std::endl;
    while (!queryResultQueueOp.getProduceFlag()) {
        std::cout << "produce once" << std::endl;
        queryResultQueueOp.fetchNextQueryResult(primer);
    }
}

int main()
{
    std::vector<int> primer(1000);
    QueryResultQueue queryResultQueueOp;
    std::vector<std::thread> consumerThreads;
    for (int i = 0; i < 3; i++) {
        consumerThreads.emplace_back(std::thread(consumeData, std::ref(queryResultQueueOp), i));
    }
    produceData(queryResultQueueOp, primer);
    for(auto& consumer : consumerThreads) {
        consumer.join();
    }
    return 0;
}

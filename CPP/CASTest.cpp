#include<iostream>
#include<atomic>
#include<thread>
using namespace std;

class CAS
{
private:
    std::atomic<bool> flag;
public:
    CAS():flag(false) {}
    ~CAS() = default;
    CAS(const CAS& s) = delete;
    CAS& operator=(const CAS&) = delete;
    void lock()
    {
        bool expect = false;
        while (!flag.compare_exchange_strong(expect, true))
        {
            expect = false;
        }
    }
    void unlock()
    {
        flag.store(false);
    }

};

int num = 0;
CAS sm;

void fun()
{
    for (int i = 0;i < 1000;i++)
    {
        sm.lock();
        cout << "num:" << ++num << endl;
        sm.unlock();
    }
}

int main()
{
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    return 0;
}

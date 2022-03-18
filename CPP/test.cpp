#include <iostream>
#include <functional>
using namespace std;

void fun()
{
    cout << "Test" << endl;
}

void funTwo(int& a) {
    a = 1;
}

int main(int argc, char const *argv[])
{
    cout << "Hello, world" << endl;
    function<void()> testFun = fun;
    testFun();
    int a = 2;
    function<void(int&)> test2 = funTwo;
    test2(a);
    cout << a << endl;
    return 0;
}

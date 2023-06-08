#include <iostream>
#include <vector>
#include <functional>

using namespace std;

vector<function<int()>> createCounter(int init) {
    static int curVal = init;
    static int prime = init;
    auto add = [&]() { return ++curVal; };
    auto dec = [&]() { return --curVal; };
    auto reset = [&]() { return curVal = prime; };
    return {add, dec, reset};
}

int main() {
    auto sol = createCounter(5);
    cout << sol[0]() << endl;
    cout << sol[2]() << endl;
    cout << sol[1]() << endl;
}
// 6
// 5
// 4

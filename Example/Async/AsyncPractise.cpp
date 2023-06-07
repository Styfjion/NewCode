#include <iostream>
#include <future>
#include <thread>

using namespace std;

int g() {
    cout << "g 1" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "g 2" << endl;
    return 0;
}

int f() {
    auto gf = async(g);
    cout << "f 1" << endl;
    int gr = gf.get(); // 阻塞到获取值
    cout << "gr is " << gr << endl;
    cout << "f 2" << endl;
    return 1;
}

int main() {
    cout << "start" << endl;
    auto ff = async(f);
    int fr = ff.get();
    cout << "fr is " << fr << endl;
    cout << "finish" << endl;
    return 0;
}

//output:
//start
//f 1
//g 1
//g 2
//gr is 0
//f 2
//fr is 1
//finish
//说明：f 1和g 1顺序不确定

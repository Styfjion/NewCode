//
// Created by yangf on 2022/2/20.
//
#include <vector>
#include <list>
using namespace std;
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        if (bits.back() != 0) {
            return false;
        }
        bits.pop_back();
        auto iter = bits.begin();

        while (iter != bits.end()) {
            if (*iter == 1) {
                if (iter == bits.end() - 1) {
                    return false;
                }
                bits.erase(iter, iter + 2);
            } else {
                iter++;
            }
        }
        return true;
    }
};

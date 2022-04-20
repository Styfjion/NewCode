//
// Created by yangf on 2022/4/9.
//
#include <queue>
#include <unordered_set>
#include <iostream>

using namespace std;

struct PointHash {
    size_t operator()(const pair<int, int> item) const
    {
        return hash<int>()(item.first) ^ hash<int>()(item.second);
    }
};

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx > sx && ty > sy && tx != ty) {
            if (ty > tx) {
                ty %= tx;
            } else {
                tx %= ty;
            }
        }
        if (tx == ty) {
            return tx == sx && ty == sy;
        } else if (tx > sx && ty == sy) {
            return (tx - sx) % ty == 0;
        } else if (ty > sy && tx == sx) {
            return (ty - sy) % tx == 0;
        } else {
            return false;
        }
    }
};

int main()
{
    Solution sol;
    cout << sol.reachingPoints(1, 1, 3, 5);
}
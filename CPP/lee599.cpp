//
// Created by yangf on 2022/3/14.
//
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> records;
        for (int i = 0; i < list1.size(); i++) {
            records[list1[i]] = i;
        }

        vector<string> rslt;
        int result = list1.size() + list2.size();
        for (int i = 0; i < list2.size(); i++) {
            if (records.count(list2[i]) != 0) {
                int curVal = i + records[list2[i]];
                if (curVal > result) {
                    continue;
                }
                if (curVal < result) {
                    rslt.clear();
                    result = curVal;
                }
                rslt.emplace_back(list2[i]);
            }
        }
        return rslt;
    }
};
//
// Created by yangf on 2022/4/20.
//
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <numeric>

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        regex re("\n");
        vector<string> subList(sregex_token_iterator(input.begin(), input.end(), re, -1), sregex_token_iterator());
        int result = 0;
        vector<int> tempList;
        for (const string& unit : subList) {
            auto level = count(unit.begin(), unit.end(), '\t');
            if (level < tempList.size()) {
                tempList.resize(level);
            }
            auto pos = unit.find_last_of('\t');
            string file_name = pos != string::npos ? unit.substr(pos + 1) : unit;
            if (file_name.rfind('.') == string::npos) {
                tempList.emplace_back(file_name.size() + 1);
            } else {
                result = max(result, accumulate(tempList.begin(), tempList.end(), static_cast<int>(file_name.size())));
            }
        }
        return result;
    }
};
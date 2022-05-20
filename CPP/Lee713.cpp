//
// Created by yangf on 2022/5/5.
//
#include <vector>

using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0;
        int product = 1;
        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            product *= nums[i];
            while (left <= i && product <= k) {
                product /= nums[left++];
            }
            result += i - left + 1;
        }
        return result;
    }
};
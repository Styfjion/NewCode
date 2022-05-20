from typing import List


class Solution:
    def findDuplicates(self, nums: List[int]) -> List[int]:
        res = []
        for unit in nums:
            unit = abs(unit)
            if nums[unit - 1] > 0:
                nums[unit - 1] = - nums[unit - 1]
            else:
                res.append(unit)
        return res

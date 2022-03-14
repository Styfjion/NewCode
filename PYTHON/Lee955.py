from typing import List


class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        records = {elem: i for i, elem in enumerate(list1)}

        result = []
        min_sum = len(list1) + len(list2)
        for i, elem in enumerate(list2):
            if elem not in records:
                continue
            cur_sum = records[elem] + i
            if cur_sum > min_sum:
                continue
            if cur_sum < min_sum:
                result.clear()
                min_sum = cur_sum
            result.append(elem)

        return result


class Solution:
    def lengthLongestPath(self, input: str) -> int:
        sub_list = input.split('\n')
        result = 0
        temp_list = []
        for unit in sub_list:
            level = unit.count('\t')
            if level < len(temp_list):
                temp_list = temp_list[:level]
            pos = unit.rfind('\t')
            file_name = unit[pos + 1:]
            if '.' not in file_name:
                temp_list.append(len(file_name) + 1)
            else:
                result = max(result, sum(temp_list) + len(file_name))
        return result


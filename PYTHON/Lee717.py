from typing import List


class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        if bits[-1] != 0:
            return False

        bits.pop()
        pos = 0
        while pos != len(bits):
            if bits[pos] == 1:
                bits.pop(pos)
                if pos == len(bits):
                    return False
                bits.pop(pos)
            else:
                pos += 1
        return True

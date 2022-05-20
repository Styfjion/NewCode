//
// Created by yangf on 2022/4/29.
//
#include <vector>
#include <unordered_set>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node* traverseSubnet(const pair<int, int>& point, int level, vector<vector<int>>& grid)
    {
        if (level == 0) {
            return new Node(bool(grid[0][0]), true);
        }
        Node *topLeft, *topRight, *bottomLeft, *bottomRight;
        if (level > 1) {
            topLeft = traverseSubnet({point.first - level / 2, point.second - level / 2}, level / 2, grid);
            topRight = traverseSubnet({point.first + level / 2, point.second - level / 2}, level / 2, grid);
            bottomLeft = traverseSubnet({point.first - level / 2, point.second + level / 2}, level / 2, grid);
            bottomRight = traverseSubnet({point.first + level / 2, point.second + level / 2}, level / 2, grid);
        } else {
            topLeft = new Node(grid[point.second - 1][point.first - 1], true);
            topRight = new Node(grid[point.second - 1][point.first], true);
            bottomLeft = new Node(grid[point.second][point.first - 1], true);
            bottomRight = new Node(grid[point.second][point.first], true);
        }
        vector<bool> valArray{topLeft->val, topRight->val, bottomLeft->val, bottomRight->val};
        unordered_set<bool> valSet(valArray.begin(), valArray.end());
        if (valSet.size() == 1 && topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->topRight) {
            return new Node(topLeft->val, true);
        } else {
            return new Node(true, false, topLeft, topRight, bottomLeft, bottomRight);
        }
    }

    Node* construct(vector<vector<int>>& grid) {
        return traverseSubnet({grid.size() / 2, grid.size() / 2}, grid.size() / 2, grid);
    }
};

int main()
{
    vector<vector<int>> grid{{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0}};
    Solution sol;
    sol.construct(grid);
    return 0;
}
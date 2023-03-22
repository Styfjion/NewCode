//
// Created by yangf on 2023/3/22.
//
#include <algorithm>

using namespace std;

struct Player {
    int score;
    int age;

    Player(int score, int age) : score(score), age(age) {}
};

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        if (scores.size() == 1) {
            return scores.front();
        }
        vector<Player> players;
        for (size_t i = 0; i < scores.size(); i++) {
            players.emplace_back(scores[i], ages[i]);
        }

        sort(players.begin(), players.end(), [](auto &&player1, auto&& player2){
            if (player1.score != player2.score) {
                return player1.score > player2.score;
            }
            return player1.age > player2.age;
        });
        int curScore = 0;
        int stop_pos = 0;
        for (size_t i = 0; i < )
    }
};
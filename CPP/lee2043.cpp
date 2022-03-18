//
// Created by yangf on 2022/3/18.
//
#include <vector>
#include <iostream>

using namespace std;

class Bank {
public:
    Bank(vector<long long>& balance) {
        this->balance = balance;
    }

    bool transfer(int account1, int account2, long long money) {
        if (account1 > balance.size() || account2 > balance.size()) {
            return false;
        }
        if (money > balance[account1 - 1]) {
            return false;
        }
        balance[account1 - 1] -= money;
        balance[account2 - 1] += money;
        return true;
    }

    bool deposit(int account, long long money) {
        if (account > balance.size()) {
            return false;
        }
        balance[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money) {
        if (account > balance.size()) {
            return false;
        }
        if (money > balance[account - 1]) {
            return false;
        }
        balance[account - 1] -= money;
        return true;
    }

private:
    vector<long long> balance;
};
//
// Created by y00564656 on 2023/2/25.
//
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

using namespace std;

class Data {
public:
    Data(){}
    Data(int id, string name) : m_id(id), m_name(std::move(name)) {}

    void show() {
        cout << "now id :" << m_id << " name: " << m_name;
        cout << " data: " << Data::trans(m_data) << endl;
    }

    static string trans(vector<int> &data) {
        vector<string> show;
        transform(data.begin(), data.end(),
                  back_inserter(show), [](int unit) { return to_string(unit); });
        return boost::algorithm::join(show, ",");
    }

    int m_id;
    string m_name;
    vector<int> m_data;
};

void changeVal(Data &data) {
    data.m_id++;
    data.m_name += "post";
}

void setListByRef(vector<int> &data) {
    data.push_back(1);
    data.push_back(2);
    data = vector<int>();
    data.push_back(3);
    cout << "new ref data is " << Data::trans(data) << endl;
}

void setListByPoint(vector<int>* data_ptr) {
    data_ptr->push_back(1);
    data_ptr->push_back(2);

    auto new_data = vector<int>();
    data_ptr = &new_data;
    data_ptr->push_back(3);
    cout << "new point data is " << Data::trans(*data_ptr) << endl;
}

int main() {
    unordered_map<int, Data> dict{{1, Data(1, "test1")},
                                  {2, Data(2, "test2")}};
    for (auto &&item: dict) {
        changeVal(item.second);
    }

    for (auto &&item: dict) {
        item.second.show();
    }

    setListByRef(dict[1].m_data);
    dict[1].show();

    setListByPoint(&dict[2].m_data);
    dict[2].show();
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& attr, int begin, int mid, int end) {
    vector<int> temp(end - begin + 1);
    int point1 = begin, point2 = mid + 1, point = 0;
    while (point1 <= mid && point2 <= end) {
        if (attr[point1] < attr[point2]) {
            temp[point++] = attr[point1++];
        } else {
            temp[point++] = attr[point2++];
        }
    }

    while (point1 <= mid)
    {
        temp[point++] = attr[point1++];
    }

    while (point2 <= end)
    {
        temp[point++] = attr[point2++];
    }
    
    for(int i = 0; i < temp.size(); i++) {
        attr[begin + i] = temp[i];
    }
}

void mergeSort(vector<int>& attr, int begin, int end) {
    if (begin >= end) {
        return;
    }

    int mid = (begin + end) / 2;
    mergeSort(attr, begin, mid);
    mergeSort(attr, mid + 1, end);
    merge(attr, begin, mid, end);
}

int main() {
    vector<int> data = {5, 2, 4, 7, 1, 3, 2, 6, 6, 20};
    mergeSort(data, 0, data.size() - 1);
    for(int num : data) {
        cout << num << " ";
    }
    cout << endl;
}
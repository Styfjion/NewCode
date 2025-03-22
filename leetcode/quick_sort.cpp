#include <iostream>
#include <vector>

using namespace std;

int patition(vector<int>&attr, int begin, int end) {
    int pivot = attr[begin];
    int left = begin, right = end;
    while (left < right) {
        while (left < right && attr[right] >= pivot) {
            right--;
        }

        while (left < right && attr[left] <= pivot) {
            left++;
        }

        if (left < right) {
            swap(attr[left], attr[right]);
        }
    }
    swap(attr[left], attr[begin]);
    return left;
}

void quickSort(vector<int>&attr, int begin, int end) {
    if (begin >= end) {
        return;
    }

    int pivot = patition(attr, begin, end);
    quickSort(attr, begin, pivot - 1);
    quickSort(attr, pivot + 1, end);
}

int main() {
    vector<int> data = {5, 2, 4, 7, 1, 3, 2, 6, 6, 20};
    quickSort(data, 0, data.size() - 1);
    for(int num : data) {
        cout << num << " ";
    }
    cout << endl;
}
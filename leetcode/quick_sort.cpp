#include <iostream>
#include <vector>

using namespace std;

int patition(vector<int>&attr, int begin, int end) {
    int pivot = attr[begin];
    int left = begin + 1, right = end;
    while (true) {
        while (left <= end && attr[left] < pivot) {
            left++;
        }
        while (right >= begin + 1 && attr[right] > pivot) {
            right--;
        }
        if (left <= right) {
            swap(attr[left], attr[right]);
            left += 1;
            right -= 1;
        } else {
            break;
        }
    }
    swap(attr[right], attr[begin]);
    return right;
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

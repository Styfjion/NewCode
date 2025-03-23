#include <vector>
#include <iostream>

using namespace std;

void heapfy(vector<int> &attr, int heapSize, int root)
{
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    int largest = root;
    if (left < heapSize && attr[left] > attr[largest])
    {
        largest = left;
    }
    if (right < heapSize && attr[right] > attr[largest])
    {
        largest = right;
    }

    if (largest != root)
    {
        swap(attr[root], attr[largest]);
        heapfy(attr, heapSize, largest);
    }
}

void heapfySort(vector<int> &attr)
{
    for (int i = attr.size() / 2 - 1; i >= 0; i--)
    {
        heapfy(attr, attr.size(), i);
    }

    for (int i = attr.size() - 1; i > 0; i--)
    {
        swap(attr[0], attr[i]);
        heapfy(attr, i, 0);
    }
}

int main() {
    vector<int> data = {5, 2, 4, 7, 1, 3, 2, 6, 6, 20};
    heapfySort(data);
    for(int num : data) {
        cout << num << " ";
    }
    cout << endl;
}

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::list;
using std::vector;

void printVector(vector<int>& vec)
{
    for (int i = 0; i < vec.size() - 1; i++) {
        cout << vec[i] << " ";
    }
    if (vec.size() - 1 >= 0) {
        cout << vec.back() << endl;
    }
}

bool insertionSort(vector<int>& container, vector<int>& target)
{
    bool isMatch = false;
    for (int sortedSize = 1; sortedSize < container.size(); sortedSize++) {
        int curr = container[sortedSize];
        int i;
        for (i = sortedSize - 1; i >= 0 && container[i] > curr; i--) {
            container[i + 1] = container[i];
        }
        container[i + 1] = curr;

        //关键代码
        if (isMatch) {
            cout << "Insertion Sort\n";
            printVector(container);
            break;
        }
        if (container == target) {
            isMatch = true;
        }
    }
    return isMatch;
}
bool heapSort(vector<int>& container,vector<int>& target)
{
    std::make_heap(container.begin(), container.end()); //默认是大顶堆
    auto itr = container.end();
    bool isMatch=false;
    while (itr != container.begin() + 1) {
        std::pop_heap(container.begin(), itr);
        itr--;
        if (isMatch) {
            cout << "Heap Sort\n";
            printVector(container);
            break;
        }
        if (container == target) {
            isMatch = true;
        }
    }
    return isMatch;
}
int main()
{
    int numOfElements;
    cin >> numOfElements;
    vector<int> originalSeq {};
    vector<int> originalSeq2 {};
    int temp;
    for (int i = 0; i < numOfElements; i++) {
        cin >> temp;
        originalSeq.push_back(temp);
        originalSeq2.push_back(temp);
    }
    vector<int> targetSeq {};
    for (int i = 0; i < numOfElements; i++) {
        cin >> temp;
        targetSeq.push_back(temp);
    }
    if (!heapSort(originalSeq, targetSeq)) {
        insertionSort(originalSeq2, targetSeq);
    }
}
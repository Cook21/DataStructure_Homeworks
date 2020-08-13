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

void popSort(vector<int>& container)
{
    bool isSwapedThisRound = true;
    for (int i = 0; i < container.size() - 1 && isSwapedThisRound; i++) {
        isSwapedThisRound = false;
        for (int j = 0; j < container.size() - 1 - i; j++) {
            if (container[j] > container[j + 1]) {
                int temp = container[j];
                container[j] = container[j + 1];
                container[j + 1] = temp;
                isSwapedThisRound = true;
            }
        }
    }
}
void insertionSort(vector<int>& container)
{
    for (int sortedSize = 1; sortedSize < container.size(); sortedSize++) {
        int curr = container[sortedSize];
        int i;
        for (i = sortedSize - 1; i >= 0 && container[i] > curr; i--) {
            container[i + 1] = container[i];
        }
        container[i + 1] = curr;
    }
}
void shellSort(vector<int>& container)
{
    //Hibbard增量序列
    for (int delta = pow(2, floor(log(container.size()) / log(2))-1) - 1; delta > 0; delta = (delta-1)/2) {
        //cout << "delta:" << delta << endl;
        for (int sortedSize = delta; sortedSize < container.size(); sortedSize++) {
            int curr = container[sortedSize];
            int i;
            for (i = sortedSize - delta; i >= 0 && container[i] > curr; i -= delta) {
                container[i + delta] = container[i];
            }
            container[i + delta] = curr;
        }
    }
}
void heapSort(vector<int>& container)
{
    std::make_heap(container.begin(), container.end()); //默认是大顶堆
    auto itr = container.end();
    while (itr != container.begin() + 1) {
        std::pop_heap(container.begin(), itr);
        itr--;
    }
}
void merge(vector<int>& A, vector<int>& B, int leftStart, int rightStart, int rightEnd)
{
    int leftEnd = rightStart;
    int BStart = leftStart;
    while (leftStart < leftEnd && rightStart < rightEnd) {
        if (A[leftStart] < A[rightStart]) {
            B[BStart] = A[leftStart];
            leftStart++;
            BStart++;
        } else {
            B[BStart] = A[rightStart];
            rightStart++;
            BStart++;
        }
    }
    while (leftStart < leftEnd) {
        B[BStart] = A[leftStart];
        leftStart++;
        BStart++;
    }
    while (rightStart < rightEnd) {
        B[BStart] = A[rightStart];
        rightStart++;
        BStart++;
    }
}
void mergeSort(vector<int>& container)
{
    vector<int> tempContainer(container.size());
    int sortedSize = 1;
    bool isInContainer = true;
    while (sortedSize < container.size()) {
        for (int i = 0; i < container.size(); i += sortedSize * 2) {
            int rightStart = i + sortedSize;
            int rightEnd = rightStart + sortedSize;
            if (rightStart > container.size()) {
                rightStart = container.size();
            }
            if (rightEnd > container.size()) {
                rightEnd = container.size();
            }
            if (isInContainer) {
                merge(container, tempContainer, i, rightStart, rightEnd);
            } else {
                merge(tempContainer, container, i, rightStart, rightEnd);
            }
        }
        isInContainer = !isInContainer;
        sortedSize *= 2;
    }
    if (!isInContainer) {
        container = tempContainer;
    }
}
int main()
{
    int numOfNums;
    cin >> numOfNums;
    vector<int> container {};
    for (int i = 0; i < numOfNums; i++) {
        int temp;
        cin >> temp;
        container.push_back(temp);
    }
    //popSort(container);
    //insertionSort(container);
    //shellSort(container);
    //heapSort(container);
    mergeSort(container);
    for (auto i = container.begin(); i < container.end(); i++) {
        if (i != container.end() - 1) {
            cout << *i << " ";
        } else {
            cout << *i;
        }
    }
}
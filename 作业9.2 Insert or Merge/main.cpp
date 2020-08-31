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
bool mergeSort(vector<int>& container, vector<int>& target)
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
        if (isInContainer) {
            //关键代码
            if (container == target && sortedSize != 1) {
                cout << "Merge Sort\n";
                printVector(tempContainer);
                return true;
            }
        } else {
            //关键代码
            if (tempContainer == target) {
                cout << "Merge Sort\n";
                printVector(container);
                return true;
            }
        }
        isInContainer = !isInContainer;
        sortedSize *= 2;
    }
    if (!isInContainer) {
        container = tempContainer;
    }
    return false;
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
    if (!mergeSort(originalSeq, targetSeq)) {
        insertionSort(originalSeq2, targetSeq);
    }
}
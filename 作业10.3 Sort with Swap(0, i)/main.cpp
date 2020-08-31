#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::stable_sort;
using std::vector;
int main()
{
    int numOfElements;
    cin >> numOfElements;
    vector<int> nextElemIndex(numOfElements);
    vector<bool> isChecked(numOfElements, false);
    for (int i = 0; i < numOfElements; i++) {
        int input;
        cin >> input;
        nextElemIndex[input] = i;
    }
    int numOfSwap = 0;
    for (int head = 0; head < numOfElements; head++) {
        if (!isChecked[head]) {
            isChecked[head] = true;
            int curr = head;
            int loopSize = 1;
            while (nextElemIndex[curr] != head) {
                curr = nextElemIndex[curr];
                isChecked[curr] = true;
                loopSize++;
            }
            if (loopSize > 1) {
                if (head == 0) {
                    numOfSwap += loopSize - 1;
                } else {
                    numOfSwap += loopSize + 1;
                }
            }
        }
    }
    cout << numOfSwap << endl;
}
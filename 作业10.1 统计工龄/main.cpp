#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
    int numOfEmployee;
    cin >> numOfEmployee;
    vector<int> countTable(51, 0);
    int curr;
    for (int i = 0; i < numOfEmployee; i++) {
        cin >> curr;
        countTable[curr]++;
    }
    for (int i = 0; i < countTable.size(); i++) {
        if (countTable[i] > 0) {
            cout << i << ":" << countTable[i] << endl;
        }
    }
}
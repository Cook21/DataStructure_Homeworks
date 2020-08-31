#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
int main()
{
    int numOfRecords;
    cin >> numOfRecords;
    unordered_map<long long, int> hashTable {};
    hashTable.reserve(3*numOfRecords);
    for (int i = 0; i < numOfRecords * 2; i++) {
        long long phoneNum;
        cin >> phoneNum;
        hashTable[phoneNum]++;
    }
    long long madmanNumber = 99999999999;
    int madManCallTimes = -1;
    int madManCount = 0;
    for (auto it : hashTable) {
        if (it.second > madManCallTimes) {
            madManCallTimes = it.second;
            madmanNumber = it.first;
            madManCount = 1;
        } else if (it.second == madManCallTimes) {
            if (it.first < madmanNumber) {
                madManCallTimes = it.second;
                madmanNumber = it.first;
            }
            madManCount++;
        }
    }
    if (madManCount == 1) {
        cout << madmanNumber << " " << madManCallTimes;
    } else {
        cout << madmanNumber << " " << madManCallTimes << " " << madManCount;
    }
}
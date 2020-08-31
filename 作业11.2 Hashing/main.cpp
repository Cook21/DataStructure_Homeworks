#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
bool isPrime(int x)
{
    if (x == 1 || (x % 2 == 0 && x != 2)) {
        return false;
    } else {
        for (int i = 3; i <= sqrt(x) + 1; i += 2) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }
}
int nextPrime(int x)
{
    for (int i = x + 1;; i++) {
        if (isPrime(i)) {
            return i;
        }
    }
}
class HashTable {
    enum class Status {
        empty,
        occupied,
        deleted,
    };
    class TableElem {
    public:
        int key;
        Status status { Status::empty };
    };
    vector<TableElem> table;
    int hash(int key)
    {
        return key % table.size();
    }

public:
    HashTable(int size)
    {
        if (!isPrime(size)) {
            size = nextPrime(size);
        }
        table = vector<TableElem>(size);
    }
    int getIndex(int key)
    {
        int index = hash(key);
        int currIndex = index;
        int base = 1;
        while (table[index].status != Status::empty && !(table[index].status == Status::occupied && table[index].key == key)) {
            currIndex = index + base * base;
            currIndex %= table.size();
            base++;
        }
        return currIndex;
    }
    bool insert(int key)
    {
        int index = hash(key);
        int currIndex = index;
        int firstDeletedPos = -1;
        int base = 1;
        while (table[currIndex].status != Status::empty) {
            if(base>10000){
                cout << "-"; //题目要求
                return false;
            }
            if (table[currIndex].status == Status::occupied && table[currIndex].key == key) {
                return true;
            }
            if (table[currIndex].status == Status::deleted && firstDeletedPos == -1) {
                firstDeletedPos = currIndex;
            }
            currIndex = index + base * base;
            currIndex %= table.size();
            base++;
        }
        if (firstDeletedPos != -1) {
            currIndex = firstDeletedPos;
        }
        table[currIndex].key = key;
        cout << currIndex; //题目要求
        table[currIndex].status = Status::occupied;
        return true;
    }
};
int main()
{
    int userDefinedTableSize, numOfNums;
    cin >> userDefinedTableSize >> numOfNums;
    HashTable hashtable { userDefinedTableSize };
    for (int i = 0; i < numOfNums; i++) {
        int key;
        cin >> key;
        hashtable.insert(key);
        if (i != numOfNums - 1) {
            cout << " ";
        }
    }
}

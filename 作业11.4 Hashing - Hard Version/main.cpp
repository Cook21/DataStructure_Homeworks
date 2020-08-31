#include <algorithm>
#include <forward_list>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::forward_list;
using std::vector;
class HashTable { //没有删除操作
    enum class Status {
        empty,
        occupied,
    };
    class TableElem {
    public:
        int key;
        Status status { Status::empty };
    };
    int hash(int key)
    {
        return key % table.size();
    }
    vector<TableElem> table;

public:
    HashTable(int size)
    {
        table = vector<TableElem>(size);
    }
    int getIndex(int key)
    {
        int index = hash(key);
        while (table[index].status != Status::empty && !(table[index].status == Status::occupied && table[index].key == key)) {
            index++;
            index %= table.size();
        }
        return index;
    }
    void insertToIndex(int key, int index)
    {
        table[index].key = key;
        table[index].status = Status::occupied;
    }
};
class TableElem {
public:
    int key;
    int index;
    bool operator<(const TableElem& a) const
    {
        return key < a.key;
    }
};

int main()
{
    int hashTableSize;
    cin >> hashTableSize;
    forward_list<TableElem> table {};
    for (int index = 0; index < hashTableSize; index++) {
        int key;
        cin >> key;
        if (key >= 0) {
            table.push_front(TableElem { key, index });
        }
    }
    table.sort();
    /*
    for (auto curr = table.before_begin(); std::next(curr)!=table.end(); curr++) {
        cout << std::next(curr)->key << " " << std::next(curr)->index << endl;
    }
    */
    HashTable hashtable{ hashTableSize };
    vector<int> originalSequence {};
    while (!table.empty()) {
        for (auto curr = table.before_begin(); std::next(curr) != table.end(); curr++) {
            auto next = std::next(curr);
            if (next->index == hashtable.getIndex(next->key)) {
                hashtable.insertToIndex(next->key, next->index);
                originalSequence.push_back(next->key);
                table.erase_after(curr);
                break;
            }
        }
    }
    for (int i = 0; i < originalSequence.size(); i++) {
        if (i != 0) {
            cout << " " << originalSequence[i];
        } else {
            cout << originalSequence[i];
        }
    }
}
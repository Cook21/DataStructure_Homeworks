/*
1.验证是否为前缀码
2.计算编码长度, 构造哈夫曼树计算最小编码长度, 验证编码长度是否最小
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class BinaryEncodeTree {
public:
    char character = '0'; //代表无内容
    int frequency = 0;
    BinaryEncodeTree* left = nullptr;
    BinaryEncodeTree* right = nullptr;
    int insert(char character, int frequency, string code)
    { //0表示成功

        if (this->character != '0') {
            return -1;
        }
        BinaryEncodeTree** next;
        if (code[0] == '0') {
            next = &left;
        } else {
            next = &right;
        }
        if (code.size() == 1) {
            if (*next != nullptr) {
                return -1;
            } else {
                *next = new BinaryEncodeTree(BinaryEncodeTree { character, frequency });
                return 0;
            }
        } else {
            code.erase(0, 1);
            //cout << character <<":"<<code <<endl;
            if (*next == nullptr) {
                *next = new BinaryEncodeTree(BinaryEncodeTree {});
            }
            return (**next).insert(character, frequency, code);
        }
    }
    bool operator>=(const BinaryEncodeTree& tree) const
    {
        return frequency >= tree.frequency;
    }
    int pathLength(int currDepth = 0)
    {

        int result = 0;
        if (character != '0') {
            result = currDepth * frequency;
        } else {
            if (left != nullptr) {
                result += left->pathLength(currDepth + 1);
            }
            if (right != nullptr) {
                result += right->pathLength(currDepth + 1);
            }
        }
        return result;
    }
};
bool greater(const BinaryEncodeTree& t1, const BinaryEncodeTree& t2)
{
    return t1 >= t2;
}
BinaryEncodeTree buildHuffmanTree(vector<BinaryEncodeTree> allTree)
{
    std::make_heap(allTree.begin(), allTree.end(), greater);
    while (allTree.size() > 1) {
        BinaryEncodeTree temp {};
        temp.left = new BinaryEncodeTree(allTree.front());
        temp.frequency += allTree.front().frequency;
        std::pop_heap(allTree.begin(), allTree.end(), greater);
        allTree.pop_back();
        temp.right = new BinaryEncodeTree(allTree.front());
        temp.frequency += allTree.front().frequency;
        std::pop_heap(allTree.begin(), allTree.end(), greater);
        allTree.pop_back();
        allTree.push_back(temp);
        std::push_heap(allTree.begin(), allTree.end(), greater);
    }
    return allTree[0];
}
int main()
{
    int numOfCharacter;
    cin >> numOfCharacter;
    map<char, int> frequencyTable {};
    vector<BinaryEncodeTree> AllHuffmanTreeNode {};
    for (int i = 0; i < numOfCharacter; i++) {
        char character;
        int frequency;
        cin >> character >> frequency;
        AllHuffmanTreeNode.push_back(BinaryEncodeTree { character, frequency });
        frequencyTable[character] = frequency;
    }
    BinaryEncodeTree huffmanTree = buildHuffmanTree(AllHuffmanTreeNode);
    //cout << huffmanTree.pathLength(0);
    int numOfSubmission;
    cin >> numOfSubmission;
    std::stringstream sstream;
    for (int i = 0; i < numOfSubmission; i++) {
        BinaryEncodeTree currTree {};
        int success = 0;
        for (int i = 0; i < numOfCharacter; i++) {
            char character;
            string code {};
            cin >> character >> code;
            int currSuccess = currTree.insert(character, frequencyTable[character], code);
            if (currSuccess != 0) {
                success = -1;
            }
        }
        if (success == 0 && currTree.pathLength() == huffmanTree.pathLength()) {
            sstream << "Yes" << endl;
        } else {
            sstream << "No" << endl;
        }
    }
    cout << sstream.str();
}
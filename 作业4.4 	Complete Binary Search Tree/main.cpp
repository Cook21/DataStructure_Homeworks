#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
class CompleteBinaryTree {
public:
    vector<int> data {};

    void levelOrderTraversal()
    {
        if (data.size() > 0) {
            cout << data[0];
            for (int i = 1; i < data.size(); i++) {
                cout << ' ' << data[i];
            }
        }
    }
    int getLeftSize(int parentSize)
    {
        int height = std::log2(parentSize + 1) + 1;
        int numOfLastLevelElements = parentSize - (pow(2, height - 1) - 1);
        return pow(2, height - 2) - 1 + std::min(numOfLastLevelElements, (int)pow(2, height - 2));
    }
    void build(int tree, vector<int>& input, int beg, int end) //end指向末尾的下一个元素
    {
        if (end - beg > 0) {
            int mid = beg + getLeftSize(end - beg);
            data[tree] = input[mid];
            build(tree * 2 + 1, input, beg, mid);
            build(tree * 2 + 2, input, mid + 1, end);
        }
    }
    void initialize()
    {
        int numOfNodes;
        cin >> numOfNodes;
        vector<int> input;
        for (int i = 0; i < numOfNodes; i++) {
            int temp;
            cin >> temp;
            input.push_back(temp);
        }
        std::sort(input.begin(), input.end());
        data.resize(numOfNodes);
        build(0, input, 0, input.size());
    }
};
int main()
{
    CompleteBinaryTree CBT {};
    //cout<< CBT.getLeftSize(4) << ' ' << CBT.getLeftSize(7) << endl;
    CBT.initialize();
    CBT.levelOrderTraversal();
}
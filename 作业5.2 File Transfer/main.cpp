#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
class setTree {
public:
    vector<int> parentOf;
    setTree(int size)
    {
        parentOf = vector<int>(size, -1);
    }
    int findRoot(int currNode)
    {
        while (parentOf[currNode] >= 0) {
            currNode = parentOf[currNode];
        }
        return currNode;
    }
    void connect(int a, int b)
    {
        int rootOfa = findRoot(a);
        int rootOfb = findRoot(b);
        if (parentOf[rootOfa] < parentOf[rootOfb]) { //a所属集合的元素较多
            parentOf[rootOfa] += parentOf[rootOfb];
            parentOf[rootOfb] = rootOfa;
        } else {
            parentOf[rootOfb] += parentOf[rootOfa];
            parentOf[rootOfa] = rootOfb;
        }
    }
    int numOfComponents()
    {
        int numOfComponents = 0;
        for (auto i : parentOf) {
            //cout << i << " ";
            if (i < 0) {
                numOfComponents ++;
            }
        }
        //cout << endl;
        return numOfComponents;
    }
};

int main()
{
    int numOfNodes;
    cin >> numOfNodes;
    setTree set { numOfNodes };
    string op {};
    std::stringstream out {};
    for (cin >> op; op != "S"; cin >> op) {
        int a, b;
        cin >> a >> b;
        if (op == "I") {
            set.connect(a - 1, b - 1);
        } else if (op == "C") {
            if (set.findRoot(a - 1) == set.findRoot(b - 1)) {
                out << "yes" << endl;
            } else {
                out << "no" << endl;
            }
        }
    }
    if (set.numOfComponents() == 1) {
        out << "The network is connected.";
    } else {
        out << "There are " << set.numOfComponents() << " components.";
    }
    cout << out.str();
}
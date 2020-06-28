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
    int data;
    int parent = -1;
    static vector<setTree> table;
    int find(int a)
    {
        for (int i = 0; i < table.size(); i++) {
            if (table[i].data == a) {
                int root;
                for (root=i; table[root].parent >= 0; root = table[root].parent)
                    ;
                return root;
            }
        }
        return -1;
    }
    void connect(int a, int b)
    {
        int rootOfa = find(a);
        int rootOfb = find(b);
        if (table[rootOfa].parent < table[rootOfb].parent) { //a所属集合的元素较多
            table[rootOfa].parent += table[rootOfb].parent;
            table[rootOfb].parent = rootOfa;
        } else {
            table[rootOfb].parent += table[rootOfa].parent;
            table[rootOfa].parent = rootOfb;
        }
    }
    int numOfComponents()
    {
        int numOfComponents = 0;
        for (auto i : setTree::table) {
            if (i.parent < 0) {
                numOfComponents++;
            }
        }
        return numOfComponents;
    }
};
vector<setTree> setTree::table {};
int main()
{
    int numOfNodes;
    cin >> numOfNodes;
    for (int i = 1; i <= numOfNodes; i++) {
        setTree::table.push_back(setTree { i });
    }
    setTree set {};
    string op {};
    std::stringstream out {};
    for (cin >> op; op != "S"; cin >> op) {
        int a, b;
        cin >> a >> b;
        if (op == "I") {
            set.connect(a, b);
        } else if (op == "C") {
            if (set.find(a) == set.find(b)) {
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
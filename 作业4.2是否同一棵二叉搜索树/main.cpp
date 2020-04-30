#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class BinSearchTree {
private:
    struct Node {
        int data;
        struct Node* left;
        struct Node* right;
    };
    void insert(int data, struct Node*& tree)
    {
        if (tree == nullptr) {
            tree = new (struct Node) { data, nullptr, nullptr };
        } else {
            if (data < tree->data) {
                //cout << "left\n"; //check point
                insert(data, tree->left);
            } else if (data > tree->data) {
                //cout << "right\n"; //check point
                insert(data, tree->right);
            }
        }
        return;
    }
    struct Node* bulidTree(int n, int input[10])
    {
        struct Node* newTree = nullptr;
        for (int i = 0; i < n; i++) {
            insert(input[i], newTree);
        }
        return newTree;
    }
    bool isSame(struct Node* tree1, struct Node* tree2)
    {
        if (tree1 == nullptr && tree2 == nullptr) {
            return true;
        } else if (tree1 == nullptr || tree2 == nullptr) {
            return false;
        } else if (tree1->data != tree2->data) {
            return false;
        } else {
            return isSame(tree1->left, tree2->left) && isSame(tree1->right, tree2->right);
        }
    }
    void preTraversal(struct Node* tree)
    {
        if (tree != nullptr) {
            cout << tree->data << ' ';
            preTraversal(tree->left);
            preTraversal(tree->right);
        }
        return;
    }

public:
    void getInput()
    {
        int n; //插入元素个数
        int l; //检查序列个数
        while (true) {
            cin >> n;
            if (n == 0) {
                break;
            }
            cin >> l;
            int input[10];
            for (int i = 0; i < n; i++) {
                cin >> input[i];
            }
            struct Node* tree0 = bulidTree(n, input);
            for (int i = 0; i < l; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> input[j];
                }
                if (!isSame(tree0, bulidTree(n, input))) {
                    cout << "No\n";
                }else{
                    cout << "Yes\n";
                }
            }
            //preTraversal(tree0); //check point
        }
    }
};
int main()
{
    BinSearchTree b;
    b.getInput();
    return 0;
}
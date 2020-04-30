#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class BinTree {
private:
    struct Node {
        char data;
        struct Node* left;
        struct Node* right;
    };
    struct Node* ta;
    struct Node* tb;
    struct Node* createTree(char a[10][3], int n)
    {
        bool child[10] = { false };
        for (int i = 0; i < n; i++) {
            if (a[i][1] != '-') {
                child[a[i][1] - '0'] = true;
            }
            if (a[i][2] != '-') {
                child[a[i][2] - '0'] = true;
            }
        }
        int rootIndex = -1;
        for (int i = 0; i < n && rootIndex == -1; i++) {
            if (child[i] == false) {
                rootIndex = i;
            }
        }
        struct Node* rootNode = nullptr;
        if (n > 0) {
            rootNode = createTreeHelper(a, rootIndex);
        }
        return rootNode;
    }
    struct Node* createTreeHelper(char a[10][3], int i)
    {
        struct Node* newNode = new (struct Node) { a[i][0], nullptr, nullptr };
        if (a[i][1] != '-') {
            newNode->left = createTreeHelper(a, a[i][1] - '0');
        }
        if (a[i][2] != '-') {
            newNode->right = createTreeHelper(a, a[i][2] - '0');
        }
        return newNode;
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
    bool isSimilar(struct Node* tree1, struct Node* tree2)
    {
        if (tree1 == nullptr && tree2 == nullptr) {
            return true;
        } else if (tree1 == nullptr || tree2 == nullptr) {
            return false;
        } else if (tree1->data == tree2->data && isSimilar(tree1->left, tree2->left) && isSimilar(tree1->right, tree2->right)) {
            return true;
        } else if (tree1->data == tree2->data && isSimilar(tree1->left, tree2->right) && isSimilar(tree1->right, tree2->left)) {
            return true;
        } else {
            return false;
        }
    }

public:
    void getInput()
    {
        int n;
        char a[10][3];
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i][0] >> a[i][1] >> a[i][2];
        }
        ta = createTree(a, n);

        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i][0] >> a[i][1] >> a[i][2];
        }
        tb = createTree(a, n);
        //cout << "create complete!\n";
        //preTraversal(ta);
        //preTraversal(tb);
        return;
    }
    void judge()
    {
        if (isSimilar(ta, tb)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
};
int main()
{
    BinTree t;
    t.getInput();
    t.judge();
    return 0;
}
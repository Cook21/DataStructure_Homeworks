#include <deque>
#include <iostream>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
class BinTree {
private:
    struct Node {
        int data; //表示这节点对应数列里第几行
        struct Node* left;
        struct Node* right;
    };
    struct Node* ta;
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
        struct Node* newNode = new (struct Node) { i, nullptr, nullptr };
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
    bool isLeave(struct Node* tree)
    {
        if (tree->left == nullptr && tree->right == nullptr) {
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
            cin >> a[i][1] >> a[i][2];
        }
        ta = createTree(a, n);
        //cout << "create complete!\n";
        //preTraversal(ta);
        return;
    }
    void levelOrderTraversal()
    {
        if (ta != nullptr) {
            deque<struct Node*> q;
            q.push_back(ta);
            struct Node* temp;
            bool printSpace = false;
            while (!q.empty()) {
                temp = q.front();
                q.pop_front();
                if (isLeave(temp)) {
                    if (printSpace) {
                        cout << ' ' << temp->data;
                    } else {
                        cout << temp->data;
                        printSpace = true;
                    }
                }
                if (temp->left) {
                    q.push_back(temp->left);
                }
                if (temp->right) {
                    q.push_back(temp->right);
                }
            }
        }
        return;
    }
};
int main()
{
    BinTree t;
    t.getInput();
    t.levelOrderTraversal();
    return 0;
}
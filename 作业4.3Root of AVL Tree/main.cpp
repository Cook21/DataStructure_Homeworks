#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class AVLTree {
private:
    struct Node {
        int data;
        struct Node* left;
        struct Node* right;
    };
    struct Node* insert(int data, struct Node* tree)
    {
        if (tree == nullptr) {
            tree = new (struct Node) { data, nullptr, nullptr };
        } else {
            if (data < tree->data) {
                tree->left = insert(data, tree->left);
                if (getHeight(tree->left) - getHeight(tree->right) > 1) { //检测到不平衡
                    if (data > tree->left->data) { //LR旋转
                        struct Node* temp = tree->left;
                        tree->left = temp->right->right;
                        temp->right->right = tree;
                        tree = temp->right;
                        temp->right = tree->left;
                    } else { //LL旋转
                        struct Node* temp = tree->left;
                        tree->left = temp->right;
                        temp->right = tree;
                        tree = temp;
                    }
                }
            } else if (data > tree->data) {
                tree->right = insert(data, tree->right);
                if (getHeight(tree->right) - getHeight(tree->left) > 1) { //检测到不平衡
                    if (data < tree->right->data) { //RL旋转
                        struct Node* temp = tree->right;
                        tree->right = temp->left->left;
                        temp->left->left = tree;
                        tree = temp->left;
                        temp->left = tree->right;
                    } else { //RR旋转
                        struct Node* temp = tree->right;
                        tree->right = temp->left;
                        temp->left = tree;
                        tree = temp;
                    }
                }
            }
        }
        return tree;
    }
    int getHeight(struct Node* tree)
    {
        if (tree == NULL) {
            return 0;
        } else {
            return std::max(getHeight(tree->left) + 1, getHeight(tree->right) + 1);
        }
    }

public:
    void getInput()
    {
        int n = 0;
        cin >> n;
        struct Node* root = nullptr;
        int temp;
        for (int i = 0; i < n; i++) {
            //cin >> temp;
            root = insert(i, root);
            //cout << "insert complete!\n"; //check point
            //cout << root->data << endl; //check point
        }
        if (root) {
            cout << root->data;
        }
    }
};
int main()
{
    AVLTree tree;
    tree.getInput();
    return 0;
}
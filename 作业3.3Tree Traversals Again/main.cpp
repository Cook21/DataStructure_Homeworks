#include <cstdio>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::string;
using std::vector;
using namespace std::string_literals;
class BinTree {
private:
    struct Node {
        int data;
        struct Node* left;
        struct Node* right;
    };
    struct Node* ta;
    void preTraversal(struct Node* tree)
    {
        if (tree != nullptr) {
            cout << tree->data << ' ';
            preTraversal(tree->left);
            preTraversal(tree->right);
        }
        return;
    }
    void postTraversal(struct Node* tree)
    {
        if (tree != nullptr && tree == ta) {
            postTraversal(tree->left);
            postTraversal(tree->right);
            cout << tree->data;
        } else if (tree != nullptr) {
            postTraversal(tree->left);
            postTraversal(tree->right);
            cout << tree->data << ' ';
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
        cin >> n;
        getchar();
        string input[60];
        for (int i = 0; i < 2 * n; i++) {
            getline(cin, input[i]);
        }
        vector<struct Node*> stack;
        *ta = { stoi(input[0].substr(5)), nullptr, nullptr };
        stack.push_back(ta);
        struct Node** curr = &ta->left;
        for (int i = 1; i < 2 * n; i++) {
            if (input[i].substr(0, 4).compare("Push"s) == 0) {
                //cout << "push\n"; //测试点
                *curr = new (struct Node) { stoi(input[i].substr(5)), nullptr, nullptr };
                stack.push_back(*curr);
                curr = &(*curr)->left;
            } else if (input[i].substr(0, 3).compare("Pop"s) == 0) {
                //cout << "pop\n"; //测试点
                curr = &(stack.back())->right;
                stack.pop_back();
            }
        }
        //cout << "create complete!\n"; //测试点
        postTraversal(ta); 
        return;
    }
};
int main()
{
    BinTree t;
    t.getInput();
    return 0;
}
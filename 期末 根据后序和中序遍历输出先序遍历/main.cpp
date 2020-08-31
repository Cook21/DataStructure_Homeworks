#include <deque>
#include <iostream>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
class BinSearchTree {
private:
    struct Node {
        int data;
        struct Node* left;
        struct Node* right;
    };
    struct Node* bulidTree(deque<int>& inOrder, int inOrderLeft, int inOrderRight, deque<int>& postOrder, int postOrderLeft, int postOrderRight)
    {
        if (inOrderRight >= inOrderLeft) {
            int rootContent = postOrder[postOrderRight];
            int mid = inOrderLeft;
            while (inOrder[mid] != rootContent) {
                mid++;
            }
            int leftLength = mid - inOrderLeft;
            struct Node* leftTree = bulidTree(inOrder, inOrderLeft, mid - 1, postOrder, postOrderLeft, postOrderLeft + leftLength - 1);
            struct Node* rightTree = bulidTree(inOrder, mid + 1, inOrderRight, postOrder, postOrderLeft + leftLength, postOrderRight - 1);
            return new (struct Node) { rootContent, leftTree, rightTree };
        } else {
            return nullptr;
        }
    }
    void preTraversal(struct Node* tree)
    {
        if (tree != nullptr) {
            cout << ' '<< tree->data ;
            preTraversal(tree->left);
            preTraversal(tree->right);
        }
        return;
    }

public:
    void getInput()
    {
        int n; //插入元素个数
        cin >> n;
        deque<int> postOrder {};
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            postOrder.push_back(temp);
        }
        deque<int> inOrder {};
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            inOrder.push_back(temp);
        }
        struct Node* tree = bulidTree(inOrder, 0, n - 1, postOrder, 0, n - 1);
        cout << "Preorder:";
        preTraversal(tree); //check point
    }
};
int main()
{
    BinSearchTree b;
    b.getInput();
    return 0;
}
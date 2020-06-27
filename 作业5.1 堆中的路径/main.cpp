#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
class MinHeap {
public:
    vector<int> tree {};
    void sort(int root){
        int temp=tree[root];
        int curr = root;
        while (1) {
            int child = curr * 2 + 1;
            if (child >= tree.size()) {
                break;
            }
            if (child + 1 < tree.size() && tree[child] > tree[child + 1]) {
                child += 1;
            }
            if (tree[child] < temp) {
                tree[curr] = tree[child];
                curr = child;
            } else {
                break;
            }
        }
        tree[curr] = temp;
    }
    void initialize(vector<int> unsorted){
        tree=unsorted;
        int currTree=(tree.size()-1)/2;
        while(currTree!=-1){
            sort(currTree);
            currTree--;
        }
    }
    void push(int data)
    {
        tree.push_back(data);
        int curr = tree.size()-1;
        int parent = (curr-1) / 2;
        while (curr > 0 && tree[parent] > data) {
            tree[curr] = tree[parent];
            curr = parent;
            parent = (curr-1) / 2;
        }
        tree[curr] = data;
    }
    int pop()
    {
        int result = tree[0];
        tree[0] = tree.back();
        tree.pop_back();
        sort(0);
        return result;
    }
    void traverselToRoot(int start)
    {
        cout << tree[start];
        while (start != 0) {
            start =(start-1)/2;
            cout << ' ' << tree[start];
        }
    }
    void levelOrderTraversel(){
        for(auto i : tree){
            cout << i << " ";
        }
        cout << endl;
    }
};
int main()
{
    int numOfElement, numOfTraversel;
    cin >> numOfElement >> numOfTraversel;
    MinHeap minHeap{};
    //vector<int> input{};
    for (int i = 0; i < numOfElement; i++) {
        int temp;
        cin >> temp;
        minHeap.push(temp);
        //input.push_back(temp);
    }
    //minHeap.initialize(input);
    for (int i = 0; i < numOfTraversel; i++) {
        int temp;
        cin >> temp;
        minHeap.traverselToRoot(temp - 1);
        cout << endl;
    }
    //minHeap.levelOrderTraversel();
    //minHeap.pop();
    //minHeap.levelOrderTraversel();
}
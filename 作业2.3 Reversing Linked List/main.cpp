#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class List {
private:
    int numberOfNodes;
    struct Node {
        int Address;
        int Data;
        int Next;
        struct Node* PtrToNext;
    };
    struct Node* n;
    struct Node head;

public:
    int find(int Address, int numberOfInputNodes) //返回地址对应节点的下标
    {
        for (int i = 0; i < numberOfInputNodes; i++) {
            if (n[i].Address == Address) {
                return i;
            }
        }
        return -1; //-1表示没找到
    }
    List(int numberOfInputNodes, int adressOfFirstNode)
    {
        n = new struct Node[numberOfInputNodes]();
        int Address, Next;
        int Data;
        for (int i = 0; i < numberOfInputNodes; i++) {
            cin >> Address >> Data >> Next;
            n[i] = { Address, Data, Next };
        }
        this->numberOfNodes = 0;
        int curr = find(adressOfFirstNode, numberOfInputNodes);
        int next = -1;
        this->head = { 0, 0, adressOfFirstNode, &n[curr] };
        while (curr != -1) {
            next = find(n[curr].Next, numberOfInputNodes);
            if (next != -1) {
                n[curr].PtrToNext = &n[next];
                curr = next;
            } else {
                n[curr].PtrToNext = nullptr;
                curr = next;
            }
            this->numberOfNodes++;
        }
        //cout << "constructed " << this->numberOfNodes << " of legal nodes\n";
        return;
    }
    void print()
    {
        struct Node* curr = head.PtrToNext;
        while (curr != nullptr) {
            if (curr->PtrToNext == nullptr) {
                cout << std::setfill('0') << std::setw(5) << curr->Address << " " << curr->Data << " " << std::setw(2) << curr->Next << endl; //打印-1时不要填充
                break;
            }
            cout << std::setfill('0') << std::setw(5) << curr->Address << " " << curr->Data << " " << std::setw(5) << curr->Next << "\n";
            curr = curr->PtrToNext;
        }
        return;
    }
    void reverse(int reverseN)
    {
        if (reverseN < 2 || reverseN > this->numberOfNodes) {
            return;
        }
        //假设从1到reverseN号元素要被反向
        struct Node* left = &head;
        for (int i = 0; i < numberOfNodes / reverseN; i++) {
            struct Node* curr = left->PtrToNext; //指向1号元素
            struct Node* next = curr->PtrToNext; //指向2号元素
            //执行完下面的reverseN-1次for循环后, curr指向reverseN号元素, next指向reverseN+1号元素
            for (int j = 0; j < reverseN - 1; j++) {
                struct Node* temp = next->PtrToNext;
                next->PtrToNext = curr;
                next->Next = curr->Address;
                curr = next;
                next = temp;
            }
            //1号元素指向reverseN+1号元素
            left->PtrToNext->PtrToNext = next;
            if (next != nullptr) {
                left->PtrToNext->Next = next->Address;
            } else {
                left->PtrToNext->Next = -1;
            }
            //left指向reverseN号元素,left移到1号元素上, 由于已经被反向, 1号元素就是下一次循环的0号元素
            struct Node* temp = left->PtrToNext;
            left->PtrToNext = curr;
            left->Next = curr->Address;
            left = temp;
        }
    }
};
int main()
{
    int numberOfInputNodes, adressOfFirstNode, reverseN;
    cin >> adressOfFirstNode >> numberOfInputNodes >> reverseN;
    List L { numberOfInputNodes, adressOfFirstNode };
    L.reverse(reverseN);
    L.print();
    return 0;
}
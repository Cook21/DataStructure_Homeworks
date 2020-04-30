#include <chrono>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;

typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read()
{
    int n;
    cin >> n;
    List L = (List)malloc(sizeof(struct Node));
    PtrToNode curr = L;
    for (int i = 0; i < n; i++) {
        curr->Next = (List)malloc(sizeof(struct Node));
        curr = curr->Next;
        cin >> curr->Data;
    }
    curr->Next = nullptr;
    return L;
} /* 细节在此不表 */
void Print(List L)
{
    if (L->Next == nullptr) {
        cout << "NULL" << endl;
        return;
    }
    PtrToNode curr = L->Next;
    while (curr != nullptr) {
        cout << curr->Data << " ";
        curr = curr->Next;
    }
    cout << endl;
} /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    PtrToNode curr1 = L1->Next, curr2 = L2->Next;
    L1->Next = NULL;
    L2->Next = NULL;
    List L = (List)malloc(sizeof(struct Node));
    PtrToNode curr = L;
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->Data <= curr2->Data) {
            curr->Next = curr1;
            curr = curr->Next;
            curr1 = curr1->Next;
        } else {
            curr->Next = curr2;
            curr = curr->Next;
            curr2 = curr2->Next;
        }
    }
    if (curr1 != NULL) {
        curr->Next = curr1;
    } else if (curr2 != NULL) {
        curr->Next = curr2;
    }
    return L;
}
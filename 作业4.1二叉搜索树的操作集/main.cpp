#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree tree)
{
    if (tree != NULL) {
        printf("%d ", tree->Data);
        PreorderTraversal(tree->Left);
        PreorderTraversal(tree->Right);
    }
    return;
} /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree tree)
{
    if (tree != NULL) {
        PreorderTraversal(tree->Left);
        printf("%d ", tree->Data);
        PreorderTraversal(tree->Right);
    }
    return;
} /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    printf("1\n"); //check point
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    printf("\n delete %d\n", N); //check point
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Delete(BST, X);
        PreorderTraversal(BST); //check ponit
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
//函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针
BinTree Insert(BinTree BST, ElementType X)
{
    if (BST == NULL) {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    } else {
        if (X < BST->Data) {
            BST->Left = Insert(BST->Left, X);
        } else {
            BST->Right = Insert(BST->Right, X);
        }
    }
    return BST;
}

//函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针
Position Find(BinTree BST, ElementType X)
{
    if (BST == NULL || X == BST->Data) {
        return BST;
    } else if (X < BST->Data) {
        return Find(BST->Left, X);
    } else if (X > BST->Data) {
        return Find(BST->Right, X);
    }
}

//函数FindMin返回二叉搜索树BST中最小元结点的指针；
Position FindMin(BinTree BST)
{
    while (BST && BST->Left != NULL) {
        BST = BST->Left;
    }
    return BST;
}

//函数FindMin返回二叉搜索树BST中最大元结点的指针；
Position FindMax(BinTree BST)
{
    while (BST && BST->Right != NULL) {
        BST = BST->Right;
    }
    return BST;
}

//函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；
//如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
BinTree Delete(BinTree BST, ElementType X)
{
    if (BST == NULL) {
        printf("Not Found\n");
    } else if (X < BST->Data) {
        BST->Left = Delete(BST->Left, X);
    } else if (X > BST->Data) {
        BST->Right = Delete(BST->Right, X);
    } else {
        if (BST->Right != NULL) {
            BST->Data = FindMin(BST->Right)->Data;
            BST->Right = Delete(BST->Right, BST->Data);
        } else if (BST->Left != NULL) {
            BST->Data = FindMax(BST->Left)->Data;
            BST->Left = Delete(BST->Left, BST->Data);
        } else {
            free(BST);
            BST = NULL;
        }
    }
    return BST;
}
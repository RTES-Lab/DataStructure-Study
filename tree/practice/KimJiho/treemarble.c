#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num1, num2;

typedef struct BinaryTree {
    int Data;

    struct BinaryTree* LeftChild;
    struct BinaryTree* RightChild;
    struct BinaryTree* LeftSibling;
} Node;

Node* SBT_CreateNode(int NewData)
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    NewNode->LeftChild = NULL;
    NewNode->RightChild = NULL;
    NewNode->LeftSibling = NULL;
    NewNode->Data = NewData;
    return NewNode;
}

void SBT_AddNode(Node* Parent){
    scanf(" %d, %d", &num1, &num2);
    if ((num1 != -1)&&(num2 != -1)){
        Parent->LeftChild = SBT_CreateNode(num1);
        Parent->RightChild = SBT_CreateNode(num2);
        Parent->RightChild->LeftSibling = Parent->RightChild;
    }
    else if (num1 != -1){
        Parent->LeftChild = SBT_CreateNode(num1);
        if (Parent->LeftSibling != NULL){
        Parent->LeftChild->LeftSibling = Parent->LeftSibling->RightChild;
        }
    }
    else if (num2 != -1){ 
        Parent->RightChild = SBT_CreateNode(num2);
        if (Parent->LeftSibling != NULL){
        Parent->RightChild->LeftSibling = Parent->LeftSibling->RightChild;
        }
    }
    else{
        // Parent->LeftChild = SBT_CreateNode()
    }

}

int main(void){
    int Nodecount = 0;
    scanf(" %d", &Nodecount);

    Node* Tree = SBT_CreateNode(1);

    return 0;
}
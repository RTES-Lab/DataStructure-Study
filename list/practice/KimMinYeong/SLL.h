#include <stdlib.h>

typedef char* ElementType;

typedef struct tagNode
{
    ElementType Data;
    struct tagNode* NextNode;
} Node;


Node* SLL_CreateNode(ElementType NewData)
    {
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;   //  데이터를 저장한다. 
    NewNode->NextNode = NULL;  //  다음 노드에 대한 포인터는 NULL로 초기화 한다.   
                               // NextNode의 값이 NULL포인터이다. 
                               // 즉, 다음 노드가 없다.
    return NewNode;            //  노드의 주소를 반환한다. 
}

void SLL_DestroyNode(Node* Node)
{
    free(Node);
}

void SLL_AppendNode(Node** Head, Node* NewNode)
{
    //  헤드 노드가 NULL이라면 새로운 노드가 Head 
    if ( (*Head) == NULL ) 
    {   
    *Head = NewNode;
    } 
    else
    {	//  테일을 찾아 NewNode를 연결한다. 
        Node* Tail = (*Head);
        while ( Tail->NextNode != NULL )
        {
            Tail = Tail->NextNode;
        }
        Tail->NextNode = NewNode;
    }
}

Node* SLL_GetNodeAt(Node* Head, int Location)
{
    Node* Current = Head;

    while ( Current != NULL && (--Location) >= 0)
    {
        Current = Current->NextNode;
    }

    return Current;
}
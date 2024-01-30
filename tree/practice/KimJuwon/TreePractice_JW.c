#include <stdio.h>
#include <stdlib.h>

typedef struct tagSBTNode 
{
    struct tagSBTNode* Left;
    struct tagSBTNode* Right;

    int Data;
} SBTNode;

SBTNode* SBT_CreateNode( int NewData )
{
    SBTNode* NewNode = (SBTNode*)malloc( sizeof(SBTNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;

    return NewNode;
}

void SBT_DestroyNode( SBTNode* Node )
{
    free(Node);
}

void SBT_DestroyTree( SBTNode* Node )
{
    if ( Node == NULL )
        return;

    //  왼쪽 하위 트리 소멸 
    SBT_DestroyTree( Node->Left );

    //  오른쪽 하위 트리 소멸 
    SBT_DestroyTree( Node->Right );

    //  뿌리 노드 소멸 
    SBT_DestroyNode( Node );
}

//  트리 생성 함수
void MakeTree( SBTNode* Parent)
{
    int U, V;
    scanf("%d %d", &U, &V);
    //  U, V가 -1이 아니면 노드 생성 후 함수 재귀호출
    if (U != -1)
        {
            Parent->Left = SBT_CreateNode(U);
            MakeTree(Parent->Left);
        }

    if (V != -1)
        {
            Parent->Right = SBT_CreateNode(V);
            MakeTree(Parent->Right);
        }
}

//답 구하는 함수
void FindAnswer( SBTNode* Node , int K)
{
    //  결과 잎 출력
    if ( Node->Left == NULL && Node->Right == NULL )
        {
            printf("Answer : %d\n", Node->Data);
            return;
        }

    else if ( Node->Left == NULL )
        FindAnswer( Node->Right , K);
    
    else if ( Node->Right == NULL )
        FindAnswer( Node->Left , K);

    //  K가 홀수면 왼쪽 하위트리 선택, K를 K/2+1로 변경
    if ( K%2 == 1)
        FindAnswer( Node->Left , K/2+1);
    
    //  K가 짝수면 오른쪽 하위트리 선택 K를 K/2로 변경
    else
        FindAnswer( Node->Right , K/2);
}

int main(void)
{
    int N = 0, i, U, V, K;

    scanf("%d", &N);

    //  노드 생성 
    SBTNode* Root = SBT_CreateNode(1);

    //  트리 생성
    MakeTree(Root);

    //  답 출력
    scanf("%d", &K);
    FindAnswer(Root, K);

    //  트리 소멸
    SBT_DestroyTree(Root);

    return 0;    
}
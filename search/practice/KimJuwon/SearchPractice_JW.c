#include <stdio.h>
#include <stdlib.h>

typedef struct tagBSTNode 
{
    struct tagBSTNode* Left;
    struct tagBSTNode* Right;

    int count;

    int Data;
} BSTNode;

BSTNode* CreateNode( int NewData )
{
    BSTNode* NewNode = (BSTNode*)malloc( sizeof(BSTNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;

    //count 도입
    NewNode->count = 1;

    return NewNode;
}

void DestroyNode( BSTNode* Node )
{
    free(Node);
}

void DestroyTree( BSTNode* Tree )
{
    if ( Tree->Right != NULL )
        DestroyTree( Tree->Right );

    if ( Tree->Left != NULL )
        DestroyTree( Tree->Left );

    Tree->Left = NULL;
    Tree->Right = NULL;

    DestroyNode( Tree );
}

void InsertNode( BSTNode* Tree, BSTNode *Child)
{
    if ( Tree->Data < Child->Data ) 
    {
        if ( Tree->Right == NULL )
            Tree->Right = Child;
        else
            InsertNode( Tree->Right, Child );

    } 
    else if ( Tree->Data > Child->Data ) 
    {
        if ( Tree->Left == NULL )
            Tree->Left = Child;
        else
            InsertNode( Tree->Left, Child );
    }
}

BSTNode*  SearchNode( BSTNode* Tree, int Target )
{
    if ( Tree == NULL )
        return NULL;
   
    if ( Tree->Data == Target )
        {
            Tree->count += 1;
            return Tree;
        }
    else if ( Tree->Data > Target )
        return SearchNode ( Tree->Left, Target );
    else
        return SearchNode ( Tree->Right,  Target );
}

int num=0;

//결과 출력하는 함수, 중위순회 방식 차용
void PrintResult( BSTNode* Node , int k)//출력
{
    if ( Node == NULL )
        return;

    //  왼쪽 하위 트리에 대해 반복 
    PrintResult( Node->Left , k);

    //  num을 count만큼 증가시킨 뒤, k보다 num이 커지면 정답 출력 
    num += Node->count;
    if(num >= k)
        {
            printf( "Answer : %d ", Node->Data );
            return;
        }

    //  오른쪽 하위 트리에 대해 반복 
    PrintResult( Node->Right , k);
}


int main(void)
{
    //  노드 생성 
    BSTNode* Tree = CreateNode(1);
    BSTNode* Node = NULL;

    //  트리에 노드 추가
    int i, j, N, k;
    printf("N을 입력하세요: ");
    scanf("%d", &N);
    for(i=1 ; i<=N ; i++){
            for(j=1 ; j<=N ; j++){
                if(i*j==1)
                    continue;

                //이미 있으면 count+1
                SearchNode(Tree,i*j);

                //없으면 노드 추가
                InsertNode(Tree, CreateNode(i*j));
            }
        }

    printf("k를 입력하세요: ");
    scanf("%d", &k);

    PrintResult( Tree , k);
    printf( "\n");

    //  트리 소멸
    DestroyTree( Tree );

    return 0;
}
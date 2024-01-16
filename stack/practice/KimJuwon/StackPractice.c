#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
    int Data;
    struct tagNode* NextNode;
} Node;

typedef struct tagLinkedListStack
{
    Node* List;
    Node* Top;
} LinkedListStack;

void  LLS_CreateStack( LinkedListStack** Stack )
{
    //  스택을 자유 저장소에 생성 
    (*Stack )       = ( LinkedListStack*)malloc(sizeof( LinkedListStack ) );
    (*Stack )->List = NULL;
    (*Stack )->Top  = NULL;
}

Node* LLS_CreateNode( int NewData )
{
    Node* NewNode = ( Node*)malloc(sizeof( Node ) );

    NewNode->Data = NewData;  //  데이터를 저장한다. 
    NewNode->NextNode = NULL; //  다음 노드에 대한 포인터는 NULL로 초기화한다. 

    return NewNode;//  노드의 주소를 반환한다. 
}

void  LLS_DestroyNode( Node* _Node )
{
    free(_Node );
}

void LLS_Push( LinkedListStack* Stack, Node* NewNode )
{
    if ( Stack->List == NULL ) 
    {        
        Stack->List = NewNode;
    } 
    else
    {
        //  스택의 Top에 신규 노드를 연결한다.
        Stack->Top->NextNode = NewNode;
    }
    
    //  스택의 Top 필드에 새 노드의 주소를 등록한다. 
    Stack->Top = NewNode;
}

Node* LLS_Pop( LinkedListStack* Stack )
{
    //  LLS_Pop() 함수가 반환할 최상위 노드 저장 
    Node* TopNode = Stack->Top;

    if ( Stack->List == Stack->Top )
    {
        Stack->List = NULL;
        Stack->Top  = NULL;
    }
    else
    {
        // Top 아래에 있던 노드를 새로운 CurrentTop에 저장 
        Node* CurrentTop = Stack->List;
        while ( CurrentTop != NULL && CurrentTop->NextNode != Stack->Top )
        {
            CurrentTop = CurrentTop->NextNode;
        }

        // CurrentTop을 Top에 저장
        Stack->Top = CurrentTop;
        Stack->Top->NextNode = NULL;
    }

    return TopNode;
}

Node* LLS_Top( LinkedListStack* Stack )
{
    return Stack->Top;
}

int LLS_GetSize( LinkedListStack* Stack )
{
    int    Count = 0;
    Node*  Current = Stack->List;

    while ( Current != NULL )
    {
        Current = Current->NextNode;
        Count++;
    }

    return Count;
}

int LLS_IsEmpty( LinkedListStack* Stack )
{
    return (Stack->List == NULL);
}

void LLS_DestroyStack( LinkedListStack* Stack )
{
    while ( !LLS_IsEmpty(Stack ) )
    {
        Node* Popped = LLS_Pop( Stack );
        LLS_DestroyNode(Popped);    
    }

    //  스택을 자유 저장소에서 해제 
    free(Stack);
}

int main(void)
{
    int i= 0, N, num;
    int Count = 0;
    Node* Popped;

    //현재 줄 서있는 곳 스택 생성
    LinkedListStack* Stack;
    LLS_CreateStack(&Stack);

    //역순 스택 생성
    LinkedListStack* ReverseStack;
    LLS_CreateStack(&ReverseStack);

    //빠진 사람이 들어갈 스택 생성
    LinkedListStack* WaitLine;
    LLS_CreateStack(&WaitLine);
    
    //번호를 입력받아 역순 스택에 저장
    printf("학생 수를 입력하세요: ");
    scanf("%d", &N);
    printf("학생들의 번호표를 입력하세요: ");
    for( i ; i<N ; i++)
    {
        scanf("%d", &num);
        LLS_Push( ReverseStack, LLS_CreateNode(num));
    }

    //스택 저장
    for( i=0 ; i<N ; i++)
    {
        Popped = LLS_Pop(ReverseStack);
        LLS_Push( Stack, LLS_CreateNode((Popped->Data)));
        LLS_DestroyNode(Popped);
    }
    LLS_DestroyStack(ReverseStack);

    //min과 같으면 pop, min보다 크면 WaitLine에 줄세움
    int min = 1;
    for( i=0 ; i<N ; i++)
    {
        Popped = LLS_Pop(Stack);
        if((Popped->Data) > min)
            LLS_Push( WaitLine, LLS_CreateNode((Popped->Data)));
        
        else
            min++;

        LLS_DestroyNode(Popped);
    }
    LLS_DestroyStack(Stack);

    //처음부터 순서대로 서있으면 성공(=WaitLine이 비어있음)
    if(min>N)
        {
            printf("Nice\n");
            return 0;
        }

    //min과 waitLine의 Top 비교, 다르면 실패
    Count = LLS_GetSize(WaitLine);

    for ( i=0; i<Count; i++ )
    {
        if ( LLS_IsEmpty(WaitLine) )
            break;

        if((LLS_Top(WaitLine)->Data) != min)
            {
                printf("Bad\n");
                break;
            }

        Popped = LLS_Pop( WaitLine );

        LLS_DestroyNode(Popped);

        //WaitLine이 비면 성공
        if ( LLS_IsEmpty(WaitLine) )
                printf( "Nice\n");
        min++;
    }
    
    LLS_DestroyStack(WaitLine);

    return 0;
}
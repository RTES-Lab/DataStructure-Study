#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
    int Data;
    struct tagNode* NextNode;
} Node;

typedef struct tagLinkedQueue
{
    Node* Front;
    Node* Rear;
    int   Count;
} LinkedQueue;

void  LQ_CreateQueue( LinkedQueue** Queue )
{
    //  큐를 자유 저장소에 생성 
    (*Queue )        = ( LinkedQueue*)malloc(sizeof( LinkedQueue ) );
    (*Queue )->Front = NULL;
    (*Queue )->Rear  = NULL;
    (*Queue )->Count = 0;
}

Node* LQ_CreateNode( int NewData )
{
    Node* NewNode = (Node*)malloc( sizeof( Node ) );
    NewNode->Data = NewData;  //  데이터를 저장한다. 
    NewNode->NextNode = NULL; //  다음 노드에 대한 포인터는 NULL로 초기화한다. 

    return NewNode;//  노드의 주소를 반환한다. 
}

void  LQ_DestroyNode(Node* _Node )
{
    free(_Node );
}

void LQ_Enqueue( LinkedQueue* Queue, Node* NewNode )
{
    if ( Queue->Front == NULL ) 
    {        
        Queue->Front = NewNode;
        Queue->Rear  = NewNode;
        Queue->Count++;
    } 
    else
    {
        Queue->Rear->NextNode = NewNode;
        Queue->Rear = NewNode;
        Queue->Count++;
    }
}

Node* LQ_Dequeue( LinkedQueue* Queue )
{
    //  LQ_Dequeue() 함수가 반환할 최상위 노드 
    Node* Front = Queue->Front;

    if ( Queue->Front->NextNode == NULL )
    {
        Queue->Front = NULL;
        Queue->Rear  = NULL;
    }
    else
    {
        Queue->Front = Queue->Front->NextNode;
    }

    Queue->Count--;

    return Front;
}

int LQ_IsEmpty( LinkedQueue* Queue )
{
    return ( Queue->Front == NULL);
}

void LQ_DestroyQueue( LinkedQueue* Queue )
{
    while ( !LQ_IsEmpty( Queue ) )
    {
        Node* Popped = LQ_Dequeue( Queue );
        LQ_DestroyNode(Popped);    
    }
    //  큐를 자유 저장소에서 할당 해제 
    free( Queue );
}

int main(void)
{
    Node* Popped;
    LinkedQueue* Queue;

    LQ_CreateQueue(&Queue);

    int N;
    printf("N을 입력하세요: ");
    scanf("%d", &N);

    //1부터 N까지 노드 생성 후 큐에 추가
    for(int i=1 ; i<=N ; i++)
    {
        LQ_Enqueue( Queue, LQ_CreateNode(i) );
    }    

    //맨 위 카드 버리고 다음 카드 맨 밑으로 옮기는 과정 1장 남을 때까지 반복
    while(1)
    {   
        //맨 위 카드 버림
        Popped = LQ_Dequeue(Queue);
        LQ_DestroyNode(Popped);

        //1장 남으면 종료
        if(Queue->Front->NextNode == NULL)
            break;
    
        //위 카드 맨 밑으로 옮김
        Popped = LQ_Dequeue(Queue);
        //LQ_Enqueue( Queue, Popped); -이건x
        LQ_Enqueue( Queue, LQ_CreateNode(Popped->Data));
        LQ_DestroyNode(Popped);
    }

    //마지막 남은 카드 출력
    Popped = LQ_Dequeue(Queue);
    printf("%d\n", Popped->Data);

    LQ_DestroyNode(Popped);

    LQ_DestroyQueue(Queue);

    return 0;
}
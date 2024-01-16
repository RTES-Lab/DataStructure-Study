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
	int Count;
} LinkedQueue;

void LQ_CreateQueue(LinkedQueue ** Queue)
{
	(*Queue) = (LinkedQueue *) malloc(sizeof(LinkedQueue));
	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->Count = 0;
}

Node* LQ_CreateNode(int NewData)
{
	Node * NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = NewData;
	NewNode->NextNode = NULL; // 다음 노드에 대한 포인터는 NULL로 초기화한다.
	
    return NewNode; // 노드의 주소를 반환한다.
}

void LQ_Enqueue(LinkedQueue * Queue, Node * NewNode)
{
	if(Queue->Front == NULL)
	{
		Queue->Front = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
    }
	else{
		Queue->Rear->NextNode = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
    }
}

Node * LQ_Dequeue(LinkedQueue * Queue){
	Node * Front = Queue->Front;
	
    if(Queue->Front->NextNode == NULL){
		Queue->Front = NULL;
		Queue->Rear = NULL;
	}
	else{
		Queue->Front = Queue->Front->NextNode;
	}
	Queue->Count--;
	return Front;
}

void LQ_DestroyNode(Node * _Node){
	free(_Node);
}

int LQ_IsEmpty(LinkedQueue * Queue){
	return (Queue->Front == NULL);
}

void LQ_DestroyQueue(LinkedQueue * Queue){
	while(!LQ_IsEmpty(Queue))
	{
		Node* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
	}
	free(Queue);
}

int main(void) {
    int N;
	printf("Input Number of Cards: ");
    scanf("%d", &N);

    LinkedQueue* Queue;
    LQ_CreateQueue(&Queue);

    for (int i = 1; i <= N; ++i) {	// 카드 번호를 큐에 추가
        LQ_Enqueue(Queue, LQ_CreateNode(i));
    }

    while (Queue->Count > 1) {	// 카드를 하나 남을 때까지 반복
        Node* discarded = LQ_Dequeue(Queue);	// 제일 위에 있는 카드를 버림
        LQ_DestroyNode(discarded);
        
		if (Queue->Count > 1){
			Node* moved = LQ_Dequeue(Queue);	// 다음으로 제일 위에 있는 카드를 제일 아래에 옮김
			LQ_Enqueue(Queue, moved);
		}
	}

    // Node* lastCard = LQ_Dequeue(Queue);	// 마지막에 남은 카드 출력
	printf("마지막 카드의 숫자는 %d입니다.\n", Queue->Front->Data);
	Node* lastCard = LQ_Dequeue(Queue);

    // LQ_DestroyNode(lastCard);
    // LQ_DestroyQueue(Queue);

    return 0;
}

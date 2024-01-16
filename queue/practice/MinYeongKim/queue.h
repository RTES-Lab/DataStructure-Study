#include <stdlib.h>
#include <string.h>

typedef struct tagNode
{
	char * Data;
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
	// 큐를 자유 저장소에 저장
	(*Queue) = (LinkedQueue *) malloc(sizeof(LinkedQueue));
	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->Count = 0;
}

Node * LQ_CreateNode(char * NewData)
{
	Node * NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = (char*)malloc(strlen(NewData) + 1);

	strcpy(NewNode->Data, NewData); //데이터를 저장한다.

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

	else
	{
		Queue->Rear->NextNode = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
	}
}

Node * LQ_Dequeue(LinkedQueue * Queue)
{
	// LQ_Dequeue()함수가 반환할 최상위 노드
	Node * Front = Queue->Front;
	
	// 노드가 하나밖에 존재하지 않는 경우, 제거 되었을 때 전단과 후단을 가리키는 포인터는 NULL값이 된다.
	if(Queue->Front->NextNode == NULL)
	{
		Queue->Front = NULL;
		Queue->Rear = NULL;
	}
	
	else
	{
		Queue->Front = Queue->Front->NextNode;
	}
	
	Queue->Count--;

	return Front;
}

void LQ_DestroyNode(Node * _Node)
{
	free(_Node->Data);
    free(_Node);
}

int LQ_IsEmpty(LinkedQueue * Queue)
{
	return (Queue->Front == NULL);
}

void LQ_DestroyQueue(LinkedQueue * Queue)
{
	while(!LQ_IsEmpty(Queue))
	{
		Node* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
	}

	// 큐를 자유 저장소에서 할당 해제
	free(Queue);
}
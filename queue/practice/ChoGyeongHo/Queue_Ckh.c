#include <stdio.h>
#include <stdlib.h>

#define size 5000000

typedef int ElementType;
typedef struct tagNode{
    ElementType Data;
    struct tagNode* next;
} Node;

typedef struct tagQueue{
    int capacity;
    int front;
    int rear;
    
    Node* Nodes; 
} CircularQueue;

void CreatCQ(CircularQueue** Queue, int capacity){
    *Queue = (CircularQueue*)malloc(sizeof(CircularQueue));

    (*Queue)-> Nodes = (Node*)malloc(sizeof(Node)*(capacity+1));
    (*Queue)-> capacity = capacity;
    (*Queue)-> front = 0;
    (*Queue)-> rear = 0;    
}

void Enqueue(CircularQueue* Queue, ElementType Data){
    int position = 0;

    if(Queue->rear == Queue->capacity+1){
        position = Queue->rear;
        Queue->rear = 0;
    }
    else
        position = Queue->rear++;
    
    Queue->Nodes[position].Data=Data;
}

int Dequeue(CircularQueue* Queue){
    int position = Queue->front;

    if(Queue->front == Queue->capacity)
        Queue->front = 0;
    else    
        Queue->front++;

    return Queue->Nodes[position].Data;
}


int IsEnd(CircularQueue* Queue){
    return (Queue->front +1 == Queue->rear);
}

int main(){
    int N;
    int i;
    int count;
    CircularQueue* card;

    printf("카드의 장 수를 입력하세요: ");
    scanf("%d", &N);

    if(N<=0){
        printf("[Error] 양수를 입력하세요\n");
        exit(1);
    }
    if(N>5000000){
        printf("[Error] 너무 큰 수를 입력하였습니다");
        exit(1);
    }

    CreatCQ(&card, size);


    for(i=0; i<N; i++){
        Enqueue(card, i+1);
    }

    while(!IsEnd(card)){
        Dequeue(card);
        Enqueue(card, Dequeue(card));
    }
    
    printf("마지막 카드는 %d 입니다.\n", Dequeue(card));

    return 0;    
}
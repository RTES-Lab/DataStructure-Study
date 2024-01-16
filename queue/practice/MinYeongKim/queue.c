#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(){
    int N;
    scanf("%d", &N);

    LinkedQueue* queue;
    Node* newnode;

    LQ_CreateQueue(&queue);
    for(int i = N; i >= 1 ; i--){
        char str[10];
        sprintf(str, "%d", i);
        newnode = LQ_CreateNode(str);
        LQ_Enqueue(queue, newnode);
    }

    //노드 제거 시작
    while(1){
        newnode = LQ_Dequeue(queue);
        if(LQ_IsEmpty(queue)){
            printf("%s", newnode->Data);
            break;
        }
        LQ_DestroyNode(newnode);
        newnode = LQ_Dequeue(queue);
        LQ_Enqueue(queue, newnode);
    }
    LQ_DestroyNode(newnode);
    LQ_DestroyQueue(queue);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode{
    int Right;  // 오른쪽 자식 노드의 번호
    int Left;   // 왼쪽 자식 노드의 번호
}Node;

int main(){
    int N;  // 노드 개수
    int i;
    int rest;   // 나머지
    
    scanf(" %d", &N);
    Node *arr=(Node*)malloc(sizeof(Node)*N);

    for(i=0; i<N; i++)
        scanf(" %d %d", &(arr[i].Left), &(arr[i].Right));

    long long marble;
    scanf(" %lld", &marble);

    i=0;

    while(arr[i].Right!=(-1) || arr[i].Left!=(-1)){
    
        if(arr[i].Right!=(-1) && arr[i].Left!=(-1)){    // 길이 2개

            if(marble%2==1){
                i=arr[i].Left-1;
                marble=marble/2+1;
            }

            else{
                i=arr[i].Right-1;
                marble/=2;
            }
        }

        else if(arr[i].Right!=(-1))                   // 길이 1개 오른쪽
            i=arr[i].Right-1;

        else                                        // 길이 1개 왼쪽
            i=arr[i].Left-1;
    }
    printf("%d", i+1);
    return 0;
}

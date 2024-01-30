#include <stdio.h>
#define Maxsize 200001

typedef struct tree{
    unsigned int left;
    unsigned int right;
}Tree;

int main(void){
    unsigned int n; //노드의 개수
    unsigned long k;
    Tree arr[Maxsize];

    scanf(" %u",&n);
    for(int i = 1;i <= n;i++){
        scanf(" %u %u",&arr[i].left,&arr[i].right); //편의상 인덱스가 1인 원소를 1번 노드라 하자.
    }
    scanf(" %lu",&k);
    unsigned int now = 1; 
    while(1){
        // 자식 노드가 없는 경우
        if(arr[now].left == -1 && arr[now].right == -1)
            break;
        // 자식 노드가 1개인 경우
        else if(arr[now].left == -1)
            now = arr[now].right;
        else if(arr[now].right == -1)
            now = arr[now].left;
        // 자식 노드가 2개인 경우
        else if(k % 2){     //k가 홀수 번째 공이면 왼쪽으로 이동
            now = arr[now].left;
            k = k / 2 + 1;
        }
        else{   //k가 짝수 번째 공이면 오른쪽으로 이동
            now = arr[now].right;
            k = k / 2;
        }                
    }
    printf("%u\n",now);
    return 0;
}

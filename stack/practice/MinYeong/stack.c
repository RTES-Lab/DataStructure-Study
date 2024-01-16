/*
스택 두개 생성. 스택 1에 원래 순서 다 넣기. 그리고 순서1번 위에 순서들 스택 2로 옮기기

작성자: 김민영
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

int main(){
    
    int N;
    printf("순열의 크기를 입력하세요: ");
    scanf("%d", &N);

    // 1부터 n까지의 정수 배열 생성
    int* str1 = (int*)malloc( N * sizeof(int));


    for (int i = 0; i < N; i++) {
        str1[i] = i + 1;
    }

    // 피셔-예이츠 셔플을 이용하여 배열 섞기
    // srand를 호출하여 난수 생성기를 초기화
    srand((unsigned int)time(NULL));

    // 배열의 끝부터 시작하여 무작위로 섞음
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // 배열의 i번째 요소와 j번째 요소를 교환
        int temp = str1[i];
        str1[i] = str1[j];
        str1[j] = temp;
    }


    // 스택만들기

    LinkedListStack* List1 = NULL;
    LinkedListStack* List2 = NULL;
    
    Node* newnode = NULL;
    LLS_CreateStack(&List1);
    for(int i = 0; i<N ; i++){
        char * tmp;
        sprintf(tmp, "%d", str1[i]);
        newnode = LLS_CreateNode(tmp);
        LLS_Push(List1, newnode );            
    }

    while( ( newnode =LLS_Pop(List1))->Data != '1' ){
        LLS_Push(List2, newnode);
    }


    free(str1); // 동적 할당된 메모리 해제

    return 0;
}
#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
} Node;

typedef struct tagArrayStack
{
    int   Capacity;
    int   Top;
    Node* Nodes;
} ArrayStack;

// 함수 원형 선언
/*
 처음 스택을 자유저장소에 공간을 미리 만드는 함수
 1) 스택 자체의 정보(용량, Top 실시간 위치, 노드 배열)를 담는 공간
 2) 노드 배열의 내용을 저장하는 공간 

*/
void        AS_CreateStack(ArrayStack** Stack, int Capacity);

/*
 노드 -> 스택 순
*/
void        AS_DestroyStack(ArrayStack* Stack);

/*
 스택의 삽입 연산 함수
*/
void        AS_Push(ArrayStack* Stack, ElementType Data);

/*
 스택의 제거 연산 함수 
 pop특성 상 제거할 때 값이 퐁 튀어나옴(데이터를 반환하는 이유)
*/
ElementType AS_Pop(ArrayStack* Stack);


/*
 최상위 노드 위치의 데이터를 반환하는 함수
*/
ElementType AS_Top(ArrayStack* Stack);

/*
 Stack이 지금까지 얼마나 쌓였는지 값을 반환하는 함수
*/
int         AS_GetSize(ArrayStack* Stack);

/*
 스택이 비어있는지 확인하는 함수
 스택에 아무것도 없으면 -1로 두는 것은  As_crearte함수에서 설명함
*/
int         AS_IsEmpty(ArrayStack* Stack);

#endif

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

void  AS_CreateStack(ArrayStack** Stack, int Capacity)
{
    //  스택을 자유 저장소에 생성 
    (*Stack)           = (ArrayStack*)malloc(sizeof(ArrayStack));

    //  입력된 Capacity만큼의 노드를 자유 저장소에 생성 
    (*Stack)->Nodes    = (Node*)malloc(sizeof(Node)*Capacity);

    //  Capacity 및 Top 초기화 
    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = -1;
}

void AS_DestroyStack(ArrayStack* Stack)
{
    //  노드를 자유 저장소에서 해제 
    free(Stack->Nodes);

    //  스택을 자유 저장소에서 해제 
    free(Stack);
}

void AS_Push(ArrayStack* Stack, ElementType Data)
{
    Stack->Top++;
    Stack->Nodes[Stack->Top].Data = Data;
}

ElementType AS_Pop(ArrayStack* Stack)
{
    int Position = Stack->Top--;
    return Stack->Nodes[Position].Data;
}

ElementType AS_Top(ArrayStack* Stack)
{
    return Stack->Nodes[Stack->Top].Data;
}

int AS_IsEmpty(ArrayStack* Stack)
{
    return (Stack->Top == -1);
}


int main( void )
{
    int i;
    int current_ticket=1;
    int student_num;
    int temp;

    ArrayStack* stack = NULL;
    ArrayStack* wait_stack = NULL;

    printf("input students number: ");
    scanf("%d", &student_num);

    if(student_num<1 || student_num>1000){
        printf("1부터 1000사이의 정수를 입력하시오\n");
        return 1;
    }
    // 학생 수에 관한 에러 처리 필요

    AS_CreateStack(&stack, student_num);         // 학생 수에 따른 스택 생성
    AS_CreateStack(&wait_stack, student_num);    // 대기 공간 스택 생성

    int *array = (int*)malloc(student_num * sizeof(int));

    if(array == NULL){
        printf("메모리 할당 실패\n");
        return 1;
    }

    for(i=0; i<student_num; i++){
        scanf("%d", &array[i]);  
    }

    for(i=0; i<student_num; i++){
        AS_Push(stack, array[student_num - 1 - i]);
    }

    free(array);

    // 대기열이 비워질 때까지 반복
    while(!AS_IsEmpty(stack)){
        temp = AS_Top(stack);      // 맨 앞 사람 확인

        if(temp == current_ticket){ // 순서에 맞는 사람이면 출력되고 나간다.
            AS_Pop(stack);
            current_ticket++;       // 다음 사람 찾기
        }
        else{
            if(AS_IsEmpty(wait_stack)){
                AS_Push(wait_stack, temp);
                AS_Pop(stack);
            }
            else{
                if(AS_Top(wait_stack)==current_ticket){
                    AS_Pop(wait_stack);
                    current_ticket++;
                }
                else{
                    AS_Push(wait_stack, temp);
                    AS_Pop(stack);
                }
            }
        }
    }


    // 대기 공간이 비워질 때까지 반복
    while(!AS_IsEmpty(wait_stack)){
        temp = AS_Pop(wait_stack);

        if(temp== current_ticket){
            current_ticket++;
        }
        else{
            break;
        }
    }

    if(AS_IsEmpty(wait_stack)){
        printf("NICE!\n");
    }
    else{
        printf("SAD...\n");
    }

    AS_DestroyStack(stack);
    AS_DestroyStack(wait_stack);

    return 0;
}

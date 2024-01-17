#include "ArrayStack.h"
#define Max_Student_NUM 1000
#define Min_Student_Num 1

 
void  AS_CreateStack(ArrayStack** Stack, int Capacity)
{
    //  스택을 자유 저장소에 생성
    (*Stack)           = (ArrayStack*)malloc(sizeof(ArrayStack));

    //  입력된 Capacity만큼의 노드를 자유 저장소에 생성 
    (*Stack)->Nodes    = (Node*)malloc(sizeof(Node)*Capacity);

    //  Capacity 및 Top 초기화 
    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = -1; // 처음에 노드 배열에는 아무런 정보가 없음, 그래서 -1로 표시 노드가 1개 있다면 그것은 인덱스 상 0
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
    // 스택이 쌓이면 최상위 노드 위치는 당연히 바뀜
    Stack->Top++;

    // Stack->Nodes[(Stack->Top)].Data = Data;
    Stack->Nodes[Stack->Top].Data = Data;
}

ElementType AS_Pop(ArrayStack* Stack)
{
    // 스택이 걷어지면 당연히 최상위 노드 위치는 바뀜(근데 아직 메모리 해제는 안함)
    int Position = Stack->Top--;

    // Position은 임시 저장 변수. 이전의 최상위 노드의 값 반환
    return Stack->Nodes[Position].Data;
}

ElementType AS_Top(ArrayStack* Stack)
{
    return Stack->Nodes[Stack->Top].Data;
}

int AS_GetSize(ArrayStack* Stack)
{   
    // 인덱스는 0부터 시작해서
    return Stack->Top+1;
}

int AS_IsEmpty(ArrayStack* Stack)
{
    return (Stack->Top == -1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagNode{
    char* Data;
    struct tagNode* NextNode;
} Node;

typedef struct tagLinkedListStack{  //링크드 리스트 기반 스택
    Node* List;
    Node* Top;
} LinkedListStack;

void LLS_CreateStack(LinkedListStack** Stack){  //스택 생성
    (*Stack) = (LinkedListStack*)malloc(sizeof(Stack));
    (*Stack)->List = NULL;
    (*Stack)->Top = NULL;
}

Node* LLS_CreateNode(char* NewData ){   //노드 생성
    Node* NewNode = (Node*)malloc(sizeof( Node ) );
    NewNode->Data = (char*)malloc(strlen( NewData ) + 1);
    strcpy(NewNode->Data, NewData ); 
    NewNode->NextNode = NULL; 
    return NewNode;
}

void LLS_Push( LinkedListStack* Stack, Node* NewNode )
{
    if ( Stack->List == NULL ){ 
        Stack->List = NewNode;
    } 
    else{
    Stack->Top->NextNode = NewNode; // 스택의 Top에 신규 노드를 연결한다.
    }
    Stack->Top = NewNode;   // 스택의 Top 필드에 새 노드의 주소를 등록한다. 
}

Node* LLS_Pop( LinkedListStack* Stack ) {
    Node* TopNode = Stack->Top; // LLS_Pop() 함수가 반환할 현재의 최상위 노드 저장 
    if ( Stack->List == Stack->Top ){
        Stack->List = NULL;
        Stack->Top = NULL;
    }
    else{
        Node* CurrentTop = Stack->List; // Top 아래에 있던 노드(CurrentTop) 찾기
        while (CurrentTop != NULL && CurrentTop->NextNode != Stack->Top ){
            CurrentTop = CurrentTop->NextNode;
            }
    Stack->Top = CurrentTop;// CurrentTop을 Top에 저장
    Stack->Top->NextNode = NULL;
    }
    return TopNode;
}

int main(void) {
    LinkedListStack* Stack;
    LLS_CreateStack(&Stack);

    int n;
    scanf("%d", &n);

    int expected = 1;
    for (int i = 0; i < n; ++i) {
        int num;
        scanf("%d", &num);
        
        while (Stack->Top != NULL && Stack->Top->Data[0] == expected + '0') {   // 스택이 비어있지 않고, 스택의 Top이 예상값과 같으면 Pop
            Node* popped = LLS_Pop(Stack); 
            free(popped->Data);
            free(popped);
            ++expected;
        }

        char buffer[1000];    // 현재 수를 스택에 Push
        snprintf(buffer, sizeof(buffer), "%d", num);    //sprintf + size_t -> snprintf)
        Node* newNode = LLS_CreateNode(buffer);
        LLS_Push(Stack, newNode);
    }

    while (Stack->Top != NULL && Stack->Top->Data[0] == expected + '0') {   // 스택에 남아있는 숫자들이 예상값과 일치하는지 확인
        Node* popped = LLS_Pop(Stack);
        free(popped->Data);
        free(popped);
        ++expected;
    }

    if (expected - 1 == n){ // 예상값이 모두 일치하면 "Nice" 출력, 아니면 "Sad" 출력
        printf("Nice\n");
    } 
    else{
        printf("Sad\n");
    }

    free(Stack);
    return 0;
}

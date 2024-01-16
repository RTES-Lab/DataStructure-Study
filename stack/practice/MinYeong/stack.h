#include <stdlib.h>
#include<string.h>

typedef struct tagNode
{
char* Data;
struct tagNode* NextNode;
} Node;


typedef struct tagLinkedListStack
{
Node* List;
Node* Top;
} LinkedListStack;

void LLS_CreateStack( LinkedListStack** Stack )
{
    // 스택을 자유 저장소에 생성 
    (*Stack ) = ( LinkedListStack*)malloc(sizeof( LinkedListStack ) );
    (*Stack )->List = NULL;
    (*Stack )->Top = NULL;
}

Node* LLS_CreateNode( char* NewData )
{
    // Node 구조체 메모리 할당
    Node* NewNode = ( Node*)malloc(sizeof( Node ) );
    // Node 구조체의 문자열 데이터 메모리 할당 
    NewNode->Data = ( char*)malloc(strlen( NewData ) + 1);

    strcpy(NewNode->Data, NewData ); // 데이터를 저장한다. 

    NewNode->NextNode = NULL; // 다음 노드에 대한 포인터는 NULL로 초기화한다. 

    return NewNode;// 노드의 주소를 반환한다. 
}

void LLS_Push( LinkedListStack* Stack, Node* NewNode )
{
    if ( Stack->List == NULL ) { 
        Stack->List = NewNode;
        } 
    else{
    // 스택의 Top에 신규 노드를 연결한다.
    Stack->Top->NextNode = NewNode;
    }
    // 스택의 Top 필드에 새 노드의 주소를 등록한다. 
    Stack->Top = NewNode;
}

Node* LLS_Pop( LinkedListStack* Stack ) {
	// LLS_Pop() 함수가 반환할 현재의 최상위 노드 저장 
    Node* TopNode = Stack->Top;
    // 노드가 0개 혹은 1개 일때 
    if ( Stack->List == Stack->Top ){
        Stack->List = NULL;
        Stack->Top = NULL;
        }
        else{
        // Top 아래에 있던 노드(CurrentTop) 찾기
        Node* CurrentTop = Stack->List;
        while (CurrentTop != NULL && CurrentTop->NextNode != Stack->Top ){
            CurrentTop = CurrentTop->NextNode;
            }

        // CurrentTop을 Top에 저장
        Stack->Top = CurrentTop;
        Stack->Top->NextNode = NULL;
    }

	return TopNode;
}
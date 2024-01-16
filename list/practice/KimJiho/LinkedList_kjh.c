#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void splitCommand(char *input, int *number, char *string1, char *string2) {
    char *token = strtok(input, "/");

    if (token != NULL) {
        *number = atoi(token); //앞의 숫자를 정수로 저장

        token = strtok(NULL, "/"); //다음 토큰

        if (token != NULL) { // 첫 번째 문자열
            strncpy(string1, token, 30);
            string1[29] = '\0'; // 문자열 끝에 NULL 문자 추가

            token = strtok(NULL, "/"); //다음 토큰

            if (token != NULL) {// 두 번째 문자열
                strncpy(string2, token, 30);
                string2[29] = '\0';
            } 
            else {
                string2[0] = '\0'; // 빈 문자열
            }
        } 
        else {
            // '/'가 없는 경우
            string1[0] = '\0'; // 빈 문자열로 설정
            string2[0] = '\0'; // 빈 문자열로 설정
        }
    } 
    else {
        if (*number = -1){
            exit(1);
        }
    }
}
//링크드 리스트 정의
typedef char ElementType;

typedef struct tagItem{
    ElementType Data[30];
    struct tagItem* NextItem;
} Item;

typedef struct tagNode{
    ElementType Data[30];
    struct tagNode* NextCategory;
    struct tagItem* items;
} Node;

Node* SLL_CreateCategory(char *NewData) // char 배열을 받도록 수정
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    strncpy(NewNode->Data, NewData, sizeof(NewNode->Data) - 1);  // strncpy를 사용하여 복사
    NewNode->Data[sizeof(NewNode->Data) - 1] = '\0';  // 문자열의 끝에 NULL 문자 추가
    NewNode->NextCategory = NULL;
    NewNode->items = NULL;

    return NewNode;
}

Item* SLL_CreateItem(char *NewData) // char 배열을 받도록 수정
{
    Item* NewItem = (Item*)malloc(sizeof(Item));
    strncpy(NewItem->Data, NewData, sizeof(NewItem->Data) - 1);  // strncpy를 사용하여 복사
    NewItem->Data[sizeof(NewItem->Data) - 1] = '\0';  // 문자열의 끝에 NULL 문자 추가
    NewItem->NextItem = NULL;

    return NewItem;
}

void SLL_AppendNode(Node** Head, Node* NewNode) //링크드 리스트 노드 추가
{   //  헤드 노드가 NULL이라면 새로운 노드가 Head
    if ((*Head) == NULL ){ 
        *Head = NewNode;
    } 
    else{   //  테일을 찾아 NewNode를 연결한다. 
        Node* Tail = (*Head);
        while (Tail->NextCategory != NULL)
        {
            Tail = Tail->NextCategory;
        }
        Tail->NextCategory = NewNode;
     }
}

int SLL_GetNodeCount(Node* Head)
{
    int Count = 0;
    Node* Current = Head;
    while (Current != NULL){
        Current = Current->NextCategory;
        Count++;
    }
    return Count;
}

int SLL_GetItemCount(Item* Head)
{
    int Count = 0;
    Item* CurrentItem = Head;
    while (CurrentItem != NULL){
        CurrentItem = CurrentItem->NextItem;
        Count++;
    }
    return Count;
}

Node* SLL_GetNodeAt(Node* Head, int Location)
{
    Node* Current = Head;
    while ( Current != NULL && (--Location) >= 0){
        Current = Current->NextCategory;
    }
    return Current;
}

Item* SLL_GetItemAt(Item* HeadItem, int Location)
{
    Item* CurrentItem = HeadItem;
    while ( CurrentItem != NULL && (--Location) >= 0){    
        CurrentItem = CurrentItem->NextItem;
    }
    return CurrentItem;
}

void SLL_InsertAfter(Node* Current, Node* NewNode){
    NewNode->NextCategory = Current->NextCategory;
    Current->NextCategory = NewNode;
}

void SLL_InsertNewHead(Node** Head, Node* NewHead){
    if ( (*Head) == NULL ){
        (*Head) = NewHead;
    }
    else{
        NewHead->NextCategory = (*Head);
        (*Head) = NewHead;
    }
}

void SLL_InsertBefore(Node** Head, Node* Current, Node* NewNode) {
    if (*Head == Current) {
        // 만약 Current가 헤드라면, NewNode를 Current 앞에 삽입합니다.
        NewNode->NextCategory = *Head;
        *Head = NewNode;
    } 
    
    else {
        // 만약 Current가 헤드가 아니라면, Current 앞에 삽입할 노드를 찾아 NewNode를 삽입합니다.
        Node* temp = *Head;
        while (temp != NULL && temp->NextCategory != Current) {
            temp = temp->NextCategory;
        }

        if (temp != NULL) {
            NewNode->NextCategory = temp->NextCategory;
            temp->NextCategory = NewNode;
        }
    }
}

void SLL_NodeComparison(Node** Head, Node* NewNode){
    Node* Current = *Head;
    int temp = 0, Location= 0;

    int NodeCount = SLL_GetNodeCount(*Head);

    while (1){
        temp = strcmp(NewNode->Data, Current->Data); 
        
        if (temp == 0){
            printf("이미 카테고리가 존재합니다. \n");
            free(NewNode);
            return;
        }
        
        else if((Current->NextCategory == NULL)&&(temp > 0)){
            SLL_AppendNode(Head, NewNode);
            return;
        }

        else if ((Current->NextCategory != NULL)&&(temp > 0)){ 
            Current = Current->NextCategory;
            Location++;
        }

        else{
            printf("%s", Current->Data); 
            SLL_InsertBefore(Head, Current, NewNode);
            return;
        }
    }
}

Node* SLL_FindingNode(Node** category, char* input_category){
    
    Node* Current = *category;
    while((Current != NULL)&&(strcmp(Current->Data, input_category) != 0)){
        Current = Current->NextCategory;
    }
    if (Current == NULL){
        Node* NewNode = SLL_CreateCategory(input_category);
    
        if (*category == NULL){
            SLL_AppendNode(category, NewNode);
            }
        else {
            SLL_NodeComparison(category, NewNode);
        }      
    return NewNode;
    }
    else{
        return Current;
    }
}

void SLL_AppendItem(Item** Head, Item* NewItem) //링크드 리스트 노드 추가
{   //  헤드 노드가 NULL이라면 새로운 노드가 Head
    if ((*Head) == NULL ){ 
        *Head = NewItem;
    } 
    else{   //  테일을 찾아 NewItem를 연결한다. 
        Item* Tail = (*Head);
        while (Tail->NextItem != NULL)
        {
            Tail = Tail->NextItem;
        }
        Tail->NextItem = NewItem;
     }
}

void SLL_InsertItemBefore(Item** Head, Item* Current, Item* NewItem) {
    if (*Head == Current) {
        // 만약 Current가 헤드라면, NewNode를 Current 앞에 삽입합니다.
        NewItem->NextItem = *Head;
        *Head = NewItem;
    } 
    
    else {
        // 만약 Current가 헤드가 아니라면, Current 앞에 삽입할 노드를 찾아 NewNode를 삽입합니다.
        Item* temp = *Head;
        while (temp != NULL && temp->NextItem != Current) {
            temp = temp->NextItem;
        }

        if (temp != NULL) {
            NewItem->NextItem = temp->NextItem;
            temp->NextItem = NewItem;
        }
    }
}

void AddItem(Node* category, Item* NewItem){
    Item* CurrentItem = category->items;
    int temp = 0; 
    Item* HeadItem = NULL;
    Item* TailItem = NULL;

    if (CurrentItem == NULL){
        SLL_AppendItem(&category->items, NewItem);
        return;
    }

    while (1){
        temp = strcmp(NewItem->Data, CurrentItem->Data); 

        if (temp == 0){
                printf("이미 항목이 존재합니다. \n");
                free(NewItem);
                return;
        }
        
        else if((CurrentItem->NextItem == NULL)&&(temp > 0)){
            SLL_AppendItem(&category->items, NewItem);
            return;
        }

        else if ((CurrentItem->NextItem != NULL)&&(temp > 0)){ 
            CurrentItem = CurrentItem->NextItem;
        }

        else{
            SLL_InsertItemBefore(&category->items, CurrentItem, NewItem);
            return;
        }
    }
}

int main(void){

    Node* List = NULL;
    Node* Current = NULL;
    Node* NewNode = NULL;
    Node* Head = NULL;
    Node* Tail = NULL;
    Node* TargetCategory = NULL;

    Item* NewItem = NULL;
    Item* CurrentItem = NULL;

    char input[100];
    int number, Location = 0, NodeCount = 0, ItemCount = 0;
    char category[30]; //30자를 넘지 않는다
    char item[30];

    while(1){
        printf("명령을 입력하세요: ");
        scanf(" %s", input);

        splitCommand(input, &number, category, item);

        switch (number){
            case -1:
                exit(0);
                break;    
            
            case 0:
                NewNode = SLL_CreateCategory(category);
                
                if (List == NULL){
                    SLL_AppendNode(&List, NewNode);
                }

                else {
                    SLL_NodeComparison(&List, NewNode);
                }
                break;

            case 1:
                NewItem = SLL_CreateItem(item);

                TargetCategory = SLL_FindingNode(&List, category);
                AddItem(TargetCategory, NewItem);
                break;

            case 2:
                NodeCount = SLL_GetNodeCount(List);
                for (int i = 0; i < NodeCount; i++){ 
                    Current = SLL_GetNodeAt(List, i);
                    printf("%s: ", Current->Data); 

                    ItemCount = SLL_GetItemCount(Current->items);

                    CurrentItem = Current->items;
                    while (CurrentItem != NULL){
                        printf("%s", CurrentItem->Data);
                        CurrentItem = CurrentItem->NextItem;
                        if (ItemCount != 1){
                            printf(" -> ");
                            ItemCount -= 1;
                        }
                    }
                    printf("\n");
                }
                break;

            default:
                printf("[error] Invalid argument: Number must be -1, 0, 1, or 2\n");
                break;
            }
        }
        return 0;
}
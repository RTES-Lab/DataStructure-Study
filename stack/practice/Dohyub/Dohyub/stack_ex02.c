#include "ArrayStack.h"  // ArrayStack 관련 헤더 파일
#include "defs.h"        // 상수 및 정의 관련 헤더 파일

int main(void){
    int total_num = 0;                  // 대기하고 있는 총 인원
    int targetTicket = 1;               // 대기열 숫자를 비교할 변수 선언 및 정의, 1번이 최소
    ArrayStack* Stack_wait = NULL;      // 현재 줄 서있는 곳의 스택
    ArrayStack* Stack_temp = NULL;      // 한 명씩만 설 수 있는 곳

    // 사용자에게 총원 입력 받기
    printf("현재 총원이 입력: ");
    scanf("%d", &total_num);

    // 입력 인원에 대한 예외 처리
    if(total_num < Min_Student_Num || total_num > Max_Student_NUM){
        printf("입력된 총원이 유효 범위를 벗어났습니다.\n");
        return 1;
    }

    // 입력 인원에 따라 스택과 노드 생성
    AS_CreateStack(&Stack_wait, total_num);
    AS_CreateStack(&Stack_temp, total_num);

    // 입력의 역순으로 스택에 번호표 넣기 위해 배열 동적 할당 
    int* tempArray = (int*)malloc(sizeof(int) * total_num);
    
    // 할당 성공여부 판단
    if(tempArray == NULL){
        printf("동적 배열 할당 실패\n");
        return 1;
    }

    // 대기열에 있는 사람들의 번호표 입력 받기
    printf("대기열에 있는 사람들의 번호표를 차례대로 적어주세요.\n");
    printf(": ");
    for(int i = 0; i < total_num; i++){
        scanf("%d", &tempArray[total_num - 1 - i]);  // 배열의 끝부터 값을 저장
    }

    // 번호표를 역순으로 스택에 넣기
    for(int i = 0; i < total_num; i++){
        AS_Push(Stack_wait, tempArray[i]);
    }

    free(tempArray);    // 동적할당 배열 해제

    // 알고리즘 시작
    // targetTicket과 최상위 노드를 비교, 반복 조건은 스택이 비었나 안비었나
    while(!AS_IsEmpty(Stack_wait))
    {
        // 대기열의 스택의 최상위 노드 결과 임시 저장
        int temp_result = AS_Top(Stack_wait);

        // 만약에 최상위 노드와 targetTicket의 데이터값이 같으면, 노드 삭제. targetTicket ++ 
        if(temp_result == targetTicket){
            AS_Pop(Stack_wait);
            targetTicket++;
        }
        // Stack_temp가 비어있지 않고, Stack_temp의 최상위 노드와 targetTicket이 같으면, 노드 삭제. targetTicket ++
        else if(!AS_IsEmpty(Stack_temp) && AS_Top(Stack_temp) == targetTicket){
            AS_Pop(Stack_temp);
            targetTicket++;
        }
        // 같지 않으면 한 명씩만 설 수 있는 공간(스택)에 삽입
        else{
            AS_Push(Stack_temp, temp_result);
            AS_Pop(Stack_wait);
        }
    }

    // Stack_temp에서 최상위 노드가 targetTicket과 비교, 반복 조건은 스택이 비었나 안비었나
    while(!AS_IsEmpty(Stack_temp)){
        int temp_result = AS_Pop(Stack_temp);

        // 한 명씩 설 수 있는 공간에 사람들이 번호표 순서대로 데이터가 쌓여 있는지 확인
        if(temp_result == targetTicket){
            targetTicket++;
        }
        // 번호표 순서가 맞지 않으면 정상적으로 간식 받을 수 없음
        else{
            printf("Sad\n");
            AS_DestroyStack(Stack_temp);
            AS_DestroyStack(Stack_wait);

            // 프로그램 종료
            return 0;
        }
    }

    // 정상적으로 간식 받을 수 있으므로 Nice 출력
    printf("Nice\n");
    AS_DestroyStack(Stack_temp);
    AS_DestroyStack(Stack_wait);

    // 프로그램 종료
    return 0;
}

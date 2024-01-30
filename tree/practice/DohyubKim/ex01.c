#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagSBTNode 
{
    struct tagSBTNode* Left;
    struct tagSBTNode* Right;
    int leafFlag;

    ElementType Data;
} SBTNode;

#define FIRST_NODE 1

SBTNode* SBT_CreateNode( ElementType NewData )
{
    SBTNode* NewNode = (SBTNode*)malloc( sizeof(SBTNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->leafFlag = 0;  // leafFlag를 0으로 초기화
    NewNode->Data    = NewData;

    return NewNode;
}


void SBT_DestroyNode( SBTNode* Node )
{
    free(Node);
}

void SBT_DestroyTree( SBTNode* Node )
{
    if ( Node == NULL )
        return;

    //  왼쪽 하위 트리 소멸 
    SBT_DestroyTree( Node->Left );

    //  오른쪽 하위 트리 소멸 
    SBT_DestroyTree( Node->Right );

    //  뿌리 노드 소멸 
    SBT_DestroyNode( Node );
}

// 왼쪽 노드로 이동하는 함수
void MoveLeft(SBTNode** node) {
    if ((*node)->Left != NULL) {
        *node = (*node)->Left;
    }
}

// 오른쪽 노드로 이동하는 함수
void MoveRight(SBTNode** node) {
    if ((*node)->Right != NULL) {
        *node = (*node)->Right;
    }
}


int main(void){
    int total_Node = 0;
    int node_num = 1;

    printf("총 노드의 개수 입력: \n");
    scanf("%d", &total_Node);
    if (total_Node < 1 || total_Node > 200000)
    {
        return -1;
    }

    // 입력받은 총 노드의 개수만큼 nodes배열에 메모리 할당
    SBTNode **nodes = (SBTNode**)malloc(sizeof(SBTNode*) * total_Node);

     // 노드의 번호를 중복 체크하기 위한 배열
    int *recorded_nodes = (int *)malloc(sizeof(int) * total_Node);
    

    // 루트 노드 초기화
    nodes[0] = SBT_CreateNode(FIRST_NODE);
    recorded_nodes[FIRST_NODE - 1] = 1; // 루트 노드 번호 기록

    for (int i = 1; i < total_Node; i++){
        // (i+1)번의 노드를 i번째 인덱스에 생성 
        nodes[i] = SBT_CreateNode(i + 1); 
    }


    while (node_num <= total_Node){
        int left_child = 0, right_child = 0;

        printf("%d번 노드의 자식 노드를 입력(-1일 경우 자식 없음): ", node_num);
       
        int scanned = scanf("%d %d", &left_child, &right_child);
        if (scanned != 2) {
            break;
        }
        
        // 입력 값이 유효한 범위 내에 있는지 확인
        if (left_child < 2 && right_child < 2 
                && left_child > total_Node && right_child > total_Node){   
            printf("잘못된 입력입니다\n");
            return -1;
        }
        else if (left_child == -1 && right_child == -1){
            nodes[node_num -1]->leafFlag = 1;            
        }
        else if (left_child == -1)
        {
            nodes[node_num - 1]->Left = NULL;
            nodes[node_num - 1]->Right = nodes[right_child - 1];
            nodes[node_num - 1]->leafFlag = 0;

            // 노드 번호 중복 체크
            if (recorded_nodes[right_child - 1] != 0) {
                printf("중복된 노드 번호입니다\n");
                return -1;
            }
            recorded_nodes[right_child - 1] = 1;
        }
        else if (right_child == -1)
        {
            nodes[node_num - 1]->Right = NULL;
            nodes[node_num - 1]->Left = nodes[left_child - 1];
            nodes[node_num - 1]->leafFlag = 0;


            // 노드 번호 중복 체크
            if (recorded_nodes[left_child - 1] != 0) {
                printf("중복된 노드 번호입니다\n");
                return -1;
            }
            recorded_nodes[left_child - 1] = 1;
        }
        else{
            // 유효한 범위 내에 있을 때만 노드 연결 설정
            nodes[node_num - 1]->Left = nodes[left_child - 1];
            nodes[node_num - 1]->Right = nodes[right_child - 1];
            nodes[node_num - 1]->leafFlag = 0;

            // 노드 번호 중복 체크
            if (recorded_nodes[left_child - 1] != 0 || recorded_nodes[right_child - 1] != 0) {
                printf("중복된 노드 번호입니다\n");
                return -1;
            }
            recorded_nodes[left_child - 1] = 1;
            recorded_nodes[right_child - 1] = 1;
        }
        node_num++;
    }

    // 구슬을 얼마나 떨어뜨릴 것인지 저장하는 변수
    unsigned long long k;
    if(k < 1 || k >  1000000000000000000ULL){
        return -1;
    }
    printf("구슬을 몇 번 떨어뜨릴건가요?: ");
    scanf("%llu", &k);
    SBTNode *tmp_node;
    unsigned long long tmp = k;

    if (k % 2 == 1) {
        tmp_node = nodes[0]->Left;
        tmp = k / 2 + 1;
    } 
    else {
        tmp_node = nodes[0]->Right;
        tmp = k / 2;
    }

    while (tmp_node->Left != NULL || tmp_node->Right != NULL) 
    {
        if(tmp_node->Left == NULL){
            MoveRight(&tmp_node);
        }
        else if(tmp_node->Right == NULL){
            MoveLeft(&tmp_node);
        }
        
        if (tmp % 2 == 1) {
            MoveLeft(&tmp_node);
            tmp = tmp / 2 + 1;
        } 
        else {
            MoveRight(&tmp_node);
            tmp = tmp / 2;
        }
    
    }
    printf("%d\n", tmp_node->Data);
    

    // 메모리를 해제
    SBT_DestroyTree(nodes[0]);
    free(nodes);

    return 0;
}

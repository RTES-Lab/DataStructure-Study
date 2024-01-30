#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagSBTNode 
{
    struct tagSBTNode* Left;
    struct tagSBTNode* Right;

    ElementType Data;
    ElementType total ;
} SBTNode;

SBTNode* SBT_CreateNode( ElementType NewData )
{
    SBTNode* NewNode = (SBTNode*)malloc( sizeof(SBTNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;
    NewNode->total   = 0;

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


SBTNode* root;

// 하위 트리 구슬 개수 비교
ElementType compare_total(SBTNode* A, int k){
    if(A->Left == NULL && A->Right == NULL){
        k--;
        if(k == 0){
            return A->Data;
        }
        compare_total(root, k);
    }
    else if(A->Left == NULL && A->Right != NULL){
        A->Right->total ++;
        compare_total(A->Right, k);
    } 
    else if(A->Left != NULL && A->Right == NULL){
        A->Left->total ++;
        compare_total(A->Left, k);
    }
    else{
        if(A->Left->total <= A->Right->total){
            A->Left->total ++;
            compare_total(A->Left, k);
        }
        else{
            A->Right->total ++;
            compare_total(A->Right, k);
        }
    }
}


int main(){
    int i, j;
    int left_node=0, right_node=0;
    int num, cnt, k;
    
    // 총 트리 노드의 개수 입력 받기
    scanf("%d", &num);

    // 전체 트리 노드들을 저장할 배열
    SBTNode* array[num];
    //int tree[num] = {0};

    // 각 트리 노드들의 주소 배열에 저장
    for(i=0;i<num;i++){
        array[i] = SBT_CreateNode(((ElementType)i)+ 1);
    }

    root = array[0];

    // 입력에 따른 트리 만들기
    while(cnt <= num){
        
        scanf("%d %d", &j, &k);
        if(j == -1 && k == -1){
            left_node = right_node;
            cnt += 2;
        }
        else if(j==-1 && k != -1){
            array[right_node]->Right = array[k-1];
            left_node = k-1;
            right_node = k-1;
            cnt ++;
        }
        else if(j != -1 && k == -1){
            array[left_node]->Left = array[j-1];
            left_node = j-1;
            cnt ++;
        }
        else{
            array[left_node]->Left = array[j-1];
            left_node = j-1;
            
            array[right_node]->Right = array[k-1];
            right_node = k-1;
        }

    }

    // k번째 구슬 입력
    scanf("%d", &k);

    // 트리에 저장될 구슬의 위치 및 노드 별 구슬 개수 구하기
    


    printf("%d", compare_total(array[0], k));

    SBT_DestroyTree(array[0]);

    return 0;
}


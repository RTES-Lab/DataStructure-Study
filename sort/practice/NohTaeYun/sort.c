#include <stdio.h>
#include <stdlib.h>
#define abs(x) ((x < 0)?-(x):(x))


int ComparePoint( const void *_elem1, const void *_elem2){
    int *elem1 = (int*)_elem1;
    int *elem2 = (int*)_elem2;

    if(*elem1 > *elem2){
        return 1;
    }
    else if(*elem1 < *elem2){
        return -1;
    }
    else{
        return 0;
    }
}

int main(void){
    int n;
    long arr[5000] = {0};
    long val[3] = {0};
    scanf(" %d",&n);
    for(int i = 0;i < n;i++){
        scanf(" %ld",&arr[i]);
    }
    qsort((void*)arr, n, sizeof(long), ComparePoint); 
    long result = 3000000001;    // 가능한 특성값의 최대가 300000000이므로 첫 비교를 위해 1 큰 수로 설정
    for(int i = 0;i < n - 2;i++){   // 첫 번째 원소는 고정.(1번째 ~ n-2번째)
        int L = i + 1, R = n - 1;
        while(L < R){
            long tmp = arr[i] + arr[L] + arr[R];
            if(abs(tmp) < abs(result)){    // 0과 더 가까우면 값을 갱신. 
                result = tmp;          
                val[0] = arr[i];
                val[1] = arr[L];
                val[2] = arr[R];
            }
            // 현 특성값의 크기를 줄이기 위해 0보다 작으면 값 증가, 크거나 같으면 값 감소
            if(tmp < 0)
                L++;
            else
                R--;
        }    
    }
    printf("%ld %ld %ld\n",val[0],val[1],val[2]);
    return 0;
}

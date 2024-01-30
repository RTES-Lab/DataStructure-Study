#include <stdio.h>
#include <stdlib.h>

#define llint long long int
#define f(x) (x>0 ? x : -x)    // 절댓값 함수

int ComparePoint( const void *_elem1, const void *_elem2 ){
    llint* elem1 = (llint*)_elem1;
    llint* elem2 = (llint*)_elem2;
 
    if ( *elem1 > *elem2)
        return 1; 
    else if ( *elem1 < *elem2)
        return -1; 
    else
        return 0;     
}

int main(){
    llint* arr;
    llint min, sum;
    int Left, Right;
    int N, i;
    int a1, a2, a3;

    scanf(" %d", &N);
    
    arr=(llint*)malloc(sizeof(llint)*N);

    for(i=0; i<N; i++)
        scanf(" %lld", &arr[i]);
    
    qsort(arr, N, sizeof(llint), ComparePoint);
    
    if(arr[N-1]<0){    // 모든 용액이 음수인 경우
        printf("%lld %lld %lld", arr[N-3], arr[N-2], arr[N-1]);
        return 0;
    }
    
    a1=0;    a2=1;    a3=N-1;
    min=f(arr[a1]+arr[a2]+arr[a3]);

    i=0;
    while(i<N-2 && min!=0){
        if(arr[i]>=0){    // 3개 다 양수인 경우(모든 용액이 양수인 경우 포함)
            if(min>f(arr[i]+arr[i+1]+arr[i+2])){
                a1=i;
                a2=i+1;
                a3=i+2;
            }
            break;        // 음수와 양수가 혼합된 경우
        }
        Left=i+1;
        Right=N-1;    
        while(Left<Right){
            
            sum = arr[i]+arr[Left]+arr[Right];
            if(min>f(sum)){
                a1=i;
                a2=Left;
                a3=Right;
                min=f(sum);
            }
            else if(sum<0)
                Left++;
            else
                Right--;
        }
        i++;
    }
    printf("%lld %lld %lld", arr[a1], arr[a2], arr[a3]);
}

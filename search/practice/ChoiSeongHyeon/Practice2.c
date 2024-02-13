#include <stdio.h>
#include <stdlib.h> 

//  리턴값이 
//  < 0 이면, _elem1이 _elem2보다 작다. 
//  = 0   이면, _elem1이 _elem2와 같다.  
//  > 0 이면, _elem1이 _elem2보다 크다.
int ComparePoint( const void *_elem1, const void *_elem2 ) 
{ 
    long long * elem1 = (long long*)_elem1; 
    long long * elem2 = (long long*)_elem2; 
 
    if ( *elem1 > *elem2) 
        return 1; 
    else if ( *elem1 < *elem2) 
        return -1; 
    else 
        return 0;     
} 

int main() 
{
    int size;
    long long k;

    scanf("%d", &size);
    scanf("%lld", &k);

    // size만큼 배열의 세로 동적할당
    long long** arr = (long long**)malloc(sizeof(long long*) * size);
    
    // size만큼 배열의 가로 동적할당 
    for (int i = 0; i < size; i++) 
    { 
        arr[i] = (long long*)malloc(sizeof(long long) * size); 
    }

    // 완성된 배열에 규칙에 맞게 값 할당
    for (int i = 1; i <= size; i++) 
    {
        for (int j = 1; j <= size; j++) 
        {
            arr[i-1][j-1] = i*j;
        }
    }

    // 일차원 배열 B 동적 할당
    long long * arr_B = (long long *) malloc(sizeof(long long) * size * size);
    
    // 배열 A의 원소를 배열 B에 입력하기 위한 변수
    long long number = 0;

    // 배열 B에 대입하는 코드로 작성
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            arr_B[number] = arr[i][j];
            number++;
        }
    }

    qsort((void*)arr_B, size*size, sizeof(long long), ComparePoint);

    printf("%lld", arr_B[k-1]);

    free(arr_B);
    
    for(long long i = 0 ; i < size ; i++)
        free(arr[i]);

    free(arr);

}
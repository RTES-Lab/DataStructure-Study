//시간 초과 + 의도대로 결과값이 안 나와서 수정이 필요함(수정 중..)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Min(x,y) ((x) < (y) ? (x) : (y))

int BinarySearch(int arr[], int Size, int Target)
{
    int Left, Right, Mid;

    Left = 1;
    Right = Size;

    while ( Left <= Right )
    {
        Mid = (Left + Right) / 2;

        if (arr[Mid - 1] < Target && Target <= arr[Mid])
            return arr[Mid];
        else if ( Target > arr[Mid])
            Left = Mid + 1;
        else
            Right = Mid - 1;
    }
    return 0;
}

int main(void){
    int N, k, num;
    int arr[100001] = {}; //편의상 인덱스를 1 크게 하기 위해 배열 크기를 10^5+1로 설정.
    scanf(" %d",&N);
    int size = N;
    for(int i = 1, cur = 1;i <= N;i++){
        num = (int)sqrt(i);
        for(int j = 1;j <= N && i / j > 0;j++)
            num += 2 * Min(i / j, j - 1);
        if(arr[cur] != num){
            arr[cur] = num; cur++;
        }
        else    size--;
    }
    scanf(" %d",&k);
    printf("%d\n",BinarySearch(arr,size,k));
}

/*
cnt는 Mid보다 작거나 같은 수의 개수이다.
cnt가 k가 되도록 하는 수는 한개가 아니고 이중 가장 작은 값이 행렬에 있다.
행렬에서 k번째 수를 A라 하고 k+1번째 수를 B라고 하면, A부터 B-1까지는 cnt가 k가 된다.
이 중에서 행렬에 있는 값은 A만 이므로 cnt가 k가 되는 숫자들 중 가장 작은 값을 출력하면 된다.

1 2  3  4  5  6
2 4  6  8  10 12
3 6  9  12 15 18
4 8  12 16 20 24
5 10 15 20 25 30
6 12 18 24 30 36

작은 수를 세는 알고리즘을 절반으로 줄일 수 있다.
*/
#include <stdio.h>
#define min(x, y) ((x<y) ? (x) : (y))   // 최소 구하는 매크로 함수

int main(){
    int N, i, k, Left, Mid, Right;
    
    scanf(" %d %d", &N, &k);
    Left = 1;     Right = k;    // k번째 수를 A라 하면, A는 A<=k를 만족한다.

    while(Left<=Right){
        //Mid값은 Right보다 Left에 가깝거나 같다
        Mid = (Left+Right)/2;   int cnt = 0;

        // Mid가 i*i보다 작을 때까지 반복
        for(i=1; Mid>=i*i; i++)
            cnt+=min(Mid/i, N);

        // 문제에 주어진 행렬이 주대각 행렬이다 (실행시간 줄이는 부분)
        cnt+=cnt-(i-1)*(i-1);

        if(cnt<k)
            Left = Mid+1;
        // 최소를 구하기 위해 cnt==k여도 right를 줄인다.
        else
            Right=Mid-1;
    }
    printf("%d", Left); // Left는 A값일 때, 이동하지 않는다
}

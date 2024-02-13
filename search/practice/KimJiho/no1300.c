#include <stdio.h>

long N, K, Low, High, Mid, cnt;

long count(long x)
{
    long sum = 0;
    for (int i = 1; i <= N; i++)
    {
        sum += (x / i) < N ? (x / i) : N;
    }
    return sum;
}

int main()
{
    scanf("%ld %ld", &N, &K);

    K = K < 1000000000 ? K : 1000000000;

    Low = 1;
    High = N * N;

    while (Low <= High)
    {
        Mid = (Low + High) / 2;

        cnt = count(Mid); // Mid보다 작거나 같은 수들의 개수

        if (cnt >= K)
        {
            // Mid보다 작거나 같은 수들의 개수가 목표 인덱스보다 많으므로 Mid값을 더 작게-> High 조정
            High = Mid - 1;
        }
        else
        {
            // Mid보다 작거나 같은 수들의 개수가 목표 인덱스보다 작으므로 Mid값을 더 크게-> Low 조정
            Low = Mid + 1;
        }
    }
    printf("%ld", Low);
    return 0;
}

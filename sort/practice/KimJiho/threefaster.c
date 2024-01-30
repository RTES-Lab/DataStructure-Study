#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long llong;

llong n;
llong a[5004];
llong ans[4];
llong max = 1e18; // 10^18로 초기화

int compare(const void *a, const void *b) {
    return (*(llong *)a - *(llong *)b);
}

int main(void) {
    scanf("%lld", &n);

    for (llong i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    qsort(a + 1, n, sizeof(llong), compare);

    if (a[n] != 0 && a[1] >= 0)    // 특정 경우에 따른 출력
        for (llong i = 1; i <= 3; i++)
            printf("%lld ", a[i]);
    else if (a[1] != 0 && a[n] <= 0)
        for (llong i = n - 2; i <= n; i++)
            printf("%lld ", a[i]);
    else if (a[1] == 0 && a[n] == 0)
        printf("0 0 0");
    else {
        for (llong i = 1; i <= n - 2; i++) {    // 세 수의 합이 0인 경우를 찾는 루프
            llong left = i + 1;
            llong right = n;

            while (left < right) {
                llong sum = a[i] + a[left] + a[right];

                if (llabs(sum) < max) {     // 절댓값이 현재까지 최소인 경우 갱신
                    max = llabs(sum);
                    ans[1] = a[i];
                    ans[2] = a[left];
                    ans[3] = a[right];
                }

                if (sum == 0) {     // 합이 0이면 더 이상 찾을 필요 없이 출력 후 종료
                    printf("%lld %lld %lld", ans[1], ans[2], ans[3]);
                    return 0;
                }

                if (sum < 0) {// 합이 음수면 left 증가, 양수면 right 감소
                    left++;
                } 
                else {
                    right--;
                }
            }
        }

        // 찾지 못한 경우 최종 결과 출력
        printf("%lld %lld %lld", ans[1], ans[2], ans[3]);
    }

    return 0;
}

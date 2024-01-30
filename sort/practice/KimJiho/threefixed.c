#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long llong;

llong n;
llong a[5004];
llong ans[4];
llong max = 1e18; //롱 롱을 10^18로 초기화

int compare(const void *a, const void *b) {
    return (*(llong *)a - *(llong *)b);
}

int main(void) {
    scanf("%lld", &n);
    
    for (llong i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    qsort(a + 1, n, sizeof(llong), compare);

    for (llong i = 1; i <= n - 2; i++) {
        llong left = i + 1;
        llong right = n;

        while (left < right) {
            llong sum = a[i] + a[left] + a[right];

            if (labs(sum) < max) { //labs: 절댓값
                max = llabs(sum);
                ans[1] = a[i];
                ans[2] = a[left];
                ans[3] = a[right];
            }

            if (sum < 0) {
                left++;
            } 
            else {
                right--;
            }
        }
    }

    printf("%lld %lld %lld\n", ans[1], ans[2], ans[3]);

    return 0;
}

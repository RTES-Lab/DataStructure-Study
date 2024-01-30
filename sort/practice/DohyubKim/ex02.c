#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int N;
long long *pHs;             // 용액의 특성값을 저장하는 배열
long long ans[3];           // 특성값이 0에 가장 가까운 세 용액의 특성값을 저장하는 배열
long long MIN = LLONG_MAX;  // 특성값의 최소값을 저장하는 변수

// 세 용액의 합을 계산하는 함수
long long tri_sum(long long a, long long b, long long c) {
    return llabs(a + b + c);  
}

void BubbleSort(long long *DataSet, int Length) {
    int i, j;
    long long temp;
    for (i = 0; i < Length - 1; i++) {
        for (j = 0; j < Length - (i + 1); j++) {
            if (DataSet[j] > DataSet[j + 1]) {
                temp = DataSet[j + 1];
                DataSet[j + 1] = DataSet[j];
                DataSet[j] = temp;
            }
        }
    }
}

void binary_search() {
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            // 이진 탐색을 위한 시작과 끝 인덱스 설정
            int s = j + 1, e = N - 1, mid;

            // 이진 탐색 실행
            while (s <= e) {
                mid = (s + e) / 2;
                long long mid_value = tri_sum(pHs[i], pHs[j], pHs[mid]);

                // 중간 값과 인접한 두 값과의 합을 비교하여 범위를 조절
                if (mid_value > tri_sum(pHs[i], pHs[j], pHs[mid - 1]))
                    e = mid - 1;
                else if (mid_value > tri_sum(pHs[i], pHs[j], pHs[mid + 1]))
                    s = mid + 1;
                else
                    break;
            }

            // 현재 찾은 조합의 특성값과 최소값을 비교하여 갱신
            if (MIN > tri_sum(pHs[i], pHs[j], pHs[mid])) {
                MIN = tri_sum(pHs[i], pHs[j], pHs[mid]);
             ans[0] = pHs[i];
             ans[1] = pHs[j];
             ans[2] = pHs[mid];
            }
        }
    }
}

int main() {
    // 용액의 개수 입력
    scanf("%d", &N);
    pHs = (long long *)malloc(N * sizeof(long long));

    // 용액의 특성값 입력
    for (int i = 0; i < N; i++)
        scanf("%lld", &pHs[i]);

    // 용액의 특성값을 정렬
    BubbleSort(pHs, N);

    // 이진 탐색을 사용하여 가장 가까운 세 용액을 찾음
    binary_search();

    // 결과 출력
    printf("%lld %lld %lld", ans[0], ans[1], ans[2]);

    // 동적으로 할당된 메모리를 해제
    free(pHs);

    return 0;
}

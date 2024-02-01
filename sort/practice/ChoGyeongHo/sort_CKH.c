#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 5000

// 용액 구조체 정의
typedef struct {
    int idx; // 용액의 인덱스
    int value; // 용액의 특성값
} Solution;

// 두 용액을 합친 결과 구조체 정의
typedef struct {
    int sum; // 두 용액의 특성값의 합
    Solution solution1; // 첫 번째 용액
    Solution solution2; // 두 번째 용액
    Solution solution3; // 세 번째 용액
} CombinedSolution;

// 정수 오름차순 비교 함수
int compare(const void *a, const void *b) {
    Solution *sol1 = (Solution *)a;
    Solution *sol2 = (Solution *)b;
    return (sol1->value - sol2->value);
}

// 두 용액을 합친 결과 구조체 생성 함수
CombinedSolution makeCombinedSolution(int sum, Solution s1, Solution s2, Solution s3) {
    CombinedSolution cs;
    cs.sum = sum;
    cs.solution1 = s1;
    cs.solution2 = s2;
    cs.solution3 = s3;
    return cs;
}

int main() {
    int N;
    int left, right;
    
    Solution solutions[MAX_N];
    Solution AnswerSolutoins[3];

    // 입력 받기
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        solutions[i].idx = i + 1;
        scanf("%d", &solutions[i].value);
    }

    // 용액을 특성값 기준으로 정렬
    qsort(solutions, N, sizeof(Solution), compare);

    
    // 초기값 설정
    CombinedSolution closestSolution = makeCombinedSolution(INT_MAX, solutions[0], solutions[1], solutions[2]);

    // 세 용액을 선택하여 특성값이 0에 가장 가까운 조합 찾기
    for (int i = 0; i < N - 2; ++i) {
        left = i + 1;   // 맨 처음 용액
        right = N - 1;  // 맨 끝의 용액

        while (left < right) {
            int sum = solutions[i].value + solutions[left].value + solutions[right].value;
            // 특성값이 0에 더 가까운 조합이라면 갱신
            if (abs(sum) < abs(closestSolution.sum)) {
                AnswerSolutoins[0] = solutions[i];
                AnswerSolutoins[1] = solutions[left];
                AnswerSolutoins[2] = solutions[right]; 

                qsort(AnswerSolutoins, 3, sizeof(Solution), compare);
                
                closestSolution = makeCombinedSolution(sum, AnswerSolutoins[0], AnswerSolutoins[1], AnswerSolutoins[2]);
            }

            // 합이 0보다 작으면 왼쪽 용액을 더 큰 값으로 변경
            if (sum < 0) {
                left++;
            }
            // 합이 0보다 크면 오른쪽 용액을 더 작은 값으로 변경
            else if (sum > 0) {
                right--;
            }
            // 합이 0이면 바로 출력하고 종료
            else {
                printf("%d %d %d\n", closestSolution.solution1.value, closestSolution.solution2.value, closestSolution.solution3.value);
                return 0;
            }
        }
    }
    
    // 가장 가까운 조합 출력
    printf("%d %d %d\n", closestSolution.solution1.value, closestSolution.solution2.value, closestSolution.solution3.value);

    return 0;
}

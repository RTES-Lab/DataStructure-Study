#include <stdio.h>

// 정의된 상수 Min과 Max
#define Min 0
#define Max 5000000

int main() {
    // 카드 크기 변수 선언
    int size; 

    // 사용자로부터 입력 받음
    scanf("%d", &size);

    // 입력값이 Min보다 작거나 같으면 에러 출력 후 종료
    if (size <= Min) {
        printf("[Error] 양수를 입력하세요\n");
        return 1;
    }

    // 입력값이 Max보다 크면 에러 출력 후 종료
    if (size > Max) {
        printf("[Error] 너무 큰 수를 입력하였습니다\n");
        return 1;
    }

    // 비교 변수 초기화
    int compare = 1;

    // 입력값보다 크거나 같은 2의 거듭제곱 찾기
    while (compare < size) {
        compare <<= 1;
    }

    // 결과 출력
    printf("%d\n", (size << 1) - compare);

    return 0;
}

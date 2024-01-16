/*
<자료구조를 사용하지 않은 과정>

1st : 1 2 3 4 5 6 ..
2st : 2 4 6 ..

1st->2st과정을 한 사이클이라고 하면, 한 사이클 씩 반복해서 카드가 한장 남을 때까지 진행한다.

규칙성 : 
1. 한 사이클마다 카드 넘버 사이 간격은 2배씩 증가한다.
2. 남은 카드가 처음으로 홀수가 된 경우, 맨앞 카드가 삭제된다. 그리고 남은 카드는 ConuntCard/2이다.
3. 남은 카드가 다시 홀수가 된 경우, 맨 앞카드가 유지 된다. 그리고 남은 카드는 ConuntCard/2 + 1이다.
4. 남은 카드가 홀수인 경우, (3), (4)가 반복된다.
5. 남은 카드가 짝수인 경우, 바로 직전 단계처럼 삭제한다. 그리고 남은 카드는 ConuntCard/2이다.
*/


#include <stdio.h>

int main(){
    int CountCards; // 카드 개수
    int Top_Num=1; // 맨위 카드 숫자
    int d=1; // 카드 넘버 사이 간격
    int mode=0; // 맨 위 카드를 제거해야 하는 경우, 0 / 제거하지 않는 경우, 1
    scanf(" %d", &CountCards);
    while(CountCards>1){ // 카드가 한장만 남을 때까지, 반복
        switch(CountCards%2){
            case 0:
                if(mode==0) // 짝수면 TopNum 변함
                    Top_Num+=d;
                break;

            case 1:
                if(mode==0) // 짝수면 TopNum 변함
                    Top_Num+=d;
                else
                    CountCards++;
                mode=(mode+1)%2;
                break;
        }
        CountCards/=2;
        d*=2;
    }
    printf("%d", Top_Num);
}
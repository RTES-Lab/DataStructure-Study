#include <stdio.h>

int Stack_Memory[1001];
int top = -1;

void Stack_Push(int);
int Stack_Pop(void);

int main()
{
    int NumberOfPeople;
    int possible = 1;
    int num;

    scanf("%d", &NumberOfPeople);    

    while (NumberOfPeople--) 
    {
        scanf("%d", &num);
        if (num == possible) 
        {
            possible++;
            while (top >= 0 && Stack_Memory[top] == possible)
            {
                Stack_Pop();
                possible++;
            }
        }
        
        else 
        {
            Stack_Push(num);
        }
    }

    if (top == -1)
        printf("Nice");
    else
        printf("Sad");

    return 0;
}

void Stack_Push(int data)
{
    Stack_Memory[++top] = data;
}

int Stack_Pop()
{
    return Stack_Memory[top--];
}
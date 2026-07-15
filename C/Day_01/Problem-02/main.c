#include <stdio.h>

int main()
{
    int input_N = 0;
    printf("출력할 피보나치의 번호를 입력하시오.\n");
    scanf("%d", &input_N);

    unsigned int prev_fibo = 0;
    unsigned int now_fibo = 1;
    if (input_N <= 0) printf("음수혹은 0번째 피보나치는 존재하지 않습니다.\n");
    else if (input_N == 1)
        printf("%d", prev_fibo);
    else if (input_N == 2)
        printf("%d", now_fibo);
    else{
        unsigned int next_fibo = 0;
        for (int i = 2; i < input_N; i++)
        {
            next_fibo = prev_fibo + now_fibo;
            if(now_fibo > next_fibo){
                printf("\n오버플로우 발생!!\n");
                break;
            }
            prev_fibo = now_fibo;
            now_fibo = next_fibo;
        }
        printf("%u", next_fibo);
    }
    
    printf("\n");
    return 0;
}
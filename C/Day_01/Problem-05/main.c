#include <stdio.h>

int main()
{
    int N = 1;
    printf("값을 입력하세요.");
    scanf("%d", &N);

    for (int i1 = 1; i1 <= N * 2 - 1; i1++)
    {
        for (int i2 = 1; i2 <= N * 2; i2++)
        {
            if (i1 >= i2 && N * 2 - i2 >= i1)
                printf("*");
            else if (N * 2 - i1 < i2 && i2 > i1)
                printf("*");
            else 
                printf(" ");
        }
        printf("\n");
    }
}
#include <stdio.h>

int main()
{
    int N = 1;
    printf("값을 입력하세요.");
    scanf("%d", &N);

    for (int i1 = 0; i1 < N; i1++)
    {
        for (int i2 = 0; i2 < N * 2 - 1; i2++)
        {
            if (N - i1 - 1 == i2)
                printf("*");
            else if (N + i1 - 1 == i2)
                printf("*");
            else if (N - 1 == i1)
                printf("*");
            else printf(" ");
        }
        printf("\n");
    }

    return 0;
}
#include <stdio.h>

int main()
{
    //printf("%lf", 99999999999999999999.0/5);

    int ip = 1;
    for (int i = 1; i < 15; i++)
    {
        printf("%d! : %d", i, ip);
        ip *= i;
    }

}
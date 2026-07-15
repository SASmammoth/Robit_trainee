#include <stdio.h>

int main()
{
    int year = 0;
    printf("년도를 입력하세요 : ");
    scanf("%d", &year);

    if(year <= 0)
        printf("윤년을 계산하는 년도는 오직 양의 정수인 년도만이 가능합니다.\n");
    else
    {
        if((year % 4 == 0&& year % 100 != 0) || year % 400 == 0)
            printf("윤년\n");
        else
            printf("윤년이 아님\n");
    }

    return 0;
}
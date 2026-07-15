#include <stdio.h>

const int COUNT = 5;
const double pre_MAX_NUM = -10000000000;
const double pre_MIN_NUM = 10000000000;

int main()
{
    double in_list[COUNT];

    for (int i = 0; i < COUNT; i++)
    {
        printf("%d 번째 실수를 입력하시오. ", i + 1);
        scanf("%lf", &in_list[i]);
        if(in_list[i] > pre_MIN_NUM || in_list[i] < pre_MAX_NUM)
            printf("너무 작거나 큰 입력이 들어옴, 제대로 된 최댓값과 최솟값을 계산할수 없음\n");
    }

    printf("===결과===\n");

    double list_sum = 0;
    double list_max = pre_MAX_NUM;
    double list_min = pre_MIN_NUM;
    for (int i = 0; i < COUNT; i++)
    {
        list_sum += in_list[i];
        if (list_max < in_list[i])
            list_max = in_list[i];
        if (list_min > in_list[i])
            list_min = in_list[i];
    }

    printf("평균은 %lf입니다.\n", list_sum / COUNT);
    printf("최댓값은 %lf입니다.\n", list_max);
    printf("최솟값은 %lf입니다.\n", list_min);
}
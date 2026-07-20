/*
    26.07.20.  컴퓨터정보공학부 장경민

    동적할당을 이용하여 배열의 최대 최소 합 평균을 구하는 함수이다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("몇개의 원소를 할당하시겠습니까? : ");
    scanf("%d", &n);

    int *list = (int *)malloc(sizeof(int) * n); // 배열을 동적으로 할당하는 부분이다.

    
    for (int i = 0; i < n; i++)
    {   
        printf("정수형 데이터 입력:");
        scanf("%d", &list[i]);
    }

    int max_num = -2100000000, min_num = 2100000000; // 최댓값과 최솟값을 임의의 수로 설정함.
    int sum_num = 0;
    double avg_num = 0;

    for (int i = 0; i < n; i++) // 반복문을 이용하여 최대최소값을 구함
    {
        if(max_num < list[i])
            max_num = list[i];
        if(min_num > list[i])
            min_num = list[i];
        sum_num += list[i];
    }
    avg_num = (double)sum_num / n;

    printf("최대값: %d\n", max_num);
    printf("최소값: %d\n", min_num);
    printf("전체합: %d\n", sum_num);
    printf("평  균:%lf\n", avg_num);

    free(list); // 메모리 할당을 해제함.

    printf("\n");
    return 0;
}
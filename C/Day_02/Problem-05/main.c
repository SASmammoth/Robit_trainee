/*
    26.07.16  컴퓨터정보공학부 장경민

    본 프로그램은 제곱ㄴㄴ수의 개수와 제곱ㄴㄴ수를 [min:max]의 범위에서 출력하는 프로그램이다.
    입력의 범위는 [1:10000]이므로 2~100까지의 제곱수를 pow_list에 많들어 놓고, 모든 [2:10000]의 수를 전부 pow_list로 나누어 pow_nn_list를 구했다.
    입력 받은 min_max의 범위를 반복문을 이용하여 제곱ㄴㄴ수의 개수를 세고 제곱ㄴㄴ수를 출력한다. 
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

#define NN_LIST_SIZE 10000  // 제곱 ㄴㄴ수의 최대 개수
#define POW_LIST_SIZE 100   // 제곱수의 최대 개수

int main()
{
    int pow_nn_list[NN_LIST_SIZE + 1] = {
        0,
    }; // 제곱ㄴㄴ수 리스트

    int pow_list[POW_LIST_SIZE + 1] = {
        0,
    }; // 제곱수 리스트

    int min_in, max_in, count = 0;
    printf("min :");
    scanf("%d", &min_in);
    printf("max :");
    scanf("%d", &max_in);

    for (int i = 2; i <= POW_LIST_SIZE; i++)
        pow_list[i] = i * i; //제곱수 계산

    for (int i1 = 2; i1 <= NN_LIST_SIZE; i1++)
    {
        for (int i2 = 2; i2 <= POW_LIST_SIZE; i2++)
        {
            if (i1 % pow_list[i2] == 0)
                pow_nn_list[i1] = 1; // 제곱ㄴㄴ리스트에서 제곱수를 전부 나누어서 떨어지는수를 저장함
        }
    }

    if (!((0 < min_in) && (min_in <= max_in) && (max_in <= NN_LIST_SIZE))) // 입력 조건을 판단함. 이상한 입력이면 프로그램을 종료
    {
        printf("0 < min <= max <= %d를 만족해야만 함\n", NN_LIST_SIZE);
        return 0;
    }

    for (int i = min_in; i <= max_in; i++) // 제곱수의 개수를 센다.
        if(!pow_nn_list[i])
            count++;

    printf("제곱 ㄴㄴ 수 : %d 개\n", count);

    for (int i = min_in; i <= max_in; i++) // 제곱수를 출력한다.
        if (!pow_nn_list[i])
            printf("%d ", i);

    printf("\n");
    return 0;
}
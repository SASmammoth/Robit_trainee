/*
    26.07.20.  컴퓨터정보공학부 장경민
    본 프로그램은 5X5의 이차원 배열을 만들어서 모래시계 모양으로 숫자를 체우는 프로그램이다.

    5x5 행렬을 선언한 후 반복문을 이용해 증가 시켜 모래시계를 배열에 저장하여 구현함.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

#define BOX_SIZE 5

int main()
{
    int matrix[BOX_SIZE][BOX_SIZE] = {
        0,
    };

    int count = 1;
    for (int i1 = 0; i1 < BOX_SIZE; i1++)
    {
        for (int i2 = 0; i2 < BOX_SIZE; i2++)
        {
            if ((i2 >= i1 && BOX_SIZE - i2 > i1) || (BOX_SIZE - i2 - 1 <= i1 && i2 <= i1)) // 모래시계 모양의 숫자를 작성하는 부분이다.
            {
                matrix[i1][i2] = count;
                count++;
            }
        }
    }

    for (int i1 = 0; i1 < BOX_SIZE; i1++) // 행렬을 출력하는 부분이다.
    {
        for (int i2 = 0; i2 < BOX_SIZE; i2++)
        {
            printf("%2d ", matrix[i1][i2]);
        }
        printf("\n");
    }
}
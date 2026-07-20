/*
    26.07.20.  컴퓨터정보공학부 장경민
    
    N1xN2 : m1 와 N2xN1 : m2 2차원 배열 2개를 동적으로 만들어서 m1의 전치행렬을 m2에 저장하는 프로그램이다.
    동적할당을 함수로 구현하여 가독성을 좋게 하였다.
    N1과 N2 사이즈를 사용자로 부터 입력받으란 말이 없어서 #define으로 선언 하였다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

#define SIZE_N1 4 //2차원 배열의 크기를 선언
#define SIZE_N2 3

int **matrix_malloc(int N1, int N2);            // 행렬을 생성하여 포인터를 반환한다.
void matrix_free(int ***m, int N1);             // 행렬의 메모리를 해제한다.
void matrix_filler(int **m, int N1, int N2);   // 행렬을 1, 2, 3, ... 형식으로 체운다.

void Transpose(int **m1, int **m2, int N1, int N2); // N1xN2 형식의 m1행열을 이용하여 m2에 전치행렬을 만든다.

void print_matrix(int **m, int N1, int N2);    // 행렬을 출력한다.

int main()
{
    int **matrix1 = matrix_malloc(SIZE_N1, SIZE_N2);
    int **matrix2 = matrix_malloc(SIZE_N2, SIZE_N1);

    matrix_filler(matrix1, SIZE_N1, SIZE_N2);

    printf("행렬1 : \n");
    print_matrix(matrix1, SIZE_N1, SIZE_N2);

    Transpose(matrix1, matrix2, SIZE_N1, SIZE_N2);
    printf("\n행렬2 : \n");
    print_matrix(matrix2, SIZE_N2, SIZE_N1);

    matrix_free(&matrix1, SIZE_N1);
    matrix_free(&matrix2, SIZE_N2);
}

void Transpose(int **m1, int **m2, int N1, int N2)
{
    for (int i1 = 0; i1 < N1; i1++)
    {
        for (int i2 = 0; i2 < N2; i2++)
        {
            m2[i2][i1] = m1[i1][i2]; // 행과 열을 반대로 저장하여 전치를 구현한다.
        }
    }
}

void print_matrix(int **m, int N1, int N2)
{
    for (int i1 = 0; i1 < N1; i1++)
    {
        for (int i2 = 0; i2 < N2; i2++)
        {
            printf("%2d ", m[i1][i2]);
        }
        printf("\n");
    }
}

int **matrix_malloc(int N1, int N2)
{
    int **m = (int **)malloc(sizeof(int *) * N1);
    for (int i = 0; i < N1; i++)
    {
        m[i] = (int *)malloc(sizeof(int) * N2);
    }

    return m;
}

void matrix_filler(int **m, int N1, int N2)
{
    int count = 1;
    for (int i1 = 0; i1 < N1; i1++)
    {
        for (int i2 = 0; i2 < N2; i2++)
        {
            m[i1][i2] = count;
            count++;
        }
    }
}

void matrix_free(int ***m, int N1)
{
    for (int i = 0; i < N1; i++)
    {
        free((*m)[i]);
    }
    free(*m);
}
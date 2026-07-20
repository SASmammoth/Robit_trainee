/*
    26.07.20.  컴퓨터정보공학부 장경민

    동적할당으로 생성된 NxN 배열에 대각선으로 숫자를 채워 넣는 프로그램이다.
    재귀함수를 이용하여 오른쪽 위부터 왼쪽 아래까지 대각으로 이동하며 숫자를 채워 넣었다. 
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

int **matrix_malloc(int N1, int N2); // 행렬을 생성하여 포인터를 반환한다.
void matrix_free(int ***m, int N1);  // 행렬의 메모리를 해제한다.

void print_matrix(int **m, int N1, int N2); // 행렬을 출력한다.

void fill_matrix_cross(int **m, int N, int pos_y, int pos_x, int count, char axis); // 행렬을 대각선으로 체운다.

int main()
{
    int N;
    printf("N을 입력하세요. ");
    scanf("%d", &N);

    if(N <= 0)
    {
        printf("N은 0 <= N 이어야 합니다.\n");
        return 0;
    }

    int **matrix = matrix_malloc(N, N);

    fill_matrix_cross(matrix, N, 0, 0, 1, 'c');

    print_matrix(matrix, N ,N);

    matrix_free(&matrix, N);
}

void fill_matrix_cross(int **m, int N, int pos_y, int pos_x, int count, char axis)
{
    //printf("%d, %d = %d, axis = %c\n", pos_y, pos_x, count, axis);

    m[pos_y][pos_x] = count;


    count++;

    if (count > N * N)
        return;
    
    if(pos_x == 0 && pos_y == N-1) // 축이 c이면 한 줄이 좌측변에서 끝나고, r이면 아래쪽에서 끝난다. 이를통해 다음번 숫자 위치를 추축한다.
    {
        axis = 'r';
        fill_matrix_cross(m, N, 1, N - 1, count, axis);
    }
    else if(axis == 'c')
    {
        if(pos_x == 0)
            fill_matrix_cross(m, N, 0, pos_y + 1, count, axis);
        else
            fill_matrix_cross(m, N, pos_y + 1, pos_x - 1, count, axis);
    }
    else if (axis == 'r')
    {
        if (pos_y == N - 1)
            fill_matrix_cross(m, N, pos_x + 1, N-1, count, axis);
        else
            fill_matrix_cross(m, N, pos_y + 1, pos_x - 1, count, axis);
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
        m[i] = (int *)calloc(N2, sizeof(int));
    }

    return m;
}

void matrix_free(int ***m, int N1)
{
    for (int i = 0; i < N1; i++)
    {
        free((*m)[i]);
    }
    free(*m);
}
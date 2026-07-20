/*
    26.07.20.  컴퓨터정보공학부 장경민

    본 프로그램은 홀수인 N1, N2를 입력받아서 중앙에서 부터 시작하여 반시계방향으로 숫자를 1씩 증가시켜서 배열을 생성하여 출력하는 프로그램이다.
    3번 과제와 비슷하게 재귀함수를 이용하여 풀었다. 사다리꼴을 무한정 그려나가는 대신에 잘린부분은 count를 안 증가시키는 방식으로 문제를 해결하였다.

    현재 좌표를 이용해 나선 모양의 벡터장을 연산하고 그걸 확인하여 숫자를 넣는 형식을 이용하였다.
    예시)
    ↙↙↙↖↖
    ↙↙↙↖↖
    ↓↓↓↖↖
    ↘↘↗↗↗
    ↘↘↗↗↗
    make_Nexus의 방향은 0:↓, ↗:1, ↖:2, ↙:3, ↘:4 의 형식으로 하였다.
    음의 y축:11, 양의 x축:12, 양의 y축:13, 음의 x축:14, 방금 down됨:10으로 하였다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

int **matrix_malloc(int N1, int N2);        // 행렬을 생성하여 포인터를 반환한다.
void matrix_free(int ***m, int N1);         // 행렬의 메모리를 해제한다.
void print_matrix(int **m, int N1, int N2); // 행렬을 출력한다.

void make_Nexus(int **m, int N1, int N2, int pos_y, int pos_x, int count, int direction);   // 과제의 출력에 맞는 형태의 배열을 만드는 함수
int is_vaild(int N1, int N2, int pos_y, int pos_x);                                         // 현재의 위치가 유효한지 확인하는 함수, 유효하다면 1, 유효하지않다면 0을 리턴한다.

int find_pos(int N1, int N2, int pos_y, int pos_x, int derection);                          // 현재 위치를 이용해 다음 위치를 리턴함 위의 주석에 방향이 있음

const int direction_def[5][2] = {{1, 0}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1}};                      // make_Nexus의 방향을 리스트에 저장해 놓음.

int main()
{
    int N1, N2;
    printf("N1과 N2를 입력하시오.(N1과 N2는 홀수.)\n");
    scanf("%d %d", &N1, &N2);

    if (!(0 < N1 && N1 % 2 == 1 && 0 < N2 && N2 % 2 == 1)) // 입력 예외 처리
    {
        printf("0 < N1, 0 < N2, N1과 N2는 홀수 여야함.\n");
        return 0;
    }

    int **matrix = matrix_malloc(N1, N2);

    make_Nexus(matrix, N1, N2, N1 / 2, N2 / 2, 1, 0);
    print_matrix(matrix, N1, N2);

    matrix_free(&matrix, N1);
}

int is_vaild(int N1, int N2, int pos_y, int pos_x)
{
    if (0 <= pos_y && pos_y < N1 && 0 <= pos_x && pos_x < N2)
        return 1;
    else
        return 0;
}

// make_Nexus의 방향은 0:↓, ↗:1, ↖:2, ↙:3, ↘:4 의 형식으로 하였다.
//음의 y축 : 11, 양의 x축 : 12, 양의 y축 : 13, 음의 x축 : 14, 방금 down됨 : 10으로 하였다.

int find_pos(int N1, int N2, int pos_y, int pos_x, int derection)
{
    if (pos_y == N1 / 2 && pos_x == N2 / 2)
        return 20;
    else if (pos_y > N1 / 2 && pos_x == N2 / 2) // (음의 y축)
        return 11;
    else if (pos_y == N1 / 2 &&pos_x > N2 / 2) // (양의 x축)
        return 12;
    else if (pos_y < N1 / 2 && pos_x == N2 / 2) // (양의 y축)
        return 13;
    else if (pos_y == N1 / 2 && pos_x < N2 / 2) // (음의 x축)
        return 10;

    if (pos_y > N1 / 2 && pos_x > N2 / 2)
        return 1;
    else if (pos_y < N1 / 2 && pos_x > N2 / 2)
        return 2;
    else if (pos_y < N1 / 2 && pos_x < N2 / 2)
        return 3;
    else if (pos_y > N1 / 2 && pos_x < N2 / 2)
        return 4;

    return -1;
}

void make_Nexus(int **m, int N1, int N2, int pos_y, int pos_x, int count, int direction)
{
    if(count > N1 * N2) // 모든 칸을 채웠으면 재귀를 끝낸다.
        return;

    if (is_vaild(N1, N2, pos_y, pos_x)) // 현재위치가 배열 안에 있는지 확인. 없으면 작성을 안한다.
    {
        m[pos_y][pos_x] = count;
        count++;
    }

    int next_positon = find_pos(N1, N2, pos_y, pos_x, direction);

    make_Nexus(m, N1, N2, pos_y + direction_def[next_positon % 10][0], pos_x + direction_def[next_positon % 10][1], count, next_positon % 10);
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
    //printf("\n");
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

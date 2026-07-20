/*
    26.07.20.  컴퓨터정보공학부 장경민

    본 프로그램은 N1xN2 행렬을 입력받아서 반시계방향으로 돌아가는 숫자규칙의 배열을 생성하는 프로그램이다.
    현재 위치와 주변 블럭의 정보를 입력 받아 다음의 위치를 계산하는 함수를 이용하여 배열의 숫자를 생성하였다. 
    막혀있는 블럭의 인덱스는 다음과 같이 정의하였다.
     0
    3X1     X:현재 위치
     2
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

int **matrix_malloc(int N1, int N2);                                        // 행렬을 생성하여 포인터를 반환한다.
void matrix_free(int ***m, int N1);                                         // 행렬의 메모리를 해제한다.
void print_matrix(int **m, int N1, int N2);                                 // 행렬을 출력한다.

void Pathfinder(int **m, int N1, int N2, int pos_y, int pos_x, int count);  // 과제 3과 같은 그림을 그려주는 재귀함수이다.
int *block_finder(int **m, int N1, int N2, int pos_y, int pos_x);           // pos에서 사방에 어디가 막혀있는지 리턴하는 함수이다.
int is_block(int **m, int N1, int N2, int pos_y, int pos_x);                // pos가 막혀있는지 확인하는 함수이다. pos가 블럭이라면 1을 리턴한다.
int go_dir(int *list);                                                      // 막혀있는 위치 배열을 보고 다음 이동칸을 출력하는 리턴하는 함수이다.

#define SIZE_OF_DIR 4 // 방향의 개수이다.

const int direction_def[SIZE_OF_DIR][2] = { {-1, 0},
                                            {0, 1},
                                            {1, 0},
                                            {0, -1} }; // 4 방향의 정의이다.

int main()
{
    int N1, N2;
    printf("N1, N2를 입력하시오.\n");
    scanf("%d %d", &N1, &N2);

    int **matrix = matrix_malloc(N1, N2);

    Pathfinder(matrix, N1, N2, 0, 0, 1);

    print_matrix(matrix, N1, N2);

    matrix_free(&matrix, N1);
}

void Pathfinder(int **m, int N1, int N2, int pos_y, int pos_x, int count)
{
    m[pos_y][pos_x] = count;
    count++;

    if (count > N1 * N2) // 깊이가 N1*N2가 되면 함수를 종료한다.
        return;

    int *list = block_finder(m, N1, N2, pos_y, pos_x); // 상하좌우 막혀있는 위치의 리스트를 구한다.

    int next_dir = go_dir(list); // 다음 진행방향을 받아옴

    //printf("\nndir = %d\n", next_dir);
    //print_matrix(m, N1, N2);

    Pathfinder(m, N1, N2, pos_y + direction_def[next_dir][0], pos_x + direction_def[next_dir][1], count);

    free(list);
}

int go_dir(int *list)
{
    int count = 0; // 막혀있는 개수를 센다.
    for (int i = 0; i < SIZE_OF_DIR; i++)
    {
        if(list[i])
            count++;
    }

    if(count == 1) // 한쪽만 막혀있으면 다음 위치는 위의 정의에서 다음 숫자이다.
    {
        for (int i = 0; i < SIZE_OF_DIR; i++)
            if(list[i])
                return (i + 1) % SIZE_OF_DIR;
    }
    else if(count == 2) // 2개가 막혀있는 경우의 수는 하드코딩을 하였다.
    {
        if(list[0] && list[1])
            return 2;
        else if(list[1] && list[2])
            return 3;
        else if(list[2] && list[3])
            return 0;
        else if (list[3] && list[0])
            return 1;

        return -1;
    }
    else if (count == 3) // 3개가 막혀있는 경우는 길이 한가지 밖에 안 남는다.
    {
        for (int i = 0; i < SIZE_OF_DIR; i++)
        {
            if(!list[i])
                return i;
        }
    }

    return -1; //더이상 진출 할수가 없으면 -1을 리턴한다.
}

int is_block(int **m, int N1, int N2, int pos_y, int pos_x)
{
    if (pos_y < 0 || N1 <= pos_y || pos_x < 0 || N2 <= pos_x)
        return 1;
    else if (m[pos_y][pos_x] != 0)
        return 1;
    else
        return 0;
}

int *block_finder(int **m, int N1, int N2, int pos_y, int pos_x)
{
    int *list = (int *)calloc(SIZE_OF_DIR, sizeof(int));

    for (int i = 0; i < SIZE_OF_DIR; i++)
    {
        list[i] = is_block(m, N1, N2, pos_y + direction_def[i][0], pos_x + direction_def[i][1]);
    }

    return list;
}

void print_matrix(int **m, int N1, int N2)
{
    printf("\n");
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

/*
    26.07.22.  컴퓨터정보공학부 장경민

    본 프로그램은 2차원 배열 동적할당을 이용해서 달팽이를 만들어야 한다.

    void print(int *row, int *col, int **pArr);
    void arr_ij(int *sizeRow, int *sizeCol, int **pArr);
    2개의 함수를 구현하여 달팽이를 만들고, 달팽이를 출력한다.
    
    한 블럭을 기준으로 진행방향은 : 위쪽이 0이고 시계방향으로 1, 2, 3 순서이다. 회전순서는 달팽이가 전진 못할때 꺽는 방향으로 잡았다.
     0
    3X1
     2

    print 와 arr_ij에서 row, col(sizeRow, sizeCol) 굳이 포인터 변수를 넘기는 이유를 잘 모르겠다.
    만약 두 함수가 재귀 함수이거나 함수 안에서 다른 함수를 부를때 행렬값을 전달한다 해도 row, col은 정수형이므로 복사해서 전달해도 시간 소모가 크지 않다.
    또 만약 함수 안에서 row, col(sizeRow, sizeCol)의 원본 값을 실수로 바꾸어 버리면 문제가 생기기 때문에 굳이 포인터 변수로 넘기는 이유를 잘 모르겠다.
    차라리 int나 const int가 더 좋지 않나 하는 생각이 든다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

void print(int *row, int *col, int **pArr);
void arr_ij(int *sizeRow, int *sizeCol, int **pArr);

const int dir_def[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main()
{
    int **arr = NULL;
    int row, col, sizeRow, sizeCol;

    printf("열의 수를 입력하세요: ");
    scanf("%d", &sizeCol);
    printf("행의 수를 입력하세요: ");
    scanf("%d", &sizeRow);

    row = sizeRow;
    col = sizeCol;

    // 2차원 동적 할당.
    arr = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++)
        arr[i] = (int*)calloc(col, sizeof(int) * col);

    
    arr_ij(&sizeRow, &sizeCol, arr);
    print(&row, &col, arr);

    for (int i = 0; i < row; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

void arr_ij(int *sizeRow, int *sizeCol, int **pArr)
{
    int pos_y = 0, pos_x = 0;   // 현재 커서의 포지션
    int count = 1;

    int prev_dir = 1;

    while(count <= (*sizeCol) * (*sizeRow)) // int* 형식으로 받아왔기 때문에 값을 가져오려면 *sizerow를 해야한다.
    {
        *(*(pArr + pos_y) + pos_x) = count; // 오프셋이 없으므로 포인터 연산으로 접근해야 함.
        count++;

        int next_pos_y = pos_y + dir_def[prev_dir][0]; // 다음 진행 방향
        int next_pos_x = pos_x + dir_def[prev_dir][1];

        if(next_pos_x < 0 || next_pos_y < 0 || next_pos_y >= *sizeRow || next_pos_x >= *sizeCol)
        {
            prev_dir = (prev_dir + 1) % 4;
            next_pos_y = pos_y + dir_def[prev_dir][0]; // 다음 진행 방향 변경
            next_pos_x = pos_x + dir_def[prev_dir][1];
        }
        else if (*(*(pArr + next_pos_y) + next_pos_x) != 0)
        {
            prev_dir = (prev_dir + 1) % 4;
            next_pos_y = pos_y + dir_def[prev_dir][0]; // 다음 진행 방향 변경
            next_pos_x = pos_x + dir_def[prev_dir][1];
        }

        pos_y = next_pos_y; // 다음 진행 방향으로 커서 변경
        pos_x = next_pos_x;
    }
}



void print(int *row, int *col, int **pArr)
{
    printf("\n");
    for (int i1 = 0; i1 < *row; i1++)
    {
        for (int i2 = 0; i2 < *col; i2++)
            printf("%3d ", *(*(pArr + i1) + i2));
        printf("\n");
    }
}
/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 동적할당으로 좌표를 입력 받고, 좌표 사이의 거리를 비교하여 입력한 좌표 중에서 가장 멀리 떨어진 좌표를 구하는 프로그램이다.

    좌표 구조체는 x,y 좌표와 다른 좌표의 거리 총합 3개의 요소로 구성하였다.
    입력을 전부 받은 뒤 거리를 구하는 함수를 이용하여 거리의 합을 구한뒤 저장, 총합이 가장 큰 좌표/거리를 출력한다.

    예시의 입력형태가 정수형 처럼 보여서 좌표는 정수형으로 저장하였다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // 두 점사이의 거리를 구할때 sqrt가 필요함. 구조체 실습에 있어서 사용함.

typedef struct _poistion
{
    int pos_x;
    int pos_y;
    double distanse_sum;
}POINT;

void input_point(POINT *point_list, int N);     // 점들을 입력받는 부분
void com_dis(POINT *point_list, int N);         // 점간의 거리를 계산하는 부분
void print_point(POINT *point_list, int N);     // 좌표 리스트를 출력하는 부분

void print_point_dis(POINT *point_list, int N); // 거리가 가장 긴걸 출력하는 부분

int main()
{
    int N;
    scanf("%d", &N);

    POINT *point_list = (POINT *)malloc(sizeof(POINT) * N);

    input_point(point_list, N);

    com_dis(point_list, N);

    //print_point(point_list, N);

    print_point_dis(point_list, N);

    free(point_list);
    printf("\n");
    return 0;
}

void print_point_dis(POINT *point_list, int N)
{
    int temp_i = 0;
    double temp_max = -1; // 거리는 음수가 나올수 없으므로 -1을 초기값으로 해도 괜찮음

    for (int i = 0; i < N; i++)
    {
        if(temp_max < point_list[i].distanse_sum)
        {
            temp_max = point_list[i].distanse_sum;
            temp_i = i;
        }
    }

    printf("가장 거리가 먼 좌표는 (%d, %d)이며, 다른 좌표의 거리의 총합은 약 %.1lf입니다.\n", point_list[temp_i].pos_x, point_list[temp_i].pos_y, point_list[temp_i].distanse_sum);
}

void com_dis(POINT *point_list, int N)
{
    for (int i1 = 0; i1 < N; i1++)
    {
        point_list[i1].distanse_sum = 0;

        for (int i2 = 0; i2 < N; i2++)
        {
            int x_diff = point_list[i1].pos_x - point_list[i2].pos_x;
            int y_diff = point_list[i1].pos_y - point_list[i2].pos_y;
            point_list[i1].distanse_sum += sqrt((double)(x_diff * x_diff + y_diff * y_diff));
        }
    }
}

void print_point(POINT *point_list, int N)
{
    for (int i = 0; i < N; i++)
        printf("%d %d dis : %lf\n", point_list[i].pos_x, point_list[i].pos_y, point_list[i].distanse_sum);
}

void input_point(POINT *point_list, int N)
{
    for (int i = 0; i < N; i++)
    {
        int temp_x, temp_y;
        scanf("%d %d", &temp_x, &temp_y);

        point_list[i].pos_x = temp_x;
        point_list[i].pos_y = temp_y;
    }
}
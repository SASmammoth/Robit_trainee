/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 임의의 숫자를 입력 받으면 그 숫자로 구성된 도형-패턴을 만드는 것이다.

    도형 본체 포인터 하나와, 입력받는 수 스택의 포인터 2개를 만들었다.
    그 후 반복문을 이용해 스택포인터를 한칸씩 이동하며 도형본체에 넣는다.
    종료는 두자리 숫자를 입력하면 된다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

#define SIZE_Y 3    // 도형 크기에 대해 말이 없어서 임의의 숫자를 넣었다.
#define SIZE_X 4

void input_num(int **text, int** num_list, int deep); // 포인터와 숫자리스트를 입력받아 출력 문자열을 만드는 코드
void print_num(int **text); // 포인터를 입력 받아 출력 하는 코드

int main()
{
    int num_list_max = 2;
    int *text = (int *)malloc(sizeof(int) * SIZE_X * SIZE_Y);   // 출력하는 본체 포인터. 크기가 SIZE_Y X SIZE_X와 같다.
    int *num_list = (int *)malloc(sizeof(int) * num_list_max);  // 입력 받는 숫자를 저장하는 스택

    int temp_;
    int deep = 0;
    while (1) // 형식에 맞지 않는 숫자(음수, 10이상)을 입력하면 프로그램이 종료 된다.
    {
        scanf("%d", &temp_);
        if(temp_ < 0 || 10 <= temp_)
        {
            printf("음수와 10이상의 수는 형식에 맞지 않아 도형이 못생겨 진다.\n");
            break;
        }

        *(num_list + deep) = temp_; // 스택에 입력받은 수를 추가한다.
        deep++;


        if (num_list_max / 2 <= deep) // 숫자가 늘어나면 num_list를 더 할당한다.
        {
            num_list_max *= 2;
            num_list = (int *)realloc(num_list, num_list_max * sizeof(int));
        }

        input_num(&text, &num_list, deep);

        print_num(&text);
    }

    free(text);
    free(num_list);

    printf("\n");
    return 0;
}

void print_num(int **text)
{
    for (int i1 = 0; i1 < SIZE_Y; i1++)
    {
        for (int i2 = 0; i2 < SIZE_X; i2++)
        {
            printf("%d", *(*text + i1 * SIZE_X + i2)); // 포인터 형태로 출력한다.
        }
        printf("\n");
    }
    printf("\n");
}

void input_num(int **text, int** num_list, int deep)
{
    int count = 0;
    while(count < SIZE_Y * SIZE_X)
    {
        *(*(text) + count) = *(*num_list + (count % deep)); // 본체 포인터(출력하는 배열)에 포인터 형식으로 숫자를 넣는다.

        //printf("%d\n", *(*(text) + count));
        count++;
    }
}

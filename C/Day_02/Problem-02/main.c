/*
    26.07.16 12:13 컴퓨터정보공학부 장경민

    본 프로그램은 숫자 8개의 입력을 받아 선택정렬의 과정과 결과를 출력하는 프로그램이다.
    최대한 함수를 사용하도록 지향하였고, 입/출력 형식을 예시와 같도록 노력하였다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

void swap(int list[], int id1, int id2); // 리스트와 인덱스 2개를 받아서 서로 위치를 바꾸는 부분이다.
void input_list(int list[]); // 리스트를 입력받는 부분이다. 프롬프트 출력와 입력 숫자 입력을 받는다.
void print_list(const int list[]); // 리스트를 최종 출력 형식에 맞게 출력하는 부분이다.
void print_during(const int list[]); // 리스트를 중간과정 출력 형식에 맞게 출력한다.
void choice_sort(int list[], int size); // 선택정렬을 실행하는 함수이다.

//const int INPUT_SIZE = 8 // 이러한 형식의 배열 선언이 VS에서 동작하지 않는다는걸 알게되어 수정함. C언어 1일차는 VS에서 동작하지 않을수 있다.
#define INPUT_SIZE 8 // 매직넘버를 피하기 위해 입력 정수 개수를 선언하는 부분이다.

int main()
{
    int list[INPUT_SIZE];

    input_list(list);
    print_during(list);
    choice_sort(list, INPUT_SIZE - 1);
    print_list(list);

    return 0;
}

void choice_sort(int list[], int size)
{
    int shorted_ = size;
    while (shorted_ > 0)
    {
        int max_num = list[shorted_], max_index = shorted_; // 최댓값을 정렬 안된 부분의 가장 끝 인덱스의 값으로를 선택한다.
        for (int i1 = 0; i1 < shorted_; i1++)
        {
            if (max_num < list[i1]) // 최댓값을 찾는다.
            {
                max_num = list[i1];
                max_index = i1;
            }
        }

        if (max_index != shorted_) // 최댓값의 변동이 있을때에만 swap이랑 출력을 한다.
        {
            swap(list, shorted_, max_index);
            print_during(list);
        }
        shorted_--; // 정렬된 위치를 앞으로 한칸 옮긴다.
    }
}

void swap(int list[], int id1, int id2)
{
    int temp_ = list[id1];
    list[id1] = list[id2];
    list[id2] = temp_;
}

void input_list(int list[])
{
    printf("입력\n");
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        printf("\n%d : ", i);
        scanf("%d", &list[i]);
    }
}

void print_list(const int list[])
{
    printf("\n출력\n");
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        printf("\n  %d : %d\n", i, list[i]);
    }
}

void print_during(const int list[])
{
    printf("\n");
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

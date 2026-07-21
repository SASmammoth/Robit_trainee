/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 문장을 입력받아서 문장을 거꾸로 출력하고, 최다 등장 문자를 찾는다.

    동적 할당을 이용하여 끝까지 입력 받은뒤에 스택포인터와 주소를 이용하여 뒤집어 출력하고 최다 등장 문자를 찾는다.
    최다등장문자가 여러개 있을때에 대해 말이 없어서, ascii 상에 뒤쪽에 있는 문자가 출력되게 만들었다. 
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

char *input_text(int *text_top);     // 임의의 문장을 입력 받아 포인터를 반환한는 코드

void print_reverse(char *text, int size_of_text);   // 거꾸로 출력하는 함수, 최빈값도 센다.

int main()
{
    int text_top;
    char *text = input_text(&text_top);

    print_reverse(text, text_top);

    free(text);

    printf("\n");
    return 0;
}

void print_reverse(char *text, int size_of_text)
{
    int cal_Mode[128] = { // 가장 많이 나오는 문자를 세기위해 만든 배열
        0,
    };

    for (int i = size_of_text - 1; i >= 0; i--)
    {
        char temp_ = *(text + i);
        printf("%c", temp_);

        if (temp_ != ' ') // 문자가 띄어쓰기가 아니라면 문자 빈도 추가.
        {
            cal_Mode[(int)temp_]++;
        }
    }

    int max_num = -1;
    int max_index;
    for (int i = 0; i < 128; i++)
    {
        if (max_num < cal_Mode[i])
        {
            max_index = i;
            max_num = cal_Mode[i];
        }
    }

    printf("\n최다등장문자 : %c", max_index);
}

char *input_text(int *text_top)
{
    char *text = (char *)malloc(sizeof(text) * 2);
    int top = 0, text_size = 2;
    char temp_;
    while (1)
    {
        scanf("%c", &temp_);
        if (temp_ == '\n') // 문자 끝이 오면 입력종료
            break; 

        text[top] = temp_;
        top++;

        if(text_size / 2 <= top) // 버퍼가 부족하면 버퍼 추가
        {
            text_size *= 2;
            text = (char *)realloc(text, text_size);
        }
    }

    text[top] = '\0';
    *text_top = top;
    return text;
}
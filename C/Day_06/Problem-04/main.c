/*
    26.07.23.  컴퓨터정보공학부 장경민
    본 프로그램은 팰린드롬을 판별하는 프로그램이다.

    hint: 스택과 큐를 이용(LIFO, FIFO)
    이렇게 작성되어 있다. 힌트에 작성된 것이여서 굳이 스택, 큐를 사용하지 않고, 문자열 2개를 사용하였다. 
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

void cut_enter(char *s); // fgets로 받아온 문자에 있는 \n을 없앤다.
char *cut_space(char *s, int *num_); // 문자열에 있는 ' '을 없앤다. 매개변수는 free하고 새 리턴값을 준다. num의 문자열의 길이에 관한 포인터이다.
int is_Palindraome(char *s1, int num_); // 팰린드롬인지 검사. 맞으면 1 아니면 0을 반환한다.
void copy_str_reverse(const char *original, char *copied, int num_); // 문자열을 뒤집어서 복사한다.

#define TEXT_NUM 100 // 입력받을수 있는 최댓값. 문자열을 무한히 입력바등라는 말이 없었기 때문에, 최대값을 지정하였다.

int main()
{
    char *text01 = (char*)malloc(sizeof(char) * (TEXT_NUM + 1));

    int num;

    fgets(text01, TEXT_NUM, stdin);
    cut_enter(text01);
    text01 = cut_space(text01, &num);

    if(is_Palindraome(text01, num))
        printf("is_Palindraome\n");
    else
        printf("is_not_Palindraome\n");

    free(text01);
    printf("\n");
    return 0;
}

void copy_str_reverse(const char *original, char *copied, int num_)
{
    for (int i = 0; i < num_; i++)
        copied[num_ - i - 1] = original[i];
    
    for (int i = num_; i < TEXT_NUM; i++) // 뒤쪽에 \0추가
        copied[i] = '\0';
}

int is_Palindraome(char *s1, int num_)
{
    int is_pal = 1;
    char *s2 = (char *)malloc(sizeof(char) * (TEXT_NUM + 1));

    copy_str_reverse(s1, s2, num_);

    for (int i = 0; i < num_; i++)
    {
        if(s1[i] != s2[i])
            is_pal = 0;
    }

    free(s2);
    return is_pal;
}

char *cut_space(char *s, int *num_)
{
    char *temp = (char *)malloc(sizeof(char) * (TEXT_NUM + 1));

    int i = 0, ti = 0;
    for (; s[i] != '\0'; i++)
    {
        if (s[i] != ' ')
        {
            temp[ti] = s[i];
            ti++;
        }
    }
    *num_ = ti; // 문자열의 길이

    for (; ti < TEXT_NUM + 1; ti++) // a문자열 뒤에 \0 추가
        temp[ti] = '\0';

    free(s);
    return temp;
}

void cut_enter(char *s)
{
    while (*s != '\0')
    {
        if (*s == '\n')
            *s = '\0';
        s++;
    }
}

/*
    26.07.20.  컴퓨터정보공학부 장경민

    본 프로그램은 동적할당을 이용하여 스택을 구현하고, HTML 중첩 구조를 시각적으로 표현하는 프로그램이다.
    <div>, <p>등을 토큰화 하여 스택에 저장하고, 문자열은 따로 토큰과 문자열포인터 배열을 만들어 메칭 시켰다.
    HTML의 태그는 더 많이 존재하고, 각 태그 별 규칙도 있을수 있지만 일단 예시에 나와있는 3가지만 구현하였다.

    토큰은 다음과 같다.
    <div>, </div> : 2, -2
    <p>, </p> : 3, -3
    <b>, </b> : 4, -4
    문자열 : 0
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

#define NUM_TAG 3
#define SIZE_TAG 10

char *read_cmd();                               // 끝을 모르는 문자열을 입력받아 배열에 저장함.
int str_cmp(char *str1);                        // 문자열을 토큰과 비교하여, 토큰을 반환한다. 잘못된 문자열은 -1을 반환한다.
int *simple_paser(char *cmd, char ***str, int **str_stack_size, int *token_list_size, int *text_list_size); // 간단한 파서이다. 토큰스택을 반환한다.
void print_HTML(int *token_list, char **text_list, int token_list_size, int text_list_size);             // HTML을 출력한다.

const char tag_list_start[NUM_TAG][SIZE_TAG] = {"<div>",
                                                "<p>",
                                                "<b>"};
const char tag_list_end[NUM_TAG][SIZE_TAG] = {"</div>", "</p>", "</b>"};


int main()
{
    char *cmd = read_cmd();

    char **text_list; // 문자열 리스트
    int *text_stack_size; // 개별문자열 크기 리스트
    int token_list_size, text_list_size; // 토큰 리스트 크기와 문자열 리스트 크기
    int *token_list = simple_paser(cmd, &text_list, &text_stack_size, &token_list_size, &text_list_size);

    print_HTML(token_list, text_list, token_list_size, text_list_size);

    for (int i = 0; i < text_list_size; i++)
        free(text_list[i]);
    free(text_list);
    free(text_stack_size);
    free(cmd);
    free(token_list);
}

void print_HTML(int *token_list, char **text_list, int token_list_size, int text_list_size)
{
    

    for (int i = 0; i < token_list_size; i++) // 입력이 이상한지 확인
    {
        if(token_list[i] == -1)
        {
            printf("올바르지 않은 입력\n");
            return;
        }
    }
    int *cheack_stack = (int*)malloc(sizeof(int) * token_list_size);
    int cheack_top = 0;
    for (int i = 0; i < token_list_size; i++)
    {
        int temp_ = token_list[i];
        if(temp_ == 0) continue;

        if(temp_ > 0)
        {
            cheack_stack[cheack_top] = temp_;
            cheack_top++;
        }
        else
        {
            if(cheack_top == 0 || cheack_stack[cheack_top-1] != -temp_)
            {
                printf("올바르지 않은 입력\n");
                return;
            }
            cheack_top--;
        }
    }

    int deep = 0;
    int ti = 0;
    for (int i = 0; i < token_list_size; i++)
    {
        int index_counter = token_list[i] < 0 ? token_list[i] * -1 : token_list[i];

        if(token_list[i] < 0)
            deep--;

        for (int d = 0; d < deep; d++)
            printf("\t");
        
        if(token_list[i] > 0)
        {
            printf("%s\n", tag_list_start[index_counter - 2]);
            deep++;
        }
        else if(token_list[i] < 0)
        {
            printf("%s\n", tag_list_end[index_counter - 2]);
        }
        else
        {
            printf("%s\n", text_list[ti]);
            ti++;
        }
    }

    free(cheack_stack);
}

int str_cmp(char *str1)
{
    int index = 0;
    while (str1[index] != '>' && str1[index] != '\0')
    {
        index++;
    }

    for (int i1 = 0; i1 < NUM_TAG; i1++) // 여는 태그를 확인한다.
    {
        int temp_ = 1;
        for (int i2 = 0; i2 < index; i2++)
        {
            if(str1[i2] != tag_list_start[i1][i2])
                temp_ = 0;
        }
        if (temp_ && tag_list_start[i1][index] == '>')
            return i1 + 2;
    }

    for (int i1 = 0; i1 < NUM_TAG; i1++) // 닫는 태그를 확인한다.
    {
        int temp_ = 1;
        for (int i2 = 0; i2 < index; i2++)
        {
            if (str1[i2] != tag_list_end[i1][i2])
                temp_ = 0;
        }
        if (temp_ && tag_list_end[i1][index] == '>')
            return -i1 - 2;
    }

    return -1;
}

int *simple_paser(char *cmd, char ***str, int **str_stack_size, int *token_list_size, int *text_list_size)
{
    int *token_stack = (int *)malloc(sizeof(int) * 4); // 반환할 토큰 스택을 생성한다.
    int token_size_buf = 4, token_top = 0;

    char **text = (char**)malloc(sizeof(char *) * 4); // 문자열 스택을 생성한다.
    int text_size = 4, text_top = 0;
    *str_stack_size = (int *)malloc(sizeof(int *) * 4); // 문자열 스택을 해제하기 위한 문자열스택크기스택을 생성한다.

    int index = 0;
    while (cmd[index] != '\0')
    {
        int _temp_token = -1;
        if (token_top + 1 >= token_size_buf) // 토큰스택의 크기를 동적으로 할당한다.
        {
            token_size_buf *= 2;
            token_stack = (int *)realloc(token_stack, sizeof(int) * token_size_buf);
        }
        if (text_top + 1 >= text_size) // text스택의 크기를 동적으로 할당한다.
        {
            text_size *= 2;
            text = (char **)realloc(text, sizeof(char *) * text_size);
            *str_stack_size = (int *)realloc(*str_stack_size, sizeof(int) * text_size);
        }

        if(cmd[index] == '<')
        { // HTML태그가 시작되면 파싱한다.
            _temp_token = str_cmp(&cmd[index]);
            while(cmd[index] != '>' && cmd[index] != '\0')
                index++;
        }
        else 
        { // text가 시작되면 text stack에 저장한다.
            int temp_index = index;
            while(cmd[temp_index] != '<' && cmd[temp_index] != '\0')
                temp_index++;
            text[text_top] = (char *)calloc((temp_index - index) + 1, sizeof(char));
            for (int i = 0; i < temp_index - index; i++)
            {
                text[text_top][i] = cmd[index + i];
            }
            (*str_stack_size)[text_top] = temp_index - index;
            text_top++;
            index = temp_index - 1;
            _temp_token = 0;
        }

        token_stack[token_top] = _temp_token;
        token_top++;

        //printf("%d ", _temp_token);

        index++;
    }

    *token_list_size = token_top;
    *text_list_size = text_top;

    *str = text;
    return token_stack;
}

char *read_cmd()
{
    char *buffer = (char *)malloc(sizeof(char) * 4);
    int size_buf = 4, top = 0;

    char temp_;
    while (1)
    {
        scanf("%c", &temp_);
        if (temp_ == '\n')
        {
            buffer[top] = '\0';
            break;
        }
        if (top + 1 >= size_buf)
        {
            size_buf *= 2;
            buffer = (char *)realloc(buffer, size_buf * sizeof(char));
        }
        buffer[top] = temp_;
        top++;
    }
    return buffer;
}
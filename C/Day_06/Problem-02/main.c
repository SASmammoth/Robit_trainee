/*
    26.07.23.  컴퓨터정보공학부 장경민
    본 프로그램은 단순 연결리스트를 이용한 stack구현이다.

    '단순연결리스트를 이용한'이라 하였지만, 단순연결리스트의 모든 함수를 구현 하진 않고, 2번 과제에 나와있는 동작만을 수행하도록 하였다. 
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node *bottom_next;
} Node;

typedef struct _Stack
{
    Node *top;
    int size;
} Stack;

#define CMD_SIZE 15 // 명령어 입력 사이즈
#define CMD_NUM 6 + 1   // 명령어 개수

int str_cmp(char *s1, char *s2);    // 간단한 문자열 비교 함수이다. 다르면 0 같으면 1을 출력한다.
void cut_enter(char *s);            // fgets로 받아온 문자에 있는 \n을 없앤다.

int ret_cmd_index(char *cmd);       // cmdlist에서 명령어 인덱스를 반환함,

// 아래 함수들은 함수 리스트로 운영하기 위하여 모든 매개변수를 통일하였다.
int push(Stack *my_stack, int in_num);              // 정수 push
int pop(Stack *my_stack, int in_num);               // pop하고 pop된 값 출력. stack이 비어있을 시 비어있다고 출력
int size(Stack *my_stack, int in_num);              // stack 크기 출력
int top(Stack *my_stack, int in_num);               // top에 위치한 값 반환.
int isEmpty(Stack *my_stack, int in_num);           // stack에 데이터가 없으면 true, 있으면 false 반환
int printStack(Stack *my_stack, int in_num);        // stack 내 모든 값 출력. stack이 비어있을 시 비어있다고 출력

Node *get_Node(Node* prev_top, int in_num);                  // 빈 노드를 동적으로 할당한다. 다음 직전의 top을 입력으로 받는다.
int clear_Stack(Stack *my_stack);                            // 노드를 해제한다.

int main()
{
    char *cmd = (char *)malloc(sizeof(char) * CMD_SIZE);
    int (*func_list[CMD_NUM])(Stack*, int) = {push, pop, size, top, isEmpty, printStack}; // 방금 배운 함수 포인터 배열을 사용함

    // 가장 밑바닥 노드는 bottom_next가 NULL이고 -1이 저장되어 있음.
    Stack my_stack = {get_Node(NULL, -1), 0};

    printf("명령어를 입력 하시오.\n");
    printf("push <data>, pop, size, top, isEmpty, printStack, exit\n");

    while (1)
    {
        scanf("%14s", cmd);

        int in_num = -1;
        int func_return; // 함수에서 리턴된 값. 특별한 값일수도 있고 -1일수도 있다.

        // fgets(cmd, CMD_SIZE, stdin);
        // cut_enter(cmd);
        //  *cmd_list[CMD_NUM] = {"push", "pop", "size", "top", "isEmpty", "printStack", "exit"}; 참고할것

        int cmd_index = ret_cmd_index(cmd);
        if(cmd_index == 6)
            break;
        else if(cmd_index == -1)
        {
            printf("%s는 잘못된 명령어 입력 입니다\n", cmd);
            continue;
        }
        else if(cmd_index == 0) // push같이 입력이 하나 더 있는건, 입력 하나 더 받음.
            scanf("%d", &in_num);

        func_return = func_list[cmd_index](&my_stack, in_num); // 함수리스트 사용

        //printStack(&my_stack, -1);
    }

    free(cmd);
    clear_Stack(&my_stack);

    printf("\n");
    return 0;
}

int isEmpty(Stack *my_stack, int in_num)
{
    if(my_stack->size <= 0)
    {
        printf("True\n");
        return 1;
    }
    printf("False\n");
    return 0;
}
int top(Stack *my_stack, int in_num)
{
    if (my_stack->size <= 0) // 스택이 비어있을때 출력 및 리턴
    {
        printf("스택이 비어있음\n");
        return -1;
    }

    printf("top : %d\n", my_stack->top->data);
    return my_stack->top->data;
}

int size(Stack *my_stack, int in_num)
{
    printf("size : %d\n", my_stack->size); // 사이즈 출력 및 리턴
    return my_stack->size;
}

int pop(Stack *my_stack, int in_num)
{
    if(my_stack->size <= 0)
    {
        printf("스택이 비어있음\n");
        return -1;
    }

    int save_top_data = my_stack->top->data; // 임시로 top 데이터를 저장 후 출력
    printf("pop : %d\n", save_top_data);

    Node *temp_ = my_stack->top->bottom_next;   // top 할당 해제 및 top 위치 이동
    free(my_stack->top);
    my_stack->top= temp_;
    my_stack->size--;

    return save_top_data;
}

int clear_Stack(Stack *my_stack)
{
    Node *next_cur; // 커서 생성

    next_cur = my_stack->top->bottom_next;

    while (next_cur != NULL)
    {
        free(my_stack->top);
        my_stack->top = next_cur;
        next_cur = next_cur->bottom_next;
    }

    free(my_stack->top);
    return 1;
}

int push(Stack *my_stack, int in_num)
{
    Node *tmep = get_Node(my_stack->top, in_num);
    my_stack->size++;
    my_stack->top = tmep;

    return 1;
}

int printStack(Stack *my_stack, int in_num)
{
    if(my_stack->size <= 0)
    {
        printf("stack이 비어있음\n");
        return 0;
    }
    Node *cur = my_stack->top; // 커서 생성

    while (cur->bottom_next != NULL)
    {
        printf("%d\n", cur->data);
        cur = cur->bottom_next;
    }

    return 1;
}

Node *get_Node(Node *prev_top, int in_num)
{
    Node *temp_ = (Node *)malloc(sizeof(Node));
    temp_->bottom_next = prev_top;
    temp_->data = in_num;
    return temp_;
}

int ret_cmd_index(char *cmd)
{
    const char *cmd_list[CMD_NUM] = {"push", "pop", "size", "top", "isEmpty", "printStack", "exit"}; // 명령어 리스트를 선언함.

    for (int i = 0; i < CMD_NUM; i++)
        if (str_cmp(cmd, cmd_list[i]))
            return i;

    return -1;
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

int str_cmp(char *s1, char *s2)
{
    for (; *s1 == *s2; s1++,s2++)
    {
        if(*s1 == '\0')
            return 1;
    }
    return 0;
}
/*
    26.07.23.  컴퓨터정보공학부 장경민
    본 프로그램은 단순 연결 리스트를 이용한 Queue 구현이다.

    과제 2에서 몇가지 요소를 가져와서 큐에 맞게 수정하였다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

typedef struct _Queue
{
    Node *front_;
    Node *rear_;
    int size;
} Queue;

#define CMD_SIZE 15   // 명령어 입력 사이즈
#define CMD_NUM 7 + 1 // 명령어 개수

int str_cmp(char *s1, char *s2); // 간단한 문자열 비교 함수이다. 다르면 0 같으면 1을 출력한다.
void cut_enter(char *s);         // fgets로 받아온 문자에 있는 \n을 없앤다.

int ret_cmd_index(char *cmd); // cmdlist에서 명령어 인덱스를 반환함,

// 아래 함수들은 함수 리스트로 운영하기 위하여 모든 매개변수를 통일하였다.
int Enqueue(Queue *my_queue, int in_num);    // 정수 Enqueue
int Dequeue(Queue *my_queue, int in_num);    // Dequeue하고 Dequeue된 값 출력. stack이 비어있을 시 비어있다고 출력
int size(Queue *my_queue, int in_num);       // stack 크기 출력
int front(Queue *my_queue, int in_num);      // front에 위치한 값 반환.
int rear(Queue *my_queue, int in_num);       // rear에 위치한 값 반환.
int isEmpty(Queue *my_queue, int in_num);    // stack에 데이터가 없으면 true, 있으면 false 반환
int printQueue(Queue *my_queue, int in_num); // stack 내 모든 값 출력. stack이 비어있을 시 비어있다고 출력

Node *get_Node(Node *prev_front, int in_num); // 빈 노드를 동적으로 할당한다. 다음 직전의 front을 입력으로 받는다.
int clear_Queue(Queue *my_queue);             // 노드를 해제한다.

int main()
{
    char *cmd = (char *)malloc(sizeof(char) * CMD_SIZE);
    int (*func_list[CMD_NUM])(Queue *, int) = {Enqueue, Dequeue, size, front, rear, isEmpty, printQueue}; // 방금 배운 함수 포인터 배열을 사용함

    // 가장 밑바닥 노드는 buttem_next가 NULL이고 -1이 저장되어 있음.
    Queue my_queue = {NULL, NULL, 0};

    printf("명령어를 입력 하시오.\n");
    printf("Enqueue <data>, Dequeue, size, front, rear, isEmpty, printQueue, exit\n");

    while (1)
    {
        scanf("%14s", cmd);

        int in_num = -1;
        int func_return; // 함수에서 리턴된 값. 특별한 값일수도 있고 -1일수도 있다.

        //  *cmd_list[CMD_NUM] = {"Enqueue", "Dequeue", "size", "front", "rear",  "isEmpty", "printQueue", "exit"}; 참고할것

        int cmd_index = ret_cmd_index(cmd);
        if (cmd_index == 7)
            break;
        else if (cmd_index == -1)
        {
            printf("%s는 잘못된 명령어 입력 입니다\n", cmd);
            continue;
        }
        else if (cmd_index == 0) // Enqueue같이 입력이 하나 더 있는건, 입력 하나 더 받음.
            scanf("%d", &in_num);

        func_return = func_list[cmd_index](&my_queue, in_num); // 함수리스트 사용

        // printQueue(&my_queue, -1);
    }

    free(cmd);
    clear_Queue(&my_queue);

    printf("\n");
    return 0;
}

int isEmpty(Queue *my_queue, int in_num)
{
    if (my_queue->size <= 0)
    {
        printf("True\n");
        return 1;
    }
    printf("False\n");
    return 0;
}

int rear(Queue *my_queue, int in_num)
{
    if (my_queue->size <= 0) // 스택이 비어있을때 출력 및 리턴
    {
        printf("스택이 비어있음\n");
        return -1;
    }

    printf("rear : %d\n", my_queue->rear_->data);
    return my_queue->rear_->data;
}

int front(Queue *my_queue, int in_num)
{
    if (my_queue->size <= 0) // 스택이 비어있을때 출력 및 리턴
    {
        printf("스택이 비어있음\n");
        return -1;
    }

    printf("front : %d\n", my_queue->front_->data);
    return my_queue->front_->data;
}

int size(Queue *my_queue, int in_num)
{
    printf("size : %d\n", my_queue->size); // 사이즈 출력 및 리턴
    return my_queue->size;
}

int Dequeue(Queue *my_queue, int in_num)
{
    if (my_queue->size <= 0)
    {
        printf("queue가 비어있음\n");
        return 0;
    }

    Node *temp = my_queue->front_;
    int re_data = temp->data;
    my_queue->front_ = my_queue->front_->next;
    free(temp);
    printf("Dequeu : %d\n", re_data);
    my_queue->size--;
    return re_data;
}

int clear_Queue(Queue *my_queue)
{
    for (int i = 0; i < my_queue->size; i++)
    {
        Node *temp = my_queue->front_->next;
        free(my_queue->front_);
        my_queue->front_ = temp;
    }
    return 0;
}

int Enqueue(Queue *my_queue, int in_num)
{
    // printf("enq : %d", in_num);
    if (my_queue->size == 0)
    {
        Node *temp = get_Node(NULL, in_num);
        my_queue->front_ = temp;
        my_queue->rear_ = temp;
        my_queue->size++;
    }
    else
    {
        Node *temp = get_Node(NULL, in_num);
        my_queue->rear_->next = temp;
        my_queue->rear_ = temp;
        my_queue->size++;
    }

    return 1;
}

int printQueue(Queue *my_queue, int in_num)
{
    if (my_queue->size <= 0)
    {
        printf("stack이 비어있음\n");
        return 0;
    }

    Node *cur = my_queue->front_;

    while (cur != NULL)
    {
        printf("%d\n", cur->data);
        cur = cur->next;
    }


    return 0;
}

Node *get_Node(Node *next_, int in_num)
{
    Node *temp_ = (Node *)malloc(sizeof(Node));
    temp_->next = next_;
    temp_->data = in_num;
    return temp_;
}

int ret_cmd_index(char *cmd)
{
    const char *cmd_list[CMD_NUM] = {"Enqueue", "Dequeue", "size", "front", "rear",
                                            "isEmpty",
                                            "printQueue", "exit"}; // 명령어 리스트를 선언함.

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
    for (; *s1 == *s2; s1++, s2++)
    {
        if (*s1 == '\0')
            return 1;
    }
    return 0;
}
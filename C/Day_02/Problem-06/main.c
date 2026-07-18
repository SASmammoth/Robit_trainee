/*
    26.07.16  컴퓨터정보공학부 장경민
    본 프로그램은 집합관련 명령어를 입력받아 집합을 관리하는 프로그램이다.
    프로그램이 워낙 복잡하여 설명은 주석으로 대체하였다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>


#define MAX_CMD_SIZE 10     // 최대 명령어 길이
#define CMD_LIST_SIZE_2nd 4 // X의 입력 가능함 명령어의 개수
#define CMD_LIST_SIZE_ALL 6 // 모든 명령어 개수

#define MAX_SET_SIZE 20 // 집합의 크기이다

void set_maniger(int my_set[], int cmd_type_flag, int cmd_2nd_flag, int X); // 배열과 명령어플래그들, 정수 X를 받아서 집합을 관리하는 함수이다.
int is_str_cmd_2nd(char cmd_[]);                                            // X의 입력 여부를 확인하는 함수. x가 가능하면 1, 아니면 0을 출력한다.
int is_cmd(char cmd_[]);                                                    // 명령어 여부와 명령어의 종류를 리턴한다. 명령어 라면 명령어 리스트의 인덱스를 리턴하고 명령어가 아니면 -1을 리턴한다.
void clear_cmd(char cmd_[]);                                                // cmd 문자열을 깨끗이 정리한다.

int is_X_in_set(const int my_set[], int X);     // 집합에서 X가 존재하는지 확인하는 함수이다. 있으면 인덱스를 없으면 -1을 반환한다.
void print_set(const int my_set[]);             // 집합을 출력한다.
void _push_front_set(int my_set[]);             // 집합에 생긴 구멍을 매꾼다.
int find_last_index(int my_set[]);              // 집합의 마지막 위치를 출력한다. 집합이 꽉 찼다면 -1을 출력한다.

void swap(int my_set[], int id1, int id2); // 집합과 인덱스 2개를 받아서 서로 위치를 바꾸는 부분이다.

// 집합과 관현된 함수이다.
int add_set(int my_set[], int X);       // S에 x를 추가한다. (1 ≤ x ≤ 20) S에 x가 이미 있는 경우에는 연산을 무시한다. 정상적으로 추가 되었으면 1 아니면 0을 반환한다.
int remove_set(int my_set[], int X);    // S에서 x를 제거한다. (1 ≤ x ≤ 20) S에 x가 없는 경우에는 연산을 무시한다. 정상적으로 제거 되었으면 1 아니면 0을 반환한다.
void check_set(int my_set[], int X);    // S에 x가 있으면 1을, 없으면 0을 출력한다.
void toggle_set(int my_set[], int X);   // S에 x가 있으면 x를 제거하고, 없으면 x를 추가한다. (1 ≤ x ≤ 20)
void all_set(int my_set[]);             // S를 {1, 2, ..., 20} 으로 바꾼다.
void empty_set(int my_set[]);           // 집합을 공집합으로 만든다.

int main()
{
    printf("연산을 선택하세요. (1 <= x <= %d)\n", MAX_SET_SIZE); // 기본 프롬프트를 출력하는 부분이다.
    printf("add X\n");
    printf("remove X\n");
    printf("check X\n");
    printf("toggle X\n");
    printf("all 0\n");
    printf("empty 0\n");

    char cmd[MAX_CMD_SIZE]; //사용자가 입력하는 명령어를 저장하는 곳이다.

    int my_set[MAX_SET_SIZE]; // 집합이다. 집합의 요소는 숫자를 저장하고, -1은 집합의 빈 부분을 의미한다.
    int X = -1;

    empty_set(my_set); // 집합을 초기화 한다.

    while (1)
    {
        _push_front_set(my_set);

        clear_cmd(cmd);
        printf("input : ");
        scanf("%s %d", cmd, &X);

        set_maniger(my_set, is_cmd(cmd), is_str_cmd_2nd(cmd), X);
    }
}



int add_set(int my_set[], int X)
{
    // S에 x를 추가한다. (1 ≤ x ≤ 20) S에 x가 이미 있는 경우에는 연산을 무시한다. 정상적으로 추가 되었으면 1 아니면 0을 반환한다.
    if (is_X_in_set(my_set, X) != -1) // 집합에 숫자가 있으면 0을 반환
        return 0;

    int index_X = find_last_index(my_set); // X가 들어갈 위치를 찾는다.
    if(index_X != -1)
    {
        my_set[index_X] = X;
        return 1;
    }
    return 0;
}

int remove_set(int my_set[], int X)
{
    //S에서 x를 제거한다.(1 ≤ x ≤ 20)S에 x가 없는 경우에는 연산을 무시한다.정상적으로 제거 되었으면 1 아니면 0을 반환한다.
    int index_X = is_X_in_set(my_set, X);
    if (index_X == -1) // 집합에 숫자가 없으면 0을 반환
        return 0;

    my_set[index_X] = -1;
    _push_front_set(my_set); //요소를 제거하고 배열의 구멍을 매꾼다.
    return 1;
}

void check_set(int my_set[], int X)
{
    // S에 x가 있으면 1을, 없으면 0을 출력한다.
    if (is_X_in_set(my_set, X) == -1)
        printf("0 ");
    else
        printf("1 ");
}

void toggle_set(int my_set[], int X)
{
    // S에 x가 있으면 x를 제거하고, 없으면 x를 추가한다. (1 ≤ x ≤ 20)
    if (add_set(my_set, X)) 
        return; // addset결과를 확인하여 추가됬으면 함수를 종료한다.

    remove_set(my_set, X);
    return;
}

void all_set(int my_set[])
{
    // S를 {1, 2, ..., 20} 으로 바꾼다.
    for (int i = 0; i < MAX_SET_SIZE; i++)
        my_set[i] = i + 1;
    return;
}

void _push_front_set(int my_set[])
{
    // 집합에 생긴 구멍을 매꾼다.
    for (int i1 = 0; i1 < MAX_SET_SIZE - 1; i1++) // 집합에 구멍이 있으면 한칸 뒤의 숫자와 위치를 바꾼다.
    {
        for (int i2 = 0; i2 <= i1; i2++)
            if (my_set[i2] == -1) swap(my_set, i2, i2 + 1);
    }
}

void swap(int my_set[], int id1, int id2)
{
    //배열의 요소를 swap한다.
    int temp_ = my_set[id1];
    my_set[id1] = my_set[id2];
    my_set[id2] = temp_;
}

int find_last_index(int my_set[])
{
    // 집합의 마지막 위치를 출력한다. 집합이 꽉 찼다면 -1을 출력한다.
    for (int i = 0; i < MAX_SET_SIZE; i++)
    if(my_set[i] == -1)
        return i;
    return -1; // 이 함수를 바로 set 인덱스에 넣으면 문제가 생길수 있음 
}

void empty_set(int my_set[])
{
    // 집합을 공집합으로 만든다.
    for (int i = 0; i < MAX_SET_SIZE; i++)
        my_set[i] = -1;
}

void print_set(const int my_set[])
{
    // 집합을 출력한다.
    printf("집합 : {");
    for (int i = 0; i < MAX_SET_SIZE; i++)
        if (my_set[i] != -1)
            printf(" %d, ", my_set[i]);
    printf(" }\n");
}

void clear_cmd(char cmd_[])
{
    // cmd 문자열을 깨끗이 정리한다.
    for (int i = 0; i < MAX_CMD_SIZE; i++)
        cmd_[i] = '\0';
}

int is_cmd(char cmd_[])
{
    // 명령어 여부와 명령어의 종류를 리턴한다. 명령어 라면 명령어 리스트의 인덱스를 리턴하고 명령어가 아니면 -1을 리턴한다. 
    // printf("is_cmd cmd_: %s\n", cmd_);
    char cmd_list_all[CMD_LIST_SIZE_ALL][MAX_CMD_SIZE] = {
        "add",
        "remove",
        "check",
        "toggle",
        "all",
        "empty"}; // 모든 명령어들의 리스트
    int flag_cmd_all_list[CMD_LIST_SIZE_ALL] = {
        0,
    }; // 모든 명령어들의 플래그

    for (int i1 = 0; i1 < MAX_CMD_SIZE; i1++) // 명령어 단어 확인하여 플래그에 기록한다.
    {
        for (int i2 = 0; i2 < CMD_LIST_SIZE_ALL; i2++)
        {
            if (cmd_list_all[i2][i1] != cmd_[i1])
                flag_cmd_all_list[i2] = 1;
            //printf("%c : %c  flag=%d\n", cmd_list_all[i2][i1], cmd_[i1], flag_cmd_all_list[i2]);
                }
        //printf("\n\n");
    }

    for (int i = 0; i < CMD_LIST_SIZE_ALL; i++) // 플래그를 확인하여 플래그를 반환, 잘못된 입력은 error 리턴
        if (!flag_cmd_all_list[i])
            return i;

    return -1;
}

int is_str_cmd_2nd(char cmd_[])
{
    // X의 입력 여부를 확인하는 함수. x가 가능하면 1, 아니면 0을 출력한다.
    char cmd_list_2nd[CMD_LIST_SIZE_2nd][MAX_CMD_SIZE] = {"add", "remove", "check", "toggle"}; // X가 올수있는 명령어들의 리스트
    int flag_cmd_2nd_list[CMD_LIST_SIZE_2nd] = {0, }; // X가 올수있는 명령어들의 플래그

    for (int i1 = 0; i1 < MAX_CMD_SIZE; i1++) // X가 올수있는 명령어 확인. 플래그에 기록한다.
    {
        if (cmd_[i1] == '\0') break;

        for (int i2 = 0; i2 < CMD_LIST_SIZE_2nd; i2++)
            if(cmd_list_2nd[i2][i1] != cmd_[i1]) 
                flag_cmd_2nd_list[i2] = 1;
    }

    for (int i = 0; i < CMD_LIST_SIZE_2nd; i++) // 플래그를 이용해 X가 올수있는 명령어는 1을 리턴한다.
        if (!flag_cmd_2nd_list[i]) return 1;

    return 0; // X가 올수 없는 명령어는 0을 리턴한다.
}

int is_X_in_set(const int my_set[], int X)
{
    // 집합에서 X가 존재하는지 확인하는 함수이다. 있으면 인덱스를 없으면 -1을 반환한다.
    for (int i = 0; i < MAX_SET_SIZE; i++)
        if(my_set[i] == X)
            return i;

    return -1;
}

void set_maniger(int my_set[], int cmd_type_flag, int cmd_2nd_flag, int X)
{
    // 배열과 명령어플래그들, 정수 X를 받아서 집합을 관리하는 함수이다.
    if(cmd_2nd_flag) // X를 입력 받는 명령어일때 1 <= X <=20 인지 확인함
    {
        if (!(1 <= X && X <= MAX_SET_SIZE))
        {
            printf("X는 [1:%d]인 숫자여야 합니다.\n", MAX_SET_SIZE);
            return;
        }
    }
    else // 0를 입력 받는 명령어일때 0인지 확인함
    {
        //printf("X : %d\n", X);
        if (X != 0)
        {
            printf("숫자 0이 필요합니다.\n");
            return;
        }
    }

    switch (cmd_type_flag) // 명령어 플래그를 이용해서 명령어를 실행한다.
    {
    case 0:
        add_set(my_set, X);
        print_set(my_set);
        break;
    case 1:
        remove_set(my_set, X);
        print_set(my_set);
        break;
    case 2:
        check_set(my_set, X);
        print_set(my_set);
        break;
    case 3:
        toggle_set(my_set, X);
        print_set(my_set);
        break;
    case 4:
        all_set(my_set);
        print_set(my_set);
        break;
    case 5:
        empty_set(my_set);
        print_set(my_set);
        break;
    default:
        printf("명령어가 존재하지 않습니다.\n");
        break;
    }
}

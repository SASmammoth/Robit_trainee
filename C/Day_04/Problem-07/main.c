/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 단순 연결리스트의 여러가지 함수를 구현하는 코드이다.

    배열에 링크드리스트 요소를 넣고 추가, 제거를 구현하였다.
    만약 새로운 노드가 추가될때, get_free_node함수를 이용하여 텅 빈 링크드 리스트 요소가 있으면 거기에 넣도록 하였다.

    추가 및 제거는 index, first버전만 직접적인 작용을 하고 나머지 버전은 index 버전의 명령어에 인자를 전달하도록 하게끔 하였다.

    데이터로 추가/제거 할때 같은 데이터가 2개 이상 있으면 앞에 값만 영향을 받을수 있음.

    구현이므로 사용자가 명령어를 입력받는 대신 코드에서 명령어를 시연하는 형식으로 하였다.
    명령어 형식은 다음과 같다.
        q                   종료 코드
        f <data>            맨 앞에 데이터 추가
        I <index> <data>    위치에 데이터 추가
        i <data> <data2>    데이타 위치에 data2 추가
        b <data>            데이타 맨 뒤에 추가
        F                   맨 앞 데이터 삭제
        D <index>           인덱스 위치 삭제
        d <data>            데이터 삭제
        g <data>            데이터를 넣으면 인덱스를 찾아줌
        G <index>           인덱스를 넣으면 데이터를 찾아줌
        B                   맨 뒤에 삭제
        r                   리스트 역순으로 만듦
        p                   리스트 프린트

        예시)f 5
            I 0 8
            d 3
            ...

    도저히 동적할당으로 할 수 없어서 SIZE를 정의하였다.
    출력 키가 따로 있지만, 보기 더 쉬우라고 입력이 될때마다 출력함.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

#define SIZE_LIST 100

typedef struct _Node
{
    int is_valid;
    int data;
    struct _Node *next;
}Node;

typedef struct _LinkedList
{
    Node *head;
    Node *tail;
    Node *cur;
    int size;
} LinkedList;

typedef struct _Linked_List_Basket
{
    Node Basket[SIZE_LIST];
    int size;
} LLB;

int insert_index(LLB *basket, LinkedList *mylinkedlist, int index, int insert_data);        // 인덱스를 이용한 삽입
int insert_data(LLB *basket, LinkedList *mylinkedlist, int find_data, int insert_data);   // 데이터를 이용한 삽입.
Node *get_free_node(LLB *basket);                                                        // 노드를 저장하는 동적 리스트에서 빈 노드의 주소를 반환함
void make_null_node(LLB *basket, int p1, int p2);                                        // 노드 바구니에서 p1 - p2의 요소들을 무효화 시킴. 초기화 or delet 됬을때 필요함.
int insert_first(LLB *basket, LinkedList *mylinkedlist, int insert_data);                 // 링크드리스트 맨 처음에 추가
void print_list(LinkedList *mylinkedlist);                                       // 링크드 리스트를 출력한다.
int insert_back(LLB *basket, LinkedList *mylinkedlist, int insert_data);            // 리스트 마지막에 추가한다.

int delet_index(LLB *basket, LinkedList *mylinkedlist, int find_index); // 인덱스를 이용한 제거
int delet_first(LLB *basket, LinkedList *mylinkedlist);                 // 첫번째 인덱스 제거
int delet_data(LLB *basket, LinkedList *mylinkedlist, int find_data); // 데이터를 이용한 제거
int delet_back(LLB *basket, LinkedList *mylinkedlist); // 마지막 제거

int get_entry_data(LLB *basket, LinkedList *mylinkedlist, int find_data); // 데이타로 요소 찾기 (index 반환). 없으면 -1 리턴
int get_entry_index(LLB *basket, LinkedList *mylinkedlist, int find_index); // 인덱스로 요소 찾기 (data 반환). 없으면 -999999리턴, 이런 데이타가 있을수 있지만 딱히 문제에 없을시에 어떻게 해라고 명시를 안해놔서 그냥 사용함.

int reverse(LLB *basket, LinkedList *mylinkedlist);                     // 리스트를 뒤집는다.

int main()
{
    LLB basket_maniger;
    basket_maniger.size = SIZE_LIST;
    make_null_node(&basket_maniger, 0, basket_maniger.size);
    LinkedList mylinkedlist = {basket_maniger.Basket, basket_maniger.Basket, basket_maniger.Basket, 0};

    basket_maniger.Basket[0].is_valid = 1;
    basket_maniger.Basket[0].next = NULL;

    char temp_cmd;
    int temp_data, temp_index, temp_find_index;
    int end_ = 0; // 무한반복을 종료하는 코드

    printf("명령어는 주석을 확인하시오.\n");
    while (1)
    {

        scanf("%c", &temp_cmd);
        switch (temp_cmd)
        {
        case 'q': // 종료하는 코드
            end_ = 1;
            break;
        case 'f':
            scanf("%d", &temp_data);
            insert_first(&basket_maniger, &mylinkedlist, temp_data);
            break;
        case 'I':
            scanf("%d %d", &temp_index, &temp_data);
            insert_index(&basket_maniger, &mylinkedlist, temp_index, temp_data);
            break;
        case 'i':
            scanf("%d %d", &temp_find_index, &temp_data);
            insert_data(&basket_maniger, &mylinkedlist, temp_find_index, temp_data);
            break;
        case 'b':
            scanf("%d", &temp_data);
            insert_back(&basket_maniger, &mylinkedlist, temp_data);
            break;
        case 'F':
            delet_first(&basket_maniger, &mylinkedlist);
            break;
        case 'D':
            scanf("%d", &temp_index);
            delet_index(&basket_maniger, &mylinkedlist, temp_index);
            break;
        case 'd':
            scanf("%d", &temp_data);
            delet_data(&basket_maniger, &mylinkedlist, temp_data);
            break;
        case 'g':
            scanf("%d", &temp_data);
            printf("찾는 %d의 인덱스는 : %d\n", temp_data, get_entry_data(&basket_maniger, &mylinkedlist, temp_data));
            break;
        case 'G':
            scanf("%d", &temp_index);
            printf("찾는 %d의 데이타는 : %d\n", temp_index, get_entry_index(&basket_maniger, &mylinkedlist, temp_index));
            break;
        case 'B':
            delet_back(&basket_maniger, &mylinkedlist);
            break;
        case 'r':
            reverse(&basket_maniger, &mylinkedlist);
            break;
        case 'p':
            printf("리스트를 출력합니다 : ");
            print_list(&mylinkedlist);
            break;
        default:
            break;
        }

        if(end_)
            break;

        if (basket_maniger.size * 0.95 <= mylinkedlist.size)
        {
            printf("바구니가 거의 다 찼습니다.\n프로그램이 종료 됩니다.");
            break;
        }

        print_list(&mylinkedlist); // 왜인지는 모르겠는데, 출력이 2번씩 반복됨
    }

    printf("\n");
    return 0;
}

int reverse(LLB *basket, LinkedList *mylinkedlist)
{   // 문제가 있을수도 있음
    Node *prev = mylinkedlist->tail;
    Node *now = mylinkedlist->head;
    

    for (int i = 0; i < mylinkedlist->size; i++) // 2개의 노드와 미리보기가 한칸씩 이동하며 방향을 바꾼다.
    {
        Node *next = now->next;
        now->next = prev;
        prev = now;
        now = next;
    }

    mylinkedlist->head = prev;
    return 1;
}

int get_entry_data(LLB *basket, LinkedList *mylinkedlist, int find_data)
{
    mylinkedlist->cur = mylinkedlist->head; // 커서 초기화
    for (int i = 0; i < mylinkedlist->size; i++) // 반복하여 데이터 위치 찾음.
    {
        if(mylinkedlist->cur->data == find_data)
            return i;
        mylinkedlist->cur = mylinkedlist->cur->next;
    }
    printf("그런 데이터는 없는거 같습니다.\n");
    return -1; // 없으면 -1 리턴
}

int get_entry_index(LLB *basket, LinkedList *mylinkedlist, int find_index)
{
    mylinkedlist->cur = mylinkedlist->head;      // 커서 초기화
    if (find_index < 0 || find_index >= mylinkedlist->size)
    {
        printf("인덱스 %d는 아직 존재하지 않습니다.\n", find_index);
        return -9999999;
    }

    for (int i = 0; i < find_index; i++)
    {
        mylinkedlist->cur = mylinkedlist->cur->next;
    }
    return mylinkedlist->cur->data;
}

int delet_back(LLB *basket, LinkedList *mylinkedlist)
{
    // 링크드리스트 사이즈를 이용하여 제거한다.
    delet_index(basket, mylinkedlist, mylinkedlist->size - 1);
}

int delet_data(LLB *basket, LinkedList *mylinkedlist, int find_data)
{
    mylinkedlist->cur = mylinkedlist->head; // 커서 초기화

    int is_valid = -1; // 값이 없으면 -1, 있으면 그 위치의 인덱스를 가리킨다.

    for (int i = 0; i < mylinkedlist->size; i++)
    {
        if (mylinkedlist->cur->data == find_data)
        {
            is_valid = i;
            break;
        }
        mylinkedlist->cur = mylinkedlist->cur->next;
    }

    if (is_valid == -1) // 데이터가 없으면
    {
        printf("데이터 %d를 찾을 수 없습니다.", find_data);
        return -1;
    }

    delet_index(basket, mylinkedlist, is_valid); // 데이터가 있으면 그 인덱스를 이용해서 제거한다.

    return 1;
}

int delet_first(LLB *basket, LinkedList *mylinkedlist)
{
    if(mylinkedlist->size > 0)
    {
        mylinkedlist->head->is_valid = 0;
        mylinkedlist->size--;
        mylinkedlist->head = mylinkedlist->head->next;

        return 1;
    }
    else
    {
        printf("리스트의 요소가 없어 제거할수 없음.\n");
        return -1;
    }
}

int delet_index(LLB *basket, LinkedList *mylinkedlist, int find_index)
{
    mylinkedlist->cur = mylinkedlist->head;                // 커서 초기화
    if (find_index < 0 || find_index >= mylinkedlist->size)
    {
        printf("인덱스 %d는 아직 존재하지 않습니다.\n", find_index);
        return -1;
    }

    if (find_index == 0)
    {
        delet_first(basket, mylinkedlist);
        return 1;
    }

    for (int i = 0; i < find_index - 1; i++) // 반복하여 데이터 위치 찾음.
        mylinkedlist->cur = mylinkedlist->cur->next;

    Node *temp_node = mylinkedlist->cur->next; // 임시 노드로 주소를 저장한 뒤 앞뒤에걸 붙임
    mylinkedlist->cur->next = mylinkedlist->cur->next->next;
    temp_node->is_valid = 0; // 노드 할당해제
    mylinkedlist->size--;

    return 1;
}

int insert_back(LLB *basket, LinkedList *mylinkedlist, int insert_data)
{
    // 링크드리스트 사이즈를 이용하여 추가한다.
    insert_index(basket, mylinkedlist, mylinkedlist->size, insert_data);
}

int insert_data(LLB *basket, LinkedList *mylinkedlist, int find_data, int insert_data)
{
    mylinkedlist->cur = mylinkedlist->head; // 커서 초기화

    int is_valid = -1; // 값이 없으면 -1, 있으면 그 위치의 인덱스를 가리킨다.

    for (int i = 0; i < mylinkedlist->size; i++)
    {
        if(mylinkedlist->cur->data == find_data)
        {
            is_valid = i;
            break;
        }
        mylinkedlist->cur = mylinkedlist->cur->next;
    }

    if(is_valid == -1) // 데이터가 없으면
    {
        printf("데이터 %d를 찾을 수 없습니다.", find_data);
        return -1;
    }

    insert_index(basket, mylinkedlist, is_valid + 1, insert_data); // 데이터가 있으면 그 인덱스를 이용해서 추가한다.

    return 1;
}

int insert_index(LLB *basket, LinkedList *mylinkedlist, int find_index, int insert_data)
{
    mylinkedlist->cur = mylinkedlist->head; // 커서 초기화
    if (find_index < 0 || find_index > mylinkedlist->size)
    {
        printf("인덱스 %d는 아직 존재하지 않습니다.\n", find_index);
        return -1;
    }

    if (find_index == 0)
    {
        insert_first(basket, mylinkedlist, insert_data);
        return 1;
    }

    for (int i = 0; i < find_index - 1; i++) // 반복하여 데이터 위치 찾음.
        mylinkedlist->cur = mylinkedlist->cur->next;

    Node *temp_node = get_free_node(basket);   // 노드 바구니에서 빈 노드를 가져옴
    temp_node->data = insert_data;
    temp_node->next = mylinkedlist->cur->next;
    mylinkedlist->cur->next = temp_node;

    mylinkedlist->size++;

    return 1;
}

int insert_first(LLB *basket, LinkedList *mylinkedlist, int insert_data)
{
    Node *temp_node = get_free_node(basket);

    temp_node->data = insert_data;
    temp_node->next = mylinkedlist->head;
    mylinkedlist->head = temp_node;
    mylinkedlist->size++;

    return 1;
}

void print_list(LinkedList *mylinkedlist)
{
    mylinkedlist->cur = mylinkedlist->head;

    while (mylinkedlist->cur != mylinkedlist->tail)
    {
        printf("%d -> ", mylinkedlist->cur->data);
        mylinkedlist->cur = mylinkedlist->cur->next;
    }
    printf("\n");
}

void make_null_node(LLB *basket, int p1, int p2)
{
    for (int i = p1; i < p2; i++)
    {
        basket->Basket[i].is_valid = 0;
    }
}

Node *get_free_node(LLB *basket)
{
    for (int i = 0; i < basket->size; i++)
    {
        if (basket->Basket[i].is_valid == 0)
        {
            basket->Basket[i].is_valid = 1;
            return &basket->Basket[i];
        }
    }
    return NULL;
}
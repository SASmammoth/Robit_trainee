/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 1.구매할 물품과 금액을 입력 받고 2.물건 1개를 입력하면 3.물건의 금액의 합계를 출력한다.

    물건 이름과 합계금액을 구조체로 생성하고, 새로운 품목이 들어돌때만 동적할당으로 배열에 추가함
    이렇게 하면 메모리를 최소한으로 사용할 수 있음.

    품목명은 20자 미만으로 해야됨. 안그러면 오류가 생길수 있음.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

typedef struct _product
{
    char name[20];
    int price_sum;
} Product;

int input_product(Product **list_product, int N);           // 사용자로 부터 물건을 입력 받는 부분. 물건 리스트의 크기를 리턴한다.
void pirnt_product(Product *list_product, int N);           // 물건 리스트를 출력하는 코드

void pirnt_product_finder(Product *list_product, int N);    // 물건을 검색하여 가격을 출력한다.

void cpy_str(char *copyer, char *original, int len);           // 문자열을 복사하는 함수이다.
int str_cmp(char *s1, char *s2, int n);                        // 문자열을 비교하는 함수이다. 같으면 1을 반환한다.

int main()
{
    int N;
    scanf("%d", &N);

    Product *list = (Product *)malloc(sizeof(Product)*2);


    int lists_size = input_product(&list, N);

    //pirnt_product(list, lists_size);
    pirnt_product_finder(list, lists_size);

    free(list);
}

void pirnt_product_finder(Product *list_product, int N)
{
    char name_[20];
    scanf("%s", name_);

    //int is_exist = 0;
    for (int i = 0; i < N; i++)
    {
        if(str_cmp(name_, list_product[i].name, 20))
        {
            printf("출력 : %d\n", list_product[i].price_sum);
            return;
        }
    }

    printf("출력 : 0\n");
}

void pirnt_product(Product *list_product, int N)
{
    for (int i = 0; i < N; i++)
    {
        //printf("print i : %d", i);
        printf("%s : %d\n", list_product[i].name, list_product[i].price_sum);
    }
}

int input_product(Product **list_product, int N)
{
    int top = 0;
    char _name[20];
    int _price;

    int count = 0;
    while (count < N)
    {
        scanf("%s %d", _name, &_price);
        //printf("count : %d, top : %d\n", count, top);
        if (_price <= 0) // 사용자 입력을 확인함
        {
            printf("가격은 0보다 켜야 함,\n");
            continue;
        }

        int is_same = 0; // 같은 이름이면 건너 뛰는 플래그
        for (int i = 0; i < top; i++) // 만약 같은 이름이 존재한다면, 합계를 저장.
        {
            if (str_cmp((*list_product)[i].name, _name, 20))
            {
                (*list_product)[i].price_sum += _price;
                count++;
                is_same = 1;
                break;
            }
        }
        if(is_same)
            continue;

        // 같은 이름이 존재하지 않는다면 list_product를 한칸 늘리고 가격을 저장.
        (*list_product)[top].price_sum = _price;
        cpy_str((*list_product)[top].name, _name, 20);
        top++;
        *list_product = (Product *)realloc(*list_product, sizeof(Product) * (top + 1));
        count++;
    }

    return top;
}

int str_cmp(char *s1, char *s2, int n)
{
    int i = 0;
    int tf_ = 1;
    while (i < n)
    {
        if (s1[i] == '\0' && s2[i] == '\0')
            break;
        else if ((s1[i] == '\0' && s2[i] != '\0') || (s1[i] != '\0' && s2[i] == '\0'))
        {
            tf_ = 0;
            break;
        }

        if (s1[i] != s2[i])
        {
            tf_ = 0;
            break;
        }
        i++;
    }
    return tf_;
}

void cpy_str(char *copyer, char *original, int len)
{
    for (int i = 0; i < len; i++)
        copyer[i] = original[i];
}
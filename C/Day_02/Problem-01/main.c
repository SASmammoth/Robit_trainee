/*
    26.07.16 11:22 컴퓨터정보공학부 장경민

    본 프로그램은 여러 종류의 별찍기 타입과 사이즈를 입력받아 switch문과 함수로 출력하는 코드이다.
    과제의 예시에서는 전부 홀수출력만이 나와있다. 저 모양들의 별찍기를 짝수로 출력하면 삼각형이 약간 찌그러지지만, 딱히 설명이 없어서 짝수도 출력하게끔 만들었다.
    모든 별 찍기는 i1과 i2의 비교를 이용해 알맞은 위치에 별을 찍는다.
    
    (수정) : 차후에 과제1번은 모두 홀수로 하면 된다 하였지만 이미 만들어 짝수를 만들어 놓았고, 정수는 홀수를 포함하기 때문에 지우지 않고 놔두어 놓았다.
*/

#define _CRT_SECURE_NO_WARNINGS //VS용 선언
#include <stdio.h>

// 1 ~ 4번 종류의 별찍기 출력 함수이다.
void print_type1(int len); 
void print_type2(int len);
void print_type3(int len);
void print_type4(int len);

int main()
{
    int len = 0, type_ = 0;
    printf("사이즈와 종류를 입력하시오.");
    scanf("%d %d", &len, &type_);

    if (len > 0) // 비 정상적인 입력을 걸러내는 코드
    {
        switch (type_)
        {
        case 1:
            print_type1(len);
            break;
        case 2:
            print_type2(len);
            break;
        case 3:
            print_type3(len);
            break;
        case 4:
            print_type4(len);
            break;
        default:
            printf("종류는 오직 1~4 만이 존재합니다.\n");
            break;
        }
    }
    else
        printf("길이는 양의 정수 만이 올 수 있습니다.\n");

    return 0;
}

void print_type1(int len)
{
    for (int i1 = 0; i1 < len; i1++)
    {
        for (int i2 = 0; i2 < len; i2++)
        {
            if (i1 >= i2 && len - i2 > i1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void print_type2(int len)
{
    if(len % 2 == 1)
    {   // 홀수 에서는 이 코드가 제대로 동작하지만, 짝수에서는 이 코드가 우측으로 1칸 이동하여 나와서 짝수/홀수 케이스를 나누어 진행하였다.
        //더 깔끔한 공식이 있을거 같지만 잘 모르겠다.
        for (int i1 = 0; i1 < len; i1++)
        {
            for (int i2 = 0; i2 < len; i2++)
            {
                if (i2 <= len / 2 && i1 + i2 >= len / 2 && len - i1 + i2 > len / 2) 
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
    else
    {
        for (int i1 = 0; i1 < len; i1++)
        {
            for (int i2 = 0; i2 < len; i2++)
            {
                if (i2 < len / 2 && i1 + i2 >= len / 2 - 1 && len - i1 + i2 > len / 2 - 1)
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
}
void print_type3(int len)
{

    for (int i1 = 0; i1 < len; i1++)
    {
        for (int i2 = 0; i2 < len; i2++)
        {
            if ((i2 >= i1 && len - i2 > i1) || (len - i2 - 1 <= i1 && i2 <= i1))
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}
void print_type4(int len)
{
    if (len % 2 == 1)
    { // 이 부분 또한 짝수 홀수가 약간씩 이상하게 나와서 짝수/홀수 case를 나누어 계산하였다.
        // 더 깔끔한 방법이 있을거 같지만 잘 모르겠다.
        for (int i1 = 0; i1 < len; i1++)
        {
            for (int i2 = 0; i2 < len; i2++)
            {
                if ((i2 >= i1 && len - i2 > i1 && i2 <= len / 2) || (len - i2 - 1 <= i1 && i2 <= i1 && i2 >= len / 2))
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
    else
    {
        for (int i1 = 0; i1 < len; i1++)
        {
            for (int i2 = 0; i2 < len; i2++)
            {
                if ((i2 >= i1 && len - i2 > i1 && i2 <= len / 2 - 1) || (len - i2 - 1 <= i1 && i2 <= i1 && i2 >= len / 2))
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
}
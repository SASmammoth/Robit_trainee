/*
    26.07.16  컴퓨터정보공학부 장경민

    음계 8개를 입력받아 오름차순, 내림차순, 섞임을 확인하여 출력하는 코드이다.
    음계은 일반적인 알파벳의 순서를 따르지 않는다. 따라서 어떠한 형식으로 확인할까 고민하다가, 음계가 8개 밖에 안되는걸 보고 순서를 하드 코딩 하였다.
    입력이 8개가 아닐때 확인하는 코드가 없다. 입력이 8개 보다 작다면 무조건 mixed가 나올 것이고, 8개보다 많다면 가 생길수도 있다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

// const int MAX_Scale_SIZE = 9; // 이러한 형식의 배열 선언이 VS에서 동작하지 않는다는걸 알게되어 수정함. C언어 1일차는 VS에서 동작하지 않을수 있다.
#define MAX_Scale_SIZE  9 // 음계의 크기를 선언하는 부분.

char Scale_classification(char list[]); // 음계를 입력받아 오름/내림차순 섞임을 확인하여 a,d,m을 반환한다.


int main()
{
    char scale[MAX_Scale_SIZE];

    printf("음 입력\n");
    scanf("%s", scale);

    char sw = Scale_classification(scale);

    printf("결과 : ");
    switch (sw) // Scale_classification의 리턴값에 따라 알맞은 단어를 출력한다.
    {
    case 'a':
        printf("ascending");
        break;
    case 'd':
        printf("descending");
        break;
    case 'm':
        printf("mixed");
        break;

    default:
        break;
    }

    printf("\n");
    return 0;
}

char Scale_classification(char list[])
{
    char as_list[] = "cdefgabC"; // 하드코딩한 순서
    char de_list[] = "Cbagfedc";

    int flag_as = 1, flag_de = 1; // 오름차순 내림차순의 플래그

    for (int i = 0; i < MAX_Scale_SIZE; i++)
    {
        if (list[i] != as_list[i])
            flag_as = 0;
        
        if (list[i] != de_list[i])
            flag_de = 0;
    }

    if(flag_as) // 플래그에 따라 오름차순, 내림차순, 섞임을 반환한다.
        return 'a';
    else if (flag_de)
        return 'd';
    else
        return 'm';
}
/*
    26.07.16  컴퓨터정보공학부 장경민
    임의의 문자를 입력하고, 찾는 문자열을 입력하여, 입력 문자에서의 위치를 출력하는 프로그램이다.
    문자열 비교 함수를 반복 실행 하여 문자열의 위치를 찾는다.

    MAX_STR = 100를 초과하는 문자열이 입력되면 에러가 발생할 수 있음.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

#define MAX_STR 100 //최대 문자열 크기

int comper_str_index(char big_str[], char small_str[], const int index, int size_small_str);    //index위치에서 문자열을 비교하여 같으면 index, 아니면 -1을 반환한다.
int str_count(char input_str[]);                                                                // 문자열의 길이를 반환함.

int main()
{
    char inputStr[MAX_STR], subStr[MAX_STR];                    //문자열들을 입력받는 부분.
    printf("최대 %d개 문자열 입력 <inputStr> : ", MAX_STR - 1);
    scanf("%s", inputStr);
    printf("찾는 문자열 <subStr> : ");
    scanf("%s", subStr);

    int inputStr_size = str_count(inputStr); // 입력 문자열 들의 길이를 구한다.
    int subStr_size = str_count(subStr);

    //printf("%d %d\n", inputStr_size, subStr_size);
    if (!(0 < subStr_size && subStr_size <= inputStr_size && inputStr_size < MAX_STR))
    {
        //예외처리 : 이상한 입출력 크기는 무시한다.
        printf("0 <= subStr <= inputStr < %d 를 만족해야 함\n", MAX_STR - 1);
        return 0;
    }

    printf("%s의 위치 : ", subStr);
    for (int i = 0; i < inputStr_size - subStr_size + 1; i++)
    {
        //문자열 위치를 구하고 출력한다. 
        if (comper_str_index(inputStr, subStr, i, subStr_size) != -1)
            printf("%d ", i + 1);
    }

    printf("\n");
    return 0;
}

int str_count(char input_str[])
{
    // 문자열의 길이를 반환함.
    int i = 0, count = 0;
    while (input_str[i] != '\0' && i < MAX_STR)
        {
            count++;
            i++;
        }

    return count;
}

int comper_str_index(char big_str[], char small_str[], const int index, int size_small_str)
{
    // index위치에서 문자열을 비교하여 같으면 index, 아니면 -1을 반환한다.
    int is_same = 1;
    for (int i = 0; i < size_small_str; i++)
    {
        if (big_str[index + i] != small_str[i])
        {
            is_same = 0;
            break;
        }
    }

    if(is_same)
        return index;
    else
        return -1;
}
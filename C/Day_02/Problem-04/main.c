/*
    26.07.18  컴퓨터정보공학부 장경민

    본 프로그램은 랜덤한 수열A와 숫자 B를 입력받아서 개수가 홀수인 A의 부분수열중 B가 중앙값인 수열의 개수를 출력하는 프로그램이다.
    길이가 홀수인 모든 부분수열을 조사하여 (1.B가 존재하는지의 여부, 2.오름차순으로 정렬했을때 가운데 오는지의 여부) 를 확인하여 개수를 센다.

    수열 A의 최대 크기는 딱히 명시된 바가 없어서 일단 MAX_N 선언을 통해 100으로 설정하였다. 차후에 수정할 수 있다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

#define MAX_N 100 // 최대 N의 크기(수열 A의 크기) 선언

void swap(int list[], int id1, int id2);                                        // 과제 2에서 두 숫자를 스왑하는 함수이다.
void my_sort(int list[], int size);                                             // 간단한 정렬 알고리즘이다.
void copy_list(const int list_org[], int clone[], int N);                       // 배열 복사
void copy_list_p12(const int list_org[], int clone[], int p1, int p2m, int N);  // list_org의 부분배열 [p1:p2]를 clone의 앞에 붙여넣는다.
void in_list(int list[], int N);                                                // 리스트를 입력 받는 함수이다.
int is_all(const int list[], int N);                                            // 1부터 N까지 자연수로 이루어져있는지 확인하는 부분이다. 알맞으면 1 아니면 0을 리턴한다.
int count_mid_B_part_seq(const int list[], const int N, const int B);           // B가 중앙값인 A의 부분수열 개수를 센다.
int find_B_index(const int list[], int B, int N);                               // B의 위치를 반환한다.
//int is_B_in_range(const int list[], int p1, int p2, int B)                    // list[p1:p2]의 범위에서 B가 있으면 1 아니면 0을 반환한다.

void printf_list(int list[], int N);                                            // 테스트용 리스트 출력 함수이다.
void printf_list_P1TOP2(int list[], int N, int p1, int p2);                     // 테스트용 리스트 출력 함수이다. 2개의 인덱스 사이의 값을 출력한다.


int main()
{
    int N, B;
    printf("N : ");
    scanf("%d", &N);
    printf("B : ");
    scanf("%d", &B);
    printf("\n");

    if (!(N < MAX_N && 0 < B && B <= N))
    {
        // N과 B의 유효성을 확인하는 코드
        printf("N의 크기는 %d 를 초과할 수 없고, 0 < B <= N이어야 한다.\n", MAX_N);
        return 0;
    }

    int list[MAX_N];

    in_list(list, N);

    if(!is_all(list, N))
    {
        // 수열 A의 유효성을 확인하는 부분
        printf("수열 A는 1부터 %d를 모두 포함하여야 합니다.\n", N);
        return 0;
    }

    int result = count_mid_B_part_seq(list, N, B); // 중앙값이 B인 부분수열의 개수를 세는 부분

    printf("중앙값이 %d인 부분수열의 개수 : %d\n", B, result);

    printf("\n");
    return 0;
}

int count_mid_B_part_seq(const int list[], const int N, const int B)
{
    int b_index;
    int count = 0;
    b_index = find_B_index(list, B, N);

    int p1, p2; // 부분수열의 시작과 끝 포인터
    int temp_list_P1ToP2[MAX_N]; // 임시로 저장하는 [p1:p2] 부분수열
    int sorted_part_Bloc;        // 정렬된 부분 수열에서 B의 위치 인덱스

    for (int leng = 1; leng <= N; leng += 2) // 부분수열의 길이는 1부터 N까지 2씩 증가하여 모든 홀수에 대해 찾는다.
    {
        for (int index_cmr = 0; index_cmr < N - leng + 1; index_cmr++) // 부분수열을 한칸씩 이동하여 찾는다.
        {
            p1 = index_cmr;
            p2 = index_cmr + leng - 1; //p1과 p2는 A의 부분수열인 [p1:p2] 관계이다.
            if (!(p1 <= b_index && b_index <= p2)) //[p1:p2]에 B가 없으면 반복을 건너띤다.
                continue;
            
            copy_list_p12(list, temp_list_P1ToP2, p1, p2, N);
            my_sort(temp_list_P1ToP2, leng);
            sorted_part_Bloc = find_B_index(temp_list_P1ToP2, B, leng); // 위의 3줄은 부분수열을 임시 배열에 복사하여 정렬한다.

            if(leng == 1) // 부분수열(임시배열)의 길이가 1이거나 B가 부분수열 가운데에 위치하고 있으면 count를 증가시킨다.
                    count++;
            else if (leng / 2 == sorted_part_Bloc)
                    count++;
        }
    }

    return count;
}

void copy_list_p12(const int list_org[], int clone[], int p1, int p2, int N)
{
    int count = 0;
    for (int i1 = p1; i1 <= p2; i1++)
    {
        clone[i1 - p1] = list_org[i1];
        count++;
    }
    for (; count < N; count++)
    {
        clone[count] = -1;
    }
}

int find_B_index(const int list[], int B, int N)
{
    for (int i = 0; i < N; i++)
    {
        if(list[i] == B) return i;
    }
    return -1;
}

int is_all(const int list[], int N)
{
    int cp_lsit[MAX_N] = {0, };

    copy_list(list, cp_lsit, N);

    my_sort(cp_lsit, N);

    for (int i = 0; i < N; i++)
        if (i + 1 != cp_lsit[i])
            return 0;

    return 1;
}

void in_list(int list[], int N)
{
    for (int i = 0; i < N; i++){
        scanf("%d", &list[i]);
    }

}

void copy_list(const int list_org[], int clone[], int N)
{
    for (int i = 0; i < N; i++)
        clone[i] = list_org[i];
} 

void my_sort(int list[], int size)
{
    for (int i1 = 0; i1 < size; i1++)
    {
        for (int i2 = 0; i2 < i1; i2++)
        {
            if(list[i1] < list[i2])
                swap(list, i1, i2);
        }
    }
}

void swap(int list[], int id1, int id2)
{
    int temp_ = list[id1];
    list[id1] = list[id2];
    list[id2] = temp_;
}

void printf_list(int list[], int N)
{
    // printf("\n");
    for (int i = 0; i < N; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void printf_list_P1TOP2(int list[], int N, int p1, int p2)
{
    // printf("\np1 : %d p2 : %d\n", p1, p2);
    for (int i = p1; i <= p2; i++)
        printf("%d ", list[i]);
    printf("\n");
}
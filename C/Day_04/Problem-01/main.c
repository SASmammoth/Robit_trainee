/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 5명의 학년, 성적, 이름을 구조체로 받아 학년->성적->이름 순으로 오름차순 정렬 하는 프록그램이다.

    학년->성적->이름 순으로 비교하는 함수를 만들고, 이를 이용하여 간단한 정렬을 이용하여 문제를 해결 하였다.
    예제를 보면 학년 성적이 대학생인거 같고, 이름에는 띄어쓰기가 없어보인다. 따라서 예외처리 또한 예제에 나와있는 형태로 처리 하였다. 
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>

#define STU_NUM 5       // 학생 수 

typedef struct _student //학생 구조체
{
    int grade;
    double gpa;
    char name[10];
} student;

int cpr_stu(student s1, student s2);    // 학생 1과 2를 비교 하여 2가 더 크면 1을 아니면 0을 리턴한다. 전부다 같으면 1을 리턴한다.
void input_stu(student *list);          // 학생 리스트 포인터와 사용자의 입력을 받아 학생 리스트를 완성한다.
void sort_stu(student *list);           // 학생 리스트를 정렬한다.

void print_stu(student *list);          // 학생 리스트를 출력한다.
void swap_stu(student *list, int p1, int p2); // 학생리스트에서 두 요소를 바꾼다.

void cpy_str(char *copyer, char *original, int len); // 문자열을 복사하는 함수이다.

int main()
{
    student stu_list[STU_NUM];

    input_stu(stu_list);

    sort_stu(stu_list);

    print_stu(stu_list);

    return 0;
}

void cpy_str(char *copyer, char *original, int len)
{
    for (int i = 0; i < len; i++)
        copyer[i] = original[i];
}

void swap_stu(student *list, int p1, int p2)
{
    student temp;
    temp.grade = list[p1].grade;
    temp.gpa = list[p1].gpa;
    cpy_str(temp.name, list[p1].name, 10);

    list[p1].grade = list[p2].grade;
    list[p1].gpa = list[p2].gpa;
    cpy_str(list[p1].name, list[p2].name, 10);

    list[p2].grade = temp.grade;
    list[p2].gpa = temp.gpa;
    cpy_str(list[p2].name, temp.name, 10);
}

int cpr_stu(student s1, student s2)
{
    if(s1.grade == s2.grade) // 학년을 먼저 비교함
    {
        if(s1.gpa == s2.gpa) //학점을 비교함
        {
            for (int i = 0; i < 10; i++)
            {
                if(s1.name[i] == s2.name[i])
                    continue;
                else
                    return s2.name[i] > s1.name[i];
            }
            return 1;
        }
        else
            return s2.gpa > s1.gpa;
    }
    else
        return s2.grade > s1.grade;
}

void sort_stu(student *list)
{
    for (int i1 = 0; i1 < STU_NUM; i1++)
    {
        for (int i2 = 0; i2 < STU_NUM - i1 - 1; i2++)
        {
            int temp_ = cpr_stu(list[i2], list[i2 + 1]);
            //printf("%d\n", temp_);
            if (!temp_)
            {
                swap_stu(list, i2, i2 + 1);
            }
        }
    }
}

void print_stu(student *list)
{
    printf("\n");
    for (int i = 0; i < STU_NUM; i++)
    {
        printf("%d %.1lf %9s\n", list[i].grade, list[i].gpa, list[i].name);
    }
    printf("\n");
}

void input_stu(student *list)
{
    int _grade;
    double _gpa;
    char _name[10];

    int count = 0;
    printf("학년, 성적, 이름을 입력하시오. (이름의 길이는 9보다 작아야 함)\n"); // 입력버퍼를 만져서 일정길이 이상의 이름은 예외처리 하고 싶은데 배우지 않아서 사용자입력에 의존함.
    while (count < STU_NUM)
    {
        scanf("%d %lf %s", &_grade, &_gpa, _name);
        
        if((0 < _grade && _grade <= 4) && ( 0 <= _gpa && _gpa <= 4.5)) // 입력값이 올바른지 확인
        {
            list[count].grade = _grade;
            list[count].gpa = _gpa;
            for (int i = 0; i < 10; i++)
                list[count].name[i] = _name[i];

            count++;
        }
        else
        {
            printf("입력이 잘못되었습니다. 다시 입력하세요.\n");
            printf("0 < grade <= 4, 0 <= gpa <= 4.5를 만족해야함 \n");
        }
    }
}

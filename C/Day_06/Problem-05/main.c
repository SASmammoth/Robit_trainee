/*
    26.07.23.  컴퓨터정보공학부 장경민
    본 프로그램은 간단한 출석부 프로그램이다.

    구조체배열, 구조체포인터를 이용한 함수이용.
    구조체 배열을 사용하라고 하였다. 따라서 구조체포인터를 이용한 동적할당을 쓸수가 없어 MAX_STD이용해 Student 구조체 배열을 선언하였다.

    출석부에서 학생이 삭제되면 배열에서는 형식이 깨지기 때문에 하나의 명령이 올때마다 배열을 깔끔하게 리프레쉬 하는 코드를 넣었다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

#define ADDR_D 4 // 주소의 깊이 단계이다.
#define MAX_STD 100 // 입력가능한 최대 학생수 이다.
#define MAX_STRING 20 // 입력가능한 최대 문자열 크기이다.
#define CMD_NUM 5 + 1    // 입력가능한 명령어의 종류개수.

const char *Sort_by_list[7] = {"number",
                               "name",
                               "address1",
                               "address2",
                               "address3",
                               "address4",
                               "grade"}; // 여기저기 많이 사용되어 전역변수로 선언함

typedef struct _Student
{
    int is_valid; // 학생이 유효한지 확인하는 코드이다.
    int number;
    char *name;
    char *address[ADDR_D];
    double grade;
} Student;



int str_cmp(char *s1, char *s2);                            // 간단한 문자열 비교 함수이다. 다르면 0 같으면 1을 출력한다.
int str_cmp_GL(char *s1, char *s2);                         // 위의 함수를 약간 변형하여 만듦 s2가 크다면 1 아니면 0을 반환함.
void swap(Student *s1, Student *s2);                          // 학생을 서로 바꾼다.

void cut_enter(char *s);                                    // fgets 로 받은 문자열에서 줄바꿈을 없앤다.
int str_len(char *s);                                       // 문자열의 길이를 반환한다.
int ret_cmd_index(char *cmd);                               // cmdlist에서 명령어 인덱스를 반환함,

int clear_list(Student *list); // 학생부 동적할당 해제


char *string_input_manizer(int input_index); // 문자열 입력을 자동화 해준다.

int add_stu(Student *list, int *stu_num);                   // 학생을 추가한다.
void sort_stu(Student *list, char *sort_by, int stu_num);   // 학생 배열을 정렬하는 함수이다. sort_by로 기준을 받는다. sort_by {"number", "name", "address1" ~ "address4", grade} 총 7개가 가능하다.
int sort_stu_input(Student *list, int *stu_num);            // 함수 포인터를 사용하기 위한 중간 버퍼.
int delete_stu(Student *list, int *stu_num);                // 학생을 제거한다
int find_stu(Student *list, int *stu_num);                // 학생을 찾는다.
int S_L_stu(Student *list, int *stu_num);                   // 학생을 불러오고 저장한다.
void refresh_list(Student *list);                           // 리스트를 리프래쉬 하는 함수 (빈 것들을 뒤로 밀어버린다)
void print_stu(Student *list, int stunum);                  // 학생리스트 출력하는 함수.

// 삭제 기준
int delete_by_number(Student *s1, void * p2); // void포인터를 직접적으로 배우지는 않았지만 void도 배웠고 포인터도 배웠으므로 사용함.
int delete_by_name(Student *s1, void *p2);  // void포인터를 사용 안 해도 문제를 풀 수 있지만 그렇게 된다면 dele_stu_input함수가 많이 지저분해지므로 사용함.
int delete_by_address1(Student *s1, void *p2);
int delete_by_address2(Student *s1, void *p2);
int delete_by_address3(Student *s1, void *p2);
int delete_by_address4(Student *s1, void *p2);
int delete_by_grade(Student *s1, void *p2);

// 정렬 기준
int sort_by_number(Student *s1, Student *s2);
int sort_by_name(Student *s1, Student *s2);
int sort_by_address1(Student *s1, Student *s2);
int sort_by_address2(Student *s1, Student *s2);
int sort_by_address3(Student *s1, Student *s2);
int sort_by_address4(Student *s1, Student *s2);
int sort_by_grade(Student *s1, Student *s2);

int empty_func(Student *list, int *stunum); // exit자리 체우기용 빈 함수

int main()
{
    char *cmd = (char *)malloc(sizeof(char) * 15);
    int (*func_list[CMD_NUM])(Student *, int *) = {empty_func, add_stu, delete_stu, sort_stu_input, S_L_stu, find_stu};
    Student my_stu[MAX_STD] = {0, };
    int stu_num = 0;

    while (1)
    {
        printf("명령어를 입력하시오.\nexit, add, delete, sort, s/l, find\n");
        scanf("%14s", cmd);
        int cmd_index = ret_cmd_index(cmd);
        if(cmd_index == -1)
            {printf("잘못된 명령어 입니다.\n"); continue;}

        if(cmd_index == 0) break;
        else
            func_list[cmd_index](my_stu, &stu_num);

        
        refresh_list(my_stu);
        print_stu(my_stu, stu_num);
    }

    clear_list(my_stu);
    free(cmd);
    printf("\n");
    return 0;
}

int S_L_stu(Student *list, int *stu_num)
{
    const char *S_L_by_list[2] = {"save",
                                  "load"};

    char S_L_by[20];
    printf("저장/제거를 선택하시오.\n");
    printf("명령어 : save, load\n");
    scanf("%19s", S_L_by);
    while (getchar() != '\n');

    int by_index = -1;
    for (int i = 0; i < 2; i++) // 정렬 인자와 삭제인자가 같으므로 그대로 사용함.
    {
        if (str_cmp(S_L_by_list[i], S_L_by))
        {by_index = i;break;}
    }

    if(by_index == -1)
    {printf("잘못된 명령어 입니다.\n"); return -1;}

    char file_name[20];
    printf("파일이름을 입력하시오.\n");
    scanf("%19s", file_name);
    while (getchar() != '\n');

    int file_name_len = str_len(file_name);
    if (!str_cmp(file_name + file_name_len - 4, ".txt"))
    {printf("파일 이름의 확장자는 .txt이여야 합니다.\n"); return -1;}

    FILE *F;
    switch (by_index)
    {
    case 0: // save일때
        F = fopen(file_name, "w");

        fprintf(F, "%d\n", *stu_num); // 학생 수를 따로 저장
        for (int i = 0; i < *stu_num; i++)
        {
            fprintf(F, "%d\t%s\t%s\t%s\t%s\t%s\t%.2lf\n",
                    list[i].number, list[i].name,
                    list[i].address[0], list[i].address[1],
                    list[i].address[2], list[i].address[3],
                    list[i].grade);
        }
        fclose(F);
        break;
    
    case 1: // load일때
        F = fopen(file_name, "r");

        if(F == NULL)
        {printf("%s는 존재하지 않습니다.\n", file_name); return 0;}
        
        clear_list(list);   // 읽는거는 한번 초기화 하고 다시 실행함.

        fscanf(F, "%d\n", stu_num); // 학생 수를 따로 불러옴
        for (int i = 0; i < *stu_num; i++)
        {
            list[i].name = (char *)malloc(sizeof(char) * MAX_STRING + 1);   // 동적 할당 먼저
            list[i].address[0] = (char *)malloc(sizeof(char) * MAX_STRING + 1);
            list[i].address[1] = (char *)malloc(sizeof(char) * MAX_STRING + 1);
            list[i].address[2] = (char *)malloc(sizeof(char) * MAX_STRING + 1);
            list[i].address[3] = (char *)malloc(sizeof(char) * MAX_STRING + 1);

            fscanf(F, "%d\t%20[^\t]\t%20[^\t]\t%20[^\t]\t%20[^\t]\t%20[^\t]\t%lf\n",
                   &list[i].number, list[i].name,
                   list[i].address[0], list[i].address[1],
                   list[i].address[2], list[i].address[3],
                   &list[i].grade);
            list[i].is_valid = 1;
        }
        fclose(F);
        break;

    default:
        break;
    }

    return 1;
}

int find_stu(Student *list, int *stu_num)
{
    // delete를 수정하여 사용함
    int (*delete_func_list[7])(Student *, void *) = {delete_by_number, delete_by_name, delete_by_address1, delete_by_address2, delete_by_address3, delete_by_address4, delete_by_grade};
    // ^함수 포인터 사용

    char delete_by[20];
    printf("찾는 기준을 입력하시오.\n");
    printf("명령어 : number, address1, address2, address3, address4, grade\n");
    scanf("%19s", delete_by);
    while (getchar() != '\n')
        ;

    int by_index = -1;
    for (int i = 0; i < 7; i++) // 정렬 인자와 삭제인자가 같으므로 그대로 사용함.
    {
        if (str_cmp(Sort_by_list[i], delete_by))
        {
            by_index = i;
            break;
        }
    }

    if (by_index == -1)
    {
        printf("올바르지 않은 삭제 기준입니다.\n");
        return -1;
    }
    else if(by_index == 2) // delete를 수정하여 사용하였기 때문에 예외처리를 하였다.
    {
        printf("이름으로 이름을 찾을수는 없습니다.\n");
        return -1;
    }

    int temp_i;
    double temp_d;
    char temp_s[20];
    void *temp_point; // 정수형, 실수, 문자열을 넣기위한 void형 포인터

    printf("%s : ", Sort_by_list[by_index]);
    if (by_index == 0) // 입력이 3가지가 올수 있으므로 3개를 추가함.
    {
        scanf("%d", &temp_i);
        while (getchar() != '\n')
            ;
        temp_point = &temp_i;
    }
    else if (by_index == 6)
    {
        scanf("%lf", &temp_d);
        while (getchar() != '\n')
            ;
        temp_point = &temp_d;
    }
    else
    {
        scanf("%19s", temp_s);
        while (getchar() != '\n')
            ;
        temp_point = &temp_s;
    }

    int flag_tmep = 1;
    for (int i = 0; i < *stu_num; i++)
    {
        if (delete_func_list[by_index](&list[i], temp_point)) // 일치하는것 비활성화.
        {
            flag_tmep = 0;
            printf("찾는 이름 : %s\n", list[i].name);
        }
    }

    if(flag_tmep)
    {printf("입력하신 것은 존재하지 않습니다.\n"); return 0;}
    return 1;
}

int delete_stu(Student *list, int *stu_num)
{
    int (*delete_func_list[7])(Student *, void *) = {delete_by_number, delete_by_name, delete_by_address1, delete_by_address2, delete_by_address3, delete_by_address4, delete_by_grade};
    // ^함수 포인터 사용

    char delete_by[20];
    printf("삭제 기준을 입력하시오.\n");
    printf("명령어 : number, name, address1, address2, address3, address4, grade\n");
    scanf("%19s", delete_by);
    while (getchar() != '\n');

    int by_index = -1;
    for (int i = 0; i < 7; i++)  // 정렬 인자와 삭제인자가 같으므로 그대로 사용함.
    {
        if (str_cmp(Sort_by_list[i], delete_by))
        { by_index = i; break;}
    }

    if (by_index == -1)
    {printf("올바르지 않은 삭제 기준입니다.\n"); return -1;}

    int temp_i;
    double temp_d;
    char temp_s[20];
    void *temp_point; // 정수형, 실수, 문자열을 넣기위한 void형 포인터

    printf("%s : ", Sort_by_list[by_index]);
    if (by_index == 0)  // 입력이 3가지가 올수 있으므로 3개를 추가함.
    {
        scanf("%d", &temp_i);
        while (getchar() != '\n');
        temp_point = &temp_i;
    }
    else if (by_index == 6)
    {
        scanf("%lf", &temp_d);
        while (getchar() != '\n');
        temp_point = &temp_d;
    }
    else
    {
        scanf("%19s", temp_s);
        while (getchar() != '\n');
        temp_point = &temp_s;
    }

    int match_idx[MAX_STD]; // 중복 학생 인덱스 저장
    int match_num = -1;

    for (int i = 0; i < *stu_num; i++)
    {
        if (delete_func_list[by_index](&list[i], temp_point)) // 일치하는것 비활성화.
        {
            match_num++;
            match_idx[match_num] = i;
        }
    }

    if(match_num == -1)
    {
        printf("입력하신 것은 존재하지 않습니다.\n");
        return 0;
    }
    else if(match_num == 0)
    {
        list[match_idx[0]].is_valid = 0; // 항목 비활성화 후 할당 해제.
        free(list[match_idx[0]].name);
        free(list[match_idx[0]].address[0]);
        free(list[match_idx[0]].address[1]);
        free(list[match_idx[0]].address[2]);
        free(list[match_idx[0]].address[3]);
        (*stu_num)--;
        return 1;
    }
    else
    {
        printf("일치하는 것이 몇가지 있습니다.\n");
        for (int i = 0; i < match_num + 1; i++)
        {
            printf("%d 번 : %-6d%-*s%-*s%-*s%-*s%-*s%8.2lf\n", i,
                   list[match_idx[i]].number, MAX_STRING + 2, list[match_idx[i]].name,
                   MAX_STRING + 2, list[match_idx[i]].address[0],
                   MAX_STRING + 2, list[match_idx[i]].address[1],
                   MAX_STRING + 2, list[match_idx[i]].address[2],
                   MAX_STRING + 2, list[match_idx[i]].address[3],
                   list[match_idx[i]].grade);
        }
        printf("삭제할 번호를 입력하시오. (0 ~ ?)\n");
        int temp_;
        scanf("%d", &temp_);

        if(!( 0 <= temp_ && temp_ <= match_num))
            {printf("잘못된 번호\n"); return 0;}

        list[match_idx[temp_]].is_valid = 0; // 항목 비활성화 후 할당 해제.
        free(list[match_idx[temp_]].name);
        free(list[match_idx[temp_]].address[0]);
        free(list[match_idx[temp_]].address[1]);
        free(list[match_idx[temp_]].address[2]);
        free(list[match_idx[temp_]].address[3]);
        (*stu_num)--;
        return 1;
    }
}

int delete_by_number(Student *s1, void *p2)
{return s1->number == *(int *)p2;}
int delete_by_name(Student *s1, void *p2)
{return str_cmp(s1->name, (char *)p2);}
int delete_by_address1(Student *s1, void *p2)
{return str_cmp(s1->address[0], (char *)p2);}
int delete_by_address2(Student *s1, void *p2)
{return str_cmp(s1->address[1], (char *)p2);}
int delete_by_address3(Student *s1, void *p2)
{return str_cmp(s1->address[2], (char *)p2);}
int delete_by_address4(Student *s1, void *p2)
{return str_cmp(s1->address[3], (char *)p2);}
int delete_by_grade(Student *s1, void *p2)
{return s1->grade == *(double *)p2;}

int add_stu(Student *list, int *stu_num)
{
    if (*stu_num >= MAX_STD)
    {printf("더 이상 추가할 수 없습니다.\n"); return 0;}
    
    
    printf("번호, 이름, 주소(format : 나라,도,시,구), 성적을 입력하시오. (문자열은 %d자 이하만 가능합니다, 탭을 치면 오류가 생길 수 있음)\n", MAX_STRING);
    // 파일 저장할때 탭으로 항목을 나누는데 , 탭을 치면 에러가 날 수 있음.

    int input_index = 0;
    while (1)   // 사용자로 부터 입력을 받아 예외처리 하는 부분이다. 함수를 이용해서 자동화 할까 고민하다가 그냥 이렇게 하였다.
    {           // 번호를 입력 받는 부분
        int temp_number;
        printf("%s : ", Sort_by_list[input_index]);
        scanf("%d", &temp_number);
        while (getchar() != '\n');
        if (temp_number <= 0)
        {
            printf("번호는 음수가 올 수 없습니다.\n");
            continue;
        }
        list[*stu_num].number = temp_number;
        break;
    }

    input_index++;
    while (1) // 이름을 입력 받는 부분
    {       
        char *temp_str = string_input_manizer(input_index);

        if(!('A' <= temp_str[0] && temp_str[0] <= 'Z'))
        {
            printf("이름의 첫 글자는 대문자여야 합니다..\n");
            free(temp_str);
            continue;
        }
        list[*stu_num].name = temp_str;
        break;
    }

    input_index++;
    const char* addr_format[ADDR_D] = {"", "-do", "-si", "-gu"};
    for (int addr_in_index = 0; addr_in_index < 4;) // 주소를 입력받는 부분
    {
        char *temp_str = string_input_manizer(input_index);
        int addr_num = str_len(temp_str);
        if (!str_cmp(temp_str + addr_num - str_len(addr_format[addr_in_index]), addr_format[addr_in_index]))
        {
            printf("%s 뒤에는 %s가 와야 합니다.\n", Sort_by_list[input_index], addr_format[addr_in_index]);
            free(temp_str);
            continue;
        }
        list[*stu_num].address[addr_in_index] = temp_str;
        addr_in_index++;
        input_index++;
        if(addr_in_index >= 4) break;
    }

    while (1) // 성적을 입력 받는 부분
    {
        double temp_grade;
        printf("%s : ", Sort_by_list[input_index]);
        scanf("%lf", &temp_grade);
        while (getchar() != '\n');
        if (temp_grade < 0 || 100 <= temp_grade)
        {
            printf("성적은 0 ~ 100점만이 올 수 있습니다.\n");
            continue;
        }
        list[*stu_num].grade = temp_grade;
        break;
    }

    list[*stu_num].is_valid = 1;

    (*stu_num)++;
    return 1;
}

int str_len(char *s)
{
    int count = 0;
    while(*(s++) != '\0')
        count++;

    return count;
}

char *string_input_manizer(int input_index)
{
    char *temp_str = (char *)malloc(sizeof(char) * MAX_STRING + 1);
    printf("%s : ", Sort_by_list[input_index]);
    fgets(temp_str, MAX_STRING + 1, stdin);

    int is_cuttd = 1;
    for (int i = 0; i < MAX_STRING + 1; i++) // 입력 최대 크기만큼 잘라내는 부분이다.
        if(temp_str[i] == '\n')
        {
            is_cuttd = 0;
            break;
        }
    if(is_cuttd) while (getchar() != '\n');

    cut_enter(temp_str);

    return temp_str;
}

void sort_stu(Student *list, char *sort_by, int stu_num)
{
    int (*sort_func_list[7])(Student *, Student *) = {sort_by_number, sort_by_name, sort_by_address1, sort_by_address2, sort_by_address3, sort_by_address4, sort_by_grade};

    int by_index = -1;
    for (int i = 0; i < 7; i++)
    {
        if (str_cmp(Sort_by_list[i], sort_by))
        {by_index = i; break;}
    }

    if(by_index == -1)
    { printf("올바르지 않은 정렬 기준입니다.\n"); return;}

    for (int i1 = 0; i1 < stu_num; i1++)
    {
        for (int i2 = 0; i2 < stu_num - i1 - 1; i2++)
        {
            int temp_ = sort_func_list[by_index](&list[i2], &list[i2 + 1]);
            // printf("%d\n", temp_);
            if (!temp_)
            {
                swap(&list[i2], &list[i2 + 1]);
            }
        }
    }
}

int sort_stu_input(Student *list, int *stu_num){
    char sort_by[20];
    printf("정렬 기준을 입력하시오.\n");
    printf("명령어 : number, name, address1, address2, address3, address4, grade\n");
    scanf("%19s", sort_by);
    while (getchar() != '\n');

    sort_stu(list, sort_by, *stu_num);

    return 1;
}

void refresh_list(Student *list)
{
    for (int i1 = 0; i1 < MAX_STD; i1++)
    {
        for (int i2 = 0; i2 < MAX_STD - i1 - 1; i2++)
        {
            int temp_ = list[i2].is_valid < list[i2 + 1].is_valid;
            // printf("%d\n", temp_);
            if (temp_)
            {
                swap(&list[i2], &list[i2 + 1]);
            }
        }
    }
}

int sort_by_number(Student *s1, Student *s2)
{
    return s1->number < s2->number;
}
int sort_by_name(Student *s1, Student *s2)
{
    return str_cmp_GL(s1->name, s2->name);
}
int sort_by_address1(Student *s1, Student *s2)
{
    return str_cmp_GL(s1->address[0], s2->address[0]);
}
int sort_by_address2(Student *s1, Student *s2)
{
    return str_cmp_GL(s1->address[1], s2->address[1]);
}
int sort_by_address3(Student *s1, Student *s2)
{
    return str_cmp_GL(s1->address[2], s2->address[2]);
}
int sort_by_address4(Student *s1, Student *s2)
{
    return str_cmp_GL(s1->address[3], s2->address[3]);
}
int sort_by_grade(Student *s1, Student *s2)
{
    return s1->grade > s2->grade;
}

void print_stu(Student *list, int stunum)
{
    printf("\n\n");
    printf("%-6s%-*s%-*s%-*s%-*s%-*s%8s\n",
           "No", MAX_STRING + 2, "Name",
           MAX_STRING + 2, "Addr1", MAX_STRING + 2, "Addr2",
           MAX_STRING + 2, "Addr3", MAX_STRING + 2, "Addr4", "Grade");

    for (int i = 0; i < stunum; i++)
    {
        printf("%-6d%-*s%-*s%-*s%-*s%-*s%8.2lf\n",
               list[i].number, MAX_STRING + 2, list[i].name,
               MAX_STRING + 2, list[i].address[0],
               MAX_STRING + 2, list[i].address[1],
               MAX_STRING + 2, list[i].address[2],
               MAX_STRING + 2, list[i].address[3],
               list[i].grade);
    }
    printf("\n\n");
}

void swap(Student *s1, Student *s2)
{
    Student temp;
    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

int str_cmp_GL(char *s1, char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
    {
        if (*s1 == '\0')
            return 0;
    }
    return *s1 < *s2;
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

void cut_enter(char *s)
{
    while (*s != '\0')
    {
        if (*s == '\n')
            *s = '\0';
        s++;
    }
}

int ret_cmd_index(char *cmd)
{
    const char *cmd_list[CMD_NUM] = {"exit", "add", "delete", "sort", "s/l", "find"}; // 명령어 리스트를 선언함.

    //const char *cmd_list[CMD_NUM] = {"exit", "add", "sort_stu"}; // 테스트용

    for (int i = 0; i < CMD_NUM; i++)
        if (str_cmp(cmd, cmd_list[i]))
            return i;

    return -1;
}

int empty_func(Student *list, int *stunum)
{
    return 0;
}

int clear_list(Student *list)
{
    for (int i = 0; i < MAX_STD; i++)
    {
        if (!list[i].is_valid)
            continue;
        free(list[i].name);
        free(list[i].address[0]);
        free(list[i].address[1]);
        free(list[i].address[2]);
        free(list[i].address[3]);
        list[i].is_valid = 0;
    }
    return 1;
}
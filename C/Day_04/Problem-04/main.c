/*
    26.07.21.  컴퓨터정보공학부 장경민
    본 프로그램은 y m d h m s로 구성되있는 날짜, 시각 2개를 입력받아 그 둘의 차이를 시분초로 계산하는 프로그램이다.

    중첩 구조체의 timstamp로 시간을 입력받는다.
    이를 0001. 01. 01. 00:00:00 이후 지난 second로 환산하여 둘을 뺀 뒤에 hms구조로 출력한다.
*/

#define _CRT_SECURE_NO_WARNINGS // VS용 선언
#include <stdio.h>
#include <stdlib.h>

typedef struct
 {
    int year;
    int month;
    int day;
} DATE;
typedef struct 
{
    int hour;
    int min;
    int sec;
} TIME;

typedef struct // PPT에 있는 형식의 중첩 구조체 생성 
{
    DATE Date;
    TIME Time;
}TIMESTAMP;

const int month_day[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};         // 한달에 몇일이 있는지 확인하는 배열
const int month_day_leap[13] = {-1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_leap(int year);                  // 윤년인지 확인하는 함수. 윤년이라면 1을 반환함. 1일차 과제에서 가져옴
void input_timestamp(TIMESTAMP *ts);    // 타임스템프 입력 함수, 유효값 확인도 같이함.

void print_timestamp(TIMESTAMP *ts);    // 타임스템프를 출력한다.

long long int cal_sec(TIMESTAMP ts);    // 0년 1월 1일 00:00:00 이후로 흐른 시간을 초 단위로 계산하여 리턴함

void print_sec_to_hms(long long int sec); // 초를 입력 받아서 흐른 시간으로 계산해줌.

int main()
{
    TIMESTAMP t1, t2;

    input_timestamp(&t1);
    input_timestamp(&t2);

    //print_timestamp(&t1);

    long long int t_sec_1, t_sec_2;

    t_sec_1 = cal_sec(t1);
    t_sec_2 = cal_sec(t2);

    print_sec_to_hms(t_sec_1 > t_sec_2 ? t_sec_1 - t_sec_2 : t_sec_2 - t_sec_1); // 3항연산자를 통해 이 인수 전달.

    //printf("%lld\n", t_sec_1);

    printf("\n");
    return 0;
}

void print_sec_to_hms(long long int sec)
{
    printf("%lld시 %lld분 %lld초\n", sec / 3600, (sec % 3600) / 60, sec % 60);
}

long long int cal_sec(TIMESTAMP ts)
{
    long long int sum_sec_ = 0;

    long long int leap_year_count = 0;
    long long int no_leap_year_count = 0;

    // 년도 부터 시분초 까지 지난 시간을 계산
    for (int i = 1; i < ts.Date.year; i++)
    {
        if(is_leap(i))
            leap_year_count++;
        else
            no_leap_year_count++;
    }

    sum_sec_ += no_leap_year_count * 31536000;  // 1년을 초로 환산하여 지나온 햇수를 곱하여 입력함.
    sum_sec_ += leap_year_count * 31622400;     // 윤년을 초로 환산하여 지나온 햇수를 곱하여 입력함.

    for (int i = 1; i < ts.Date.month; i++)
    {
        if(is_leap(ts.Date.year))
            sum_sec_ += 86400 * month_day_leap[i];
        else
            sum_sec_ += 86400 * month_day[i];
    }

    sum_sec_ += (ts.Date.day - 1) * 86400;

    sum_sec_ += ts.Time.hour * 3600;

    sum_sec_ += ts.Time.min * 60;

    sum_sec_ += ts.Time.sec;

    return sum_sec_;
}

void input_timestamp(TIMESTAMP *ts)
{
    int year_, month_, day_, hour_, min_, sec_;
    while (1)
    {
        scanf("%d %d %d %d %d %d", &year_, &month_, &day_, &hour_, &min_, &sec_);

        int max_day = 0;

        if (year_ <= 0) // 입력의 유효성을 검사하는 부분이다.
        {
            printf("년도는 양의 정수만 올 수 있습니다.\n");
            continue;
        }
        if (!(0 < month_ && month_ <= 12))
        {
            printf("1 <= month <= 12 를 만족해야 함.\n");
            continue;
        }
        if (is_leap(year_) && month_ == 2)
            max_day = 29;
        else
            max_day = month_day[month_];
        if (!(0 < day_ && day_ <= max_day))
        {
            printf("%d월은 1 <= day <= %d를 만족해야함.\n", month_, max_day);
            continue;
        }
        if (!(0 <= hour_ && hour_ < 24))
        {
            printf("시는 0 <= hour < 24를 만족해야 함.\n");
            continue;
        }
        if (!(0 <= min_ && min_ < 60))
        {
            printf("분은 0 <= min < 60를 만족해야 함.\n");
            continue;
        }
        if (!(0 <= sec_ && sec_ < 60))
        {
            printf("초는 0 <= sec < 60를 만족해야 함.\n");
            continue;
        }

        

        ts->Date.year = year_;
        ts->Date.month = month_;
        ts->Date.day = day_;
        ts->Time.hour = hour_;
        ts->Time.min = min_;
        ts->Time.sec = sec_;
        break;
    }
}

void print_timestamp(TIMESTAMP *ts)
{
    printf("%d %d %d %d %d %d\n", ts->Date.year, ts->Date.month, ts->Date.day, ts->Time.hour, ts->Time.min, ts->Time.sec);
}

    int is_leap(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1;
    else
        return 0;
}
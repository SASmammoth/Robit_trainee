#include <stdio.h>
#include <stdlib.h>

int *pt;

void tem(int list[5])
{
    printf("%d", sizeof(list));
}

void tem1(int list[5])
{
    int a[7];
    int *p;

    &a[0] == a;

    p = a;
    *(p + 3); // p[3]과 같은 값을 가진다.
}

void tem2(){
    int a[7], b[8];
    int *p;

    sizeof(a); // 28 // 컴파일러가 a의 크기를 할당해줌
    sizeof(p); // 4

    p = a;
    p = b; // 가르키는 값 변경 가능
    //a = b; // 변경 불가능
}

void tem3(int a[10])
{
    sizeof(a); // 4 // 함수로 배열을 전달받으면 포인터로 변환됨
}

void tem4(int a[10])
{
    int list[8];
    int *p;
    int *q = (int *)malloc(sizeof(int) * 10);
    sizeof(list); // 32
    sizeof(p); // 4
    sizeof(q); // 4

    free(q);
}

int main()
{
    int list[5];
    int *a;

    printf("%d\n", sizeof(a));

    tem(list);

    return 0;
}

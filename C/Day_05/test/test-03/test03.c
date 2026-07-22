#include <stdio.h>
#include <stdlib.h>
/*
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


void swap(int a, int b) // 교환 안됨
{
    int temp = a;
    a = b;
    b = a;
}
    */
/*
void swap(int &a, int &b) // 교환 안됨
{
    int temp = *a;
    *a = *b;
    *b = *a;
}
    */
/*
typedef struct _S {int list[1000000];} S;

void def1(S s1) // S의 리스트 백만개를 모두 복사한다.
{ /*...*/ /*};*/
/*
void def2(S* s1) // S의 주소만 복사하여 자원을 아낄수 있다.
{/*...*//*};*/
/*
int func1(int i1, int c1){ }

typedef struct _S {int a; char b} S;
S *pS;
*/

int main()
{

    char **list = (char **)malloc(sizeof(char *) * 3);
    *(list) = "text 00";
    *(list + 1) = "text 01";
    *(list + 2) = "text 02";
    
    char *temp = *(list + 1);
    *(list + 1) = *(list + 0);
    *(list + 0) = temp;
    // list = {"text01", "text00", "text02"}

    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", list[i]);
    }

/*
    int val = 5;
    int *p1;
    int **p2;

    p1 = &val; // p1에는 val의 주소가 저장되어 있다.
    p2 = &p1;  // p2에는 p1의 주소가 저장되어 있다.

    val == *p1 == **p2



    S tamp;
    pS = &tamp;

    pS->a;      // 구조체 포인터에 접근할 때에는 -> 연산자를 사용 할 수 있다.
    *pS.a       // 연산자 우선순위에 따라 .연산이 먼저 나온다.
    (*pS).a;    // 괄호를 씌우면 해결되긴 한다. 하지만 보기에 안 좋다.

    int (*func_p)(int *, char *); // 선언

    func_p = func1; // 새로운 연결

    int list[5];
    int *a;

    printf("%d\n", sizeof(a));

    tem(list);
*/
    return 0;
}

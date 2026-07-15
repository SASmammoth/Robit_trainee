#include <stdio.h>

int main()
{
    printf("Input Arithmetic Operation\n");
    printf("ex)\t\t3.4 * 8.5\n");
    printf("\t\t2.9 - 5.4\n");
    printf("\t\t3.9 * 8.0\n");
    printf("\t\t3.9 ^ 8\n");
    printf("input : ");

    double left;
    double right;
    char op;

    scanf("%lf %c %lf", &left, &op, &right);

    switch (op)
    {
    case '+':
        printf("%.2lf + %.2lf = %.2lf", left, right, left + right);
        break;

    case '-':
        printf("%.2lf - %.2lf = %.2lf", left, right, left - right);
        break;

    case '*':
        printf("%.2lf * %.2lf = %.2lf", left, right, left * right);
        break;

    case '/':
        printf("%.2lf / %.2lf = %.2lf", left, right, left / right);
        break;

    case '^':
        printf("%.2lf ^ %.2lf = ", left, right);
        double anser = 1.0;
        for (int i = 0; i < (int)right; i++)
            anser *= left;
        printf("%.2lf", anser);
        break;

    default:
        printf("%c 와 같은 연산자는 존재하지 않습니다.", op);
        break;
    }

    printf("\n");
    return 0;
}
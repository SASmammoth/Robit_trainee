#include <stdio.h>

int main()
{
    int n = 1, r = 1;

    for (int i = 0; i == 0; i++)
    {
        printf("순열,중복순열, 조합, 중복조합을 계산하기 위한 \"n r\" 을 입력하시오.");
        scanf("%d %d", &n, &r);

        if (0 < r && r <= n)
        {
            int nF = 1, rF = 1, nmrF = 1, nprm1F = 1, nm1F = 1;

            int break_flag = 0;
            for (int i = 1; i <= n + r - 1; i++)
            {
                if (i >= 13)
                {
                    printf("\n현재의 자료형으로는 12! 이상의 값을 계산하기 힘듦.\n\n");
                    break_flag = 1;
                    break;
                }
                nprm1F *= i;
            }
            
            if(break_flag)
                break;

            for (int i = 1; i <= n; i++)
                nF *= i;
            for (int i = 1; i <= r; i++)
                rF *= i;
            for (int i = 1; i <= n - r; i++)
                nmrF *= i;
            for (int i = 1; i <= n - 1; i++)
                nm1F *= i;

            //printf("nf : %d, rF : %d, nmrF : %d, nprm1F : %d nm1F : %d\n", nF, rF, nmrF, nprm1F, nm1F);

            int nPr,
                nPIr = 1, nCr, nHr;

            nPr = nF / nmrF;
            for (int i = 1; i <= r; i++)
                nPIr *= n;
            nCr = nF / (nmrF * rF);
            nHr = nprm1F / (nm1F * rF);

            printf("\n순열 : %d\n", nPr);
            printf("중복순열 : %d\n", nPIr);
            printf("조합 : %d\n", nCr);
            printf("중복조합 : %d\n", nHr);
        }
        else
            printf("순열등을 계산할때에는 0 < r <= n을 만족해야만 함.");

        printf("\n");
        break;
    }

    return 0;
}
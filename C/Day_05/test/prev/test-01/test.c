#include <stdio.h>

int main()
{
    int list1D[5] = {10, 20, 30, 40, 50};
    int list2D[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};

    size_t size;

    size = sizeof(list1D);
    printf("size : %d\n", size);

    size = sizeof(list2D);
    printf("size : %d\n", size);

    return 0;
}
#include <stdio.h>
#include <Windows.h>
#include <time.h>

int main()
{
    srand(time(0));
    //printf("%d",rand());
    int A[3][2];
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 2;j++)
            A[i][j] = rand() % 100;
    }
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 2;j++)
           printf("%d ", A[i][j]);
        printf("\n");
    }
    printf("\nEnter array size: ");
    int n;
    scanf_s("%d", &n);

    int* B = (int*)calloc(n, sizeof(int));
    if (B == NULL)
    {
        return -1;
    }
    for (int i = 0;i < n;i++)
        B[i] = (rand()%(2*n+1))-n;
    for (int i = 0;i < n;i++)
    {
        printf("%d ", B[i]);
    }
    free(B);
}
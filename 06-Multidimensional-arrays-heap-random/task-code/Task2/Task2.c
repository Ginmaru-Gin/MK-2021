#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(0));
    int a, b;
    scanf_s("%d %d", &a, &b);

    if (b >= a)
        return -1;

    int* A_arr = (int*)calloc(a, sizeof(int));
    if (A_arr == NULL)
        return -1;
    for (int i = 0;i < a;i++)
    {
        /*
        int x = (rand() % 61) - 30;
        while (x < 10 && x >=0 || x > -10 && x <= 0)
        {
            x = (rand() % 61) - 30;
        }
        */
        int sign = rand()%2;
        if (sign == 1)
            sign = -1;
        else
            sign = 1;

        A_arr[i] = sign * (rand() % 21) +10;
    }
    for (int i = 0;i < a;i++)
        printf("%d ", A_arr[i]);
    int* B_arr = (int*)calloc(b, sizeof(int));

    //int CountPast = 1;
    //int* TempArr = (int*)calloc(CountPast, sizeof(int));
    int* A_arr_StateReplay = (int*)calloc(a, sizeof(int));
    if (B_arr == NULL || A_arr_StateReplay == NULL)
    {
        return -1;
    }
    for (int i = 0;i < b;i++)
    {
        int isReplay = 0;
        int j;
        int x = rand() % a;
        while(A_arr_StateReplay[x] == 1)
            x = rand() % a;
        A_arr_StateReplay[x] = 1;
        B_arr[i] = A_arr[x];
    }
    printf("\n");
    for (int i = 0;i < b;i++)
        printf("%d ", B_arr[i]);
    free(A_arr_StateReplay);
    free(A_arr);
    free(B_arr);
}
#include <stdio.h>
#include <stdlib.h>

int main()
{
#define N 5
#define M 6
    int A[N][M];
    for (int i = 0; i < M * N; i++)
        (*A)[i] = 1;

    //int CountMultN = 0;
    //int CountMultM = 0;
    int index = M+1;
    int indexY = 1;
    for (int i = 0; i < M; i++)
        (*A)[i] = i+1;
    for (int i = 0; i < N; i++)
        (*A)[M * i] = i + 1;
    do
    {
        if (index % 6 == 0)
        {
            indexY++;
            index += 1;
        }
        else
        {
            (*A)[index] = A[0][index % M] * A[indexY][0];
            index++;
        }
    } while (index < M * N);
    int i = 0;
    do
    {
        if (i % 6 == 0)
        {
            printf("\n");
        }
        printf("%d ", (*A)[i]);
        i++;
    } while (i < M * N);
}
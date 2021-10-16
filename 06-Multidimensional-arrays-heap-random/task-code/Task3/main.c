#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 6
void SetValuesForMultTable(int arr[])
{
    //printf("%d", arr[5]);
    for (int i = 0; i < M; i++)
        arr[i] = i + 1;
        //(*arr)[i] = i + 1;
    for (int i = 0; i < N; i++)
        arr[i*M] = i + 1;
        //(*arr)[M * i] = i + 1;

}
void CreateMultTable(int arr[])
{
    int index = M + 1;
    int indexY = 1;

    do
    {
        if (index % 6 == 0)
        {
            indexY++;
            index += 1;
        }
        else
        {
            arr[index] = arr[index % M] * arr[indexY];
            index++;
        }
    } while (index < M * N);
}
void PrintMultTable(int arr[])
{
    int i = 0;
    do
    {
        if (i % 6 == 0)
        {
            printf("\n");
        }
        printf("%0*d", -3, arr[i]);
        i++;
    } while (i < M * N);
}
int main()
{
    //InitArray 
    int A[N][M];
    for (int i = 0; i < M * N; i++)
        (*A)[i] = 1;

    SetValuesForMultTable(&A);
    CreateMultTable(A);
    PrintMultTable(A);

    return 0;
}
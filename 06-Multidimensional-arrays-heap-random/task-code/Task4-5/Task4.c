#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define N 4
#define M 5
#define A -3
#define B 9
void PrintTwoDimArr(int Arr[N][M])
{
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%0*d ", -2, Arr[i][j]);
		}
		printf("\n");
	}
}
void InitAndPrintForTwoDimArr(int arr[N][M])
{
	srand(time(0));
	printf("Array:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			arr[i][j] = (rand() % (abs(A) + abs(B) + 1)) - abs(A);
			printf("%0*d", -4, arr[i][j]);
		}
		printf("\n");
	}
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void sort(int* arr, int size)
{
	for (int i = 0; i < size-1; i++)
	{
		for (int j = 0; j < size-i-1; j++)
		{
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}
}
void SwapRow(int arr1[N], int arr2[N])
{
	for (int col = 0; col < M; col++)
	{
		int temp = arr1[col];
		arr1[col] = arr2[col];
		arr2[col] = temp;
	}
}
void SortTwoDimArrayRow(int arr[N][M], int* FirstMinIndexRow, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (FirstMinIndexRow[j] == FirstMinIndexRow[j + 1])
			{
				for (int ColumnIndex = 1; ColumnIndex < M; ColumnIndex++)
				{
					if (arr[j][ColumnIndex] < arr[j+1][ColumnIndex])
					{
						FirstMinIndexRow[j] = arr[j][ColumnIndex];
						FirstMinIndexRow[j + 1] = arr[j][ColumnIndex + 1];
						SwapRow(&arr[j], &arr[j+1]);
						break;
						//swap(&FirstMinIndexRow[j], &FirstMinIndexRow[j + 1]);
					}
					else if (arr[j][ColumnIndex] > arr[j+1][ColumnIndex])
					{
						FirstMinIndexRow[j] = arr[j][ColumnIndex + 1];
						FirstMinIndexRow[j + 1] = arr[j][ColumnIndex];
						//SwapRow(&arr[j+1], &arr[j]);
						break;
						//swap(&FirstMinIndexRow[j+1], &FirstMinIndexRow[j]);
					}
				}
			}
			if (FirstMinIndexRow[j] < FirstMinIndexRow[j + 1])
			{
				for (int col = 0; col < M; col++)
				{
					int temp = arr[j][col];
					arr[j][col] = arr[j + 1][col];
					arr[j + 1][col] = temp;
				}
				swap(&FirstMinIndexRow[j], &FirstMinIndexRow[j + 1]);
			}
		}
	}
}
void SortForTwoDimArr(int Arr[N][M])
{
	for (int i = 0; i < N; i++)//Sort columns
		sort(&Arr[i][0], M);
	int RowIndex[N];
	for (int i = 0; i < N; i++)
		RowIndex[i] = Arr[i][0];
	SortTwoDimArrayRow(Arr, &RowIndex, N);
}
int main()
{
	int Arr[N][M] = { 0 };
	if(Arr == NULL)
		return -1;
	InitAndPrintForTwoDimArr(Arr);
	SortForTwoDimArr(Arr);
	PrintTwoDimArr(Arr);

	return 0;
}			
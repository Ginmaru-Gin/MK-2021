#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define N 4
#define M 5
#define A -3
#define B 9
//int** CreateTwoDimArray()
//{
//	int** arr = (int**)calloc(N, sizeof(int*));
//	if (arr == NULL)
//		return NULL;
//	for (int i = 0; i < N; i++)
//	{
//		arr[i] = (int*)calloc(M, sizeof(int));
//		if (arr[i] == NULL)
//			return NULL;
//	}
//	return arr;
//}
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
			//int sign = (rand() % 2) ? 1 : -1;
			//if (arr[i][j] == NULL)
			//	return NULL;
			arr[i][j] = (rand() % (abs(A) + abs(B) + 1)) - abs(A);
			printf("%0*d", -4, arr[i][j]);
		}
		printf("\n");
	}
}
int swap(int* a, int* b)
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
void SortWithTwoElements(int arr[N][M], int* SomeIndex, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (SomeIndex[j] < SomeIndex[j + 1])
			{
				//TODO: Change adress for pointer with long pointer
				/*int** a;
				int** b;
				a = &arr[j][0];
				b = &arr[j + 1][0];
				int** temp;
				temp = a;
				a = b;
				b = temp;*/
				//for(int i 
				/*
				int* temp = (*arr)[j*M];
				(*arr)[j*M] = (*arr)[j*M + 1];
				arr[j*M + 1][0] = &temp;
				*/
				for (int col = 0; col < M; col++)
				{
					int temp = arr[j][col];
					//printf("%d ", temp);
					arr[j][col] = arr[j + 1][col];
					arr[j + 1][col] = temp;
					//swap(arr[j][col], arr[j + 1][col]);
				}
				swap(&SomeIndex[j], &SomeIndex[j + 1]);
				//swap(&arr[j][0], &arr[j + 1][0]);
				//swap(&SomeIndex[j], &SomeIndex[j + 1]);
			}
		}
	}
}
void SortForTwoDimArr(int Arr[N][M])
{
	//printf("%d\n", Arr[3][0]);
	for (int i = 0; i < N; i++)//Sort columns
		sort(&Arr[i][0], M);
	PrintTwoDimArr(Arr);
	//printf("%d\n", Arr[3][0]);
	int RowIndex[N];
	for (int i = 0; i < N; i++)
		RowIndex[i] = Arr[i][0];
	//sort(&RowIndex, N);
	SortWithTwoElements(Arr, &RowIndex, N);
}
int main()
{
	//int** TwoDimArr = CreateTwoDimArray();
	int Arr[N][M] = { 0 };
	if(Arr == NULL)
		return -1;
	InitAndPrintForTwoDimArr(Arr);
	//printf("%d\n", TwoDimArr[2][2]);
	SortForTwoDimArr(Arr);
	PrintTwoDimArr(Arr);
	//printf("%d", TwoDimArr[2][2]);
	//printf("%d", TwoDimArr[0][0]);
	
}			
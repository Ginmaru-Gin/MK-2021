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
void sort(int** arr, int size)
{
	for (int i = size-1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}
}

void GlobalSortForTwoDimArr(int** Arr)
{
	for (int i = 0; i < N; i++)//Sort columns
		sort(Arr[i], M);

	int ArrayIndex[N];
	for (int i = 0; i < N; i++)
		ArrayIndex[i] = Arr[i][0];
	for (int i = 0; i < N; i++)
		sort(ArrayIndex[i], N);
	sort(sort())
}
int main()
{
	//int** TwoDimArr = CreateTwoDimArray();
	int Arr[N][M] = { 0 };
	if(Arr == NULL)
		return -1;
	InitAndPrintForTwoDimArr(Arr);
	//printf("%d\n", TwoDimArr[2][2]);
	GlobalSortForTwoDimArr(Arr);

	//printf("%d", TwoDimArr[2][2]);
	//printf("%d", TwoDimArr[0][0]);
	
}			
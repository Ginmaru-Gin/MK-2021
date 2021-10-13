#include <stdio.h>
#define N 4
#define M 5
#define A -3
#define B 9
int main()
{
	int arr[N][M];

	for(int i=0; i<M; i++)
		for (int j = 0; j < N; j++)
		{
			int sign = rand() % 2;
			if (sign % 2 == 0)
				sign = 1;
			else
				sign = -1;
			arr[i][j] = rand() % A;
		}
			A[i][j] = rand() 
}			
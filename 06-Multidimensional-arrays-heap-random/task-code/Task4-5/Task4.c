#include <stdio.h>
#include <math.h>
#include <time.h>
#define N 4
#define M 5
#define A -3
#define B 9
int main()
{
	srand(time(0));
	int arr[N][M];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int sign = (rand() % 2) ? 1 : -1;
			arr[i][j] = sign * ( (rand() % (abs(B) - abs(A) + 1))  + abs(A) );
		}
	}
		
}			
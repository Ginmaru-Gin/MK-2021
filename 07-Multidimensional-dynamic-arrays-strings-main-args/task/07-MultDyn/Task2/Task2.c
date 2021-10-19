#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** CreateTwoDimArray(int N, int M)
{
	char** str = (char**)calloc(N, sizeof(char*));
	if (str == NULL)
		return NULL;
	for (int i = 0; i < N; i++)
	{
		int temp = M + 1;
		str[i] = (char*)calloc(temp, sizeof(char));
		if (str[i] == NULL)
			return NULL;
	}
	return str;
}
void ReverseArray(char** str,int N)
{
	int top = strlen(str[N]);
	top -= 1;
	for (int down = 0; down < top; down++, top--)
	{
		char temp;
		temp = str[N][down];
		str[N][down] = str[N][top];
		str[N][top] = temp;
	}
}
int InputTwoDimArrayWithReverse(char** str, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		int SizeStr = M + 1;
		//int temp = (unsigned)_countof(str[i]);
		if (scanf_s("%8s", str[i], SizeStr) != 1)
			return -1;
		ReverseArray(str,i);
	}
	return 0;
}
void OutputTwoDimArray(char** str, int N)
{
	printf_s("%d string were entered:", N);
	printf_s("\n");
	for (int i = 0; i < N; i++)
	{
		int index = 0;
		while (str[i][index] != '\0')
		{
			printf_s("%c", str[i][index]);
			index++;
		}
		printf_s(" (len = %d)", (int)strlen(str[i]));
		printf_s("\n");
	}
}
void FreeTwoDimArray(char** str, int N)
{
	for (int i = 0; i < N; i++)
	{
		free(str[i]);
	}
	free(str);
}
//#define DEBUG 
int main(int argc, char* argv[])
{
	int N, M;
#ifndef DEBUG 
	if (argc != 3)
	{
		printf_s("Need Two Value");
		return -1;
	}
	N = atoi(argv[1]);
	M = atoi(argv[2]);
#else
	scanf_s("%d%d", &N, &M);
#endif
	char** str = CreateTwoDimArray(N, M);
	if (str == NULL)
	{
		//printf_s("%d %d", N, M);
		printf_s("error");
		return -1;
	}
	if(InputTwoDimArrayWithReverse(str, N, M) != 0)
		return -1;
	OutputTwoDimArray(str, N);
	FreeTwoDimArray(str, N);

	return 0;
}
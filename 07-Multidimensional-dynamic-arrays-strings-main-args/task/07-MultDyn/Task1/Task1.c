#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char** CreateTwoDimArray(int N, int M)
{
	char** str = (char**)calloc(N, sizeof(char*));
	if (str == NULL)
		return NULL;
	for (int i = 0; i < N; i++)
	{
		int temp = M+1;
		str[i] = (char*)calloc(temp, sizeof(char));
		if (str[i] == NULL)
			return NULL;
	}
	return str;
}
int InputTwoDimArray(char** str, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		//int temp = (unsigned)_countof(str[i]);
		if (scanf_s("%8s", str[i], M + 1) != 1)
			return -1;
	}
	return 0;
}
void OutputTwoDimArray(char** str, int N)
{
	printf("%d string were entered:", N);
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		int index = 0;
		while (str[i][index] != '\0')
		{
			printf("%c", str[i][index]);
			index++;
		}
		printf(" (len = %d)", (int)strlen(str[i]));
		printf("\n");
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
int main()
{
	int N, M;
	if(scanf_s("%d%d", &N, &M) != 2)
		return -1;
	char** str = CreateTwoDimArray(N, M);
	if (str == NULL)
		return -1;
	if(InputTwoDimArray(str, N, M) != 0)
		return -1;
	OutputTwoDimArray(str, N);
	FreeTwoDimArray(str, N);
	return 0;
}
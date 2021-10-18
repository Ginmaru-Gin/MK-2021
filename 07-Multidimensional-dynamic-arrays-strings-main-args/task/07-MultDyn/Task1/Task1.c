#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char** CreateTwoDimArray(int N, int M)
{
	char** str = (char**)calloc(N, sizeof(char*));
	if (str == NULL)
		return -1;
	for (int i = 0; i < N; i++)
	{
		str[i] = (char*)calloc(M + 1, sizeof(char));
		if (str[i] == NULL)
			return -1;
	}
	return str;
}
int main()
{
	int N, M;
	if(scanf_s("%d%d", &N, &M) != 2)
		return -1;
	char** str = CreateTwoDimArray(N, M);

	for (int i = 0; i < N; i++)
	{
		//int temp = (unsigned)_countof(str[i]);
		if (scanf_s("%8s", str[i], M+1) != 1)
			return -1;
	}

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
		printf(" (len = %d)", strlen(str[i]));
		printf("\n");
	}
}
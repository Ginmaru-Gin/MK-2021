#include <stdio.h>
#include <stdlib.h>

#define FILE_INPUT "input-file.txt"
#define FILE_OUTPUT "output-file.txt"

int OpenFiles(FILE* input, FILE* output)
{
	if (fopen_s(&input, FILE_INPUT, "r+") != 0)
	{
		perror("Error in OpenFiles");
		return -1;
	}
	if (fopen_s(&output, FILE_OUTPUT, "r+") != 0)
	{
		perror("Error in OpenFiles");
		return -1;
	}
	return 0;
}

int GetValue(FILE* input, int* pValue)
{
	if (fscanf_s(input, "%d", pValue) != 1)
	{
		perror("Error in GetValue");
		return -1;
	}
	return 0;
}
int main()
{
	if (sizeof(int) != 4)
	{
		printf("Incompatibility with the OS");
		return -1;
	}
	FILE *input = NULL, *output = NULL;

	if (OpenFiles(input, output) != 0)
		return -1;
	
	int InputValue = 0;
	if(GetValue(input, &InputValue) != 0)
		return -1;


	return 0;
}
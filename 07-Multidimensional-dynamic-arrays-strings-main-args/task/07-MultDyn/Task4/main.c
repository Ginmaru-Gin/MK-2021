#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COUNT_STRING 100
FILE* input;
int CreateArrayOfPoints(int** ArrayOfPoints)
{
	*ArrayOfPoints = (int*)calloc(1, sizeof(int));
	if (*ArrayOfPoints == NULL)
		return NULL;
	return 1;
}
int UpdateSizeArrayOfPoints(int** Array, int Size)
{
	int* OldBuffer;
	OldBuffer = *Array;
	int size = _msize(*Array);
	if ((*Array = (int*)realloc(OldBuffer, size + sizeof(int))) == NULL)
	{
		free(OldBuffer);
		return NULL;
	}
	if (*Array == NULL)
		return NULL;
	return 1;
}
char** ReadFileInArray(int* SizeArrOfPoints)
{
	int* ArrayOfPoints;
	if (CreateArrayOfPoints(&ArrayOfPoints) == NULL)
		return -1;

	int IndexArrayOfPoints = 0;
	while (fscanf_s(input, "%d", &ArrayOfPoints[IndexArrayOfPoints]) != EOF)
	{
		IndexArrayOfPoints++;
		if (UpdateSizeArrayOfPoints(&ArrayOfPoints, IndexArrayOfPoints) == NULL)
			return -1;
	}
	*SizeArrOfPoints = IndexArrayOfPoints;
	return ArrayOfPoints;
}
char* FindOutFileName(char** argv)
{
	char* FileName = (char*)calloc(FILENAME_MAX, sizeof(char));
	if (FileName == NULL)
		return NULL;
	int LengthFileName = strlen(argv[1]);
	for (int i = 0; i < LengthFileName; ++i)
	{
		FileName[i] = argv[1][i];
	}
	return FileName;
}
int OpenFile(char** argv)
{
	char* FileName = FindOutFileName(argv);
	if (FileName == NULL)
		return -1;
	if (fopen_s(&input, FileName, "r+") != 0)
	{
		printf_s("File Not exist\n");
		return -1;
	}
	if (input == NULL)
		return -1;
	return 0;
}
int main(int argc, char** argv)
{
	int SizeOfArray = 0;
	char** StrEncrypt = (char**)calloc(MAX_COUNT_STRING, sizeof(char*));
	if (OpenFile(argv) == -1)
		return -1;
	StrEncrypt = ReadFileInArray(&SizeOfArray);
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_FILE_NAME 101
//#define FILE_NAME "points.txt"

int* CreateAndEnterArrayOfRatio(int NumberArg, char** argv)
{
	int* ArrayOfRatio = (int*)calloc(NumberArg, sizeof(int));
	if (ArrayOfRatio == NULL)
		return -1;
	for (int i = 1; i <= NumberArg - 1; i++)
	{
		ArrayOfRatio[i - 1] = atoi(argv[i]);
	}
	return ArrayOfRatio;
}
char* FindOutFileName(char** argv, int NumberArg)
{
	char* FileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	if (FileName == NULL)
		return NULL;
	int LengthFileName = strlen(argv[NumberArg]);
	for (int i = 0; i < LengthFileName; ++i)
	{
		FileName[i] = argv[NumberArg][i];
	}
	return FileName;
}
FILE* input;
int OpenFile(char** argv, int NumberArg)
{
	char* FileName = FindOutFileName(argv, NumberArg);
	if(FileName == NULL)
		return -1;
	if (fopen_s(&input, FileName, "r+") != 0)
	{
		printf_s("File Not exist\n");
		perror("This: ");
		return -1;
	}
	if (input == NULL)
		return -1;
	perror("This: ");
	return 0;
}
int CreateArrayOfPoints(int** ArrayOfPoints)
{
	*ArrayOfPoints = (int*)calloc(1, sizeof(int));
	_msize(*ArrayOfPoints);
	if (*ArrayOfPoints == NULL)
		return NULL;
	return 1;
}
int UpdateSizeArrayOfPoints(int** Array, int Size)
{
	int* OldBuffer;
	OldBuffer = *Array;
	//int temp = Size + 1;
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
int* ReadFileInArray(int* PIndexArrayOfPoints)
{
	int* ArrayOfPoints;
	if(CreateArrayOfPoints(&ArrayOfPoints) == NULL)
		return -1;
	int IndexArrayOfPoints = 0;
	while (fscanf_s(input, "%d", &ArrayOfPoints[IndexArrayOfPoints]) != EOF)
	{
		_msize(ArrayOfPoints);
		IndexArrayOfPoints++;
		if(UpdateSizeArrayOfPoints(&ArrayOfPoints, IndexArrayOfPoints) == NULL)
			return -1;
	}
	*PIndexArrayOfPoints = IndexArrayOfPoints;
	return ArrayOfPoints;
}
int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("NoValue");
		return -1;
	}

	int* ArrayOfRatio = NULL;
	int* ArrayOfPoints = NULL;
	int IndexArrayOfPoints = 0;
	int NumberArg = argc - 1;

	ArrayOfRatio = CreateAndEnterArrayOfRatio(NumberArg-1, argv);
	if (ArrayOfRatio == NULL)
		return -1;
	if(OpenFile(argv, NumberArg) == -1)
		return -1;
	if((ArrayOfPoints = ReadFileInArray(&IndexArrayOfPoints)) == NULL)
		return -1;
	for (int i = 0; i < IndexArrayOfPoints; i++)
		printf("%d ", ArrayOfPoints[i]);

	free(ArrayOfPoints);
	if (input != NULL)
		fclose(input);
}
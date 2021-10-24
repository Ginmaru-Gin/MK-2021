#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_NAME 101
FILE* input;
//#define FILE_NAME "points.txt"

int* CreateAndEnterArrayOfRatio(int NumberOfRatio, char** argv)
{
	int* ArrayOfRatio = (int*)calloc(NumberOfRatio, sizeof(int));
	if (ArrayOfRatio == NULL)
		return -1;
	for (int i = 1; i <= NumberOfRatio; i++)
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
int OpenFile(char** argv, int NumberArg)
{
	char* FileName = FindOutFileName(argv, NumberArg);
	if(FileName == NULL)
		return -1;
	if (fopen_s(&input, FileName, "r+") != 0)
	{
		printf_s("File Not exist\n");
		perror("This ");
		return -1;
	}
	if (input == NULL)
		return -1;
	//perror("This: ");
	return 0;
}
int* CreateArrayOfPoints()
{
	int* ArrayOfPoints = NULL;
	ArrayOfPoints = (int*)calloc(1, sizeof(int));
	if (ArrayOfPoints == NULL)
		return -1;
	return ArrayOfPoints;
}
int* UpdateSizeArrayOfPoints(int* Array, int Size)
{
	int* OldBuffer;
	OldBuffer = Array;
	int temp = Size + 1;
	if ((Array = realloc(Array, temp * sizeof(int))) == NULL)
	{
		free(OldBuffer);
		return NULL;
	}
	if (Array == NULL)
		return NULL;
	return Array;
}
int* ReadFileInArray(int* ArrayOfPoints,int* SizeArrOfPoints)
{
	while (fscanf_s(input, "%d", &ArrayOfPoints[*SizeArrOfPoints]) != EOF)
	{
		*SizeArrOfPoints = *SizeArrOfPoints + 1;
		if ((ArrayOfPoints = UpdateSizeArrayOfPoints(ArrayOfPoints, *SizeArrOfPoints)) == NULL)
			return -1;
	}
	return ArrayOfPoints;
}
void PrintCorrespondToRatio(int x, int y, int IsCorrespondToRatio)
{
	if (IsCorrespondToRatio)
	{
		printf("%d %d: YES\n", x, y);
	}
	else
	{
		printf("%d %d: NO\n", x, y);
	}
}
void CheckPointsCorrespondToRatioOfStraightLine(int* ArrOfPoints, int* ArrOfRatio, int SizeArrPoint, int SizeArrRatio)
{
	printf("%d Points:\n", SizeArrPoint / 2);
	int isCorrespondToRatio = 0;
	for (int j = 0; j < SizeArrPoint - 1; j += 2)
	{
		isCorrespondToRatio = 0;
		for (int i = 0; i < SizeArrRatio-1; i++)
		{
			if (ArrOfPoints[j] * ArrOfRatio[i] == ArrOfPoints[j+1])
			{
				isCorrespondToRatio = 1;
				break;
			}
		}
		PrintCorrespondToRatio(ArrOfPoints[j], ArrOfPoints[j+1], isCorrespondToRatio);
	}
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
	int NumberArg = argc - 1;
	int SizeArrayOfPoints = 0;

	if ((ArrayOfRatio = CreateAndEnterArrayOfRatio((NumberArg-1), argv)) == -1)
		return -1;
	if ((ArrayOfPoints = CreateArrayOfPoints()) == -1)
		return -1;

	if (OpenFile(argv, NumberArg) == -1)
		return -1;
	if ((ArrayOfPoints = ReadFileInArray(ArrayOfPoints,&SizeArrayOfPoints)) == -1)
		return -1;

	CheckPointsCorrespondToRatioOfStraightLine(ArrayOfPoints, ArrayOfRatio, SizeArrayOfPoints, NumberArg);

	free(ArrayOfPoints);
	free(ArrayOfRatio);
	if (input != NULL)
		fclose(input);

	return 0;
}
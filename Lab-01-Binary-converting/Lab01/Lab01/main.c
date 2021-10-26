#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <locale.h>
#define SIZE_NUMBEROFBITFOR4BYTE 32
#define SIZE_FORREADINT 12
int GetValue(FILE* input,int* pValue)
{
	errno = 0;
	char str[SIZE_FORREADINT];
	//for(int i = 0; i < )
	if(fgets(str, SIZE_FORREADINT, input) == NULL)
		return -1;
	if(feof(input) == 0)
		return -1;
	for(int i = 0; str[i] != '\0' || i == SIZE_FORREADINT - 1; i++)
	{
		if(isalpha(str[i]))
			return -1;
	}
	/*if(str[0] == '0' && str[1] == '\0')
	{
		*pValue = 0;
	}*/
	*pValue = atoi(str);
	/*if (*pValue == 0)
	{
		printf_s("Error in GetValue, impossible convertate to int");
		return -1;
	}*/
	if (errno == ERANGE)
	{
		perror("Error in GetValue problem with input value");
		return -1;
	}
	
	return 0;
}
char* FindOutFileName()
{
	char* FileName = (char*)calloc(FILENAME_MAX, sizeof(char));
	if (FileName == NULL)
		return NULL;
	if(scanf_s("%s", FileName, FILENAME_MAX) != 1)
		return NULL;
	return FileName;
}
int OpenFiles(FILE** input, FILE** output)
{
	printf_s("Enter input filename: \n");
	char* FileNameInput = FindOutFileName();
	if (FileNameInput == NULL)
		return -1;
	printf_s("Enter output filename: \n");
	char* FileNameOutput = FindOutFileName();
	if (FileNameOutput == NULL)
		return -1;
	if (fopen_s(input, FileNameInput, "r+") != 0)
	{
		free(FileNameInput);
		perror("Error in OpenFile problem with FileNameInput");
		return -1;
	}
	if (fopen_s(output, FileNameOutput, "r+") != 0)
	{
		free(FileNameInput);
		free(FileNameOutput);
		perror("Error in OpenFile problem with FileNameOutput");
		return -1;
	}
	free(FileNameInput);
	free(FileNameOutput);
	if (input == NULL || output == NULL)
		return -1;
	return 0;
}
int SumOfEachDigitInValue(int Number)
{
	int x = abs(Number);
	int sum = 0;
	while (x > 0)
	{
		sum += x % 10;
		x /= 10;
	}
	return sum;
}
void BinaryRepresent(int Value, int** str)
{
	int count = 0;
	int x = abs(Value);
	while (x > 0)
	{
		(*str)[31 - count] = x % 2;
		x /= 2;
		count++;
	}
}
void InverseBinary(int** str)
{
	for (int i = 0; i < SIZE_NUMBEROFBITFOR4BYTE; i++)
	{
		if ((*str)[i] == 0)
			(*str)[i] = 1;
		else
			(*str)[i] = 0;
	}
}
void AddOneToBinary(int** str)
{
	//int a = 1;
	int count = SIZE_NUMBEROFBITFOR4BYTE - 1;
	//while (count >= 0)
	//{
	for (int count = SIZE_NUMBEROFBITFOR4BYTE - 1; count >= 0; count--)
	{
		if ((*str)[count] == 1)
			(*str)[count] = (1 + (*str)[count]) % 2;
		else
		{
			(*str)[count] = 1;
			break;
		}
	}
		/*if (1 + (*str)[count] == 1)
		{
			(*str)[count] = 1;
			break;
		}
		else if (1 + str[count] > 1)
		{
			(*str)[count] = (1 + (*str)[count]) % 2;
		}
		else
		{
			(*str)[count] = 0;
			break;
		}*/
		//count--;
}

void PrintBinary(int* str)
{
	for (int i = 0, count = 1; i < SIZE_NUMBEROFBITFOR4BYTE; count++)
	{
		if (count % 5 == 0)
			printf_s(" ");
		else
		{
			printf_s("%d", str[i]);
			i++;
		}
	}
}
int* NumberInBinary(int Value)
{
	int* ArrayForBinary = (int*)calloc(SIZE_NUMBEROFBITFOR4BYTE, sizeof(int));
	if (ArrayForBinary == NULL)
		return NULL;
	if (Value >= 0)
	{
		BinaryRepresent(Value, &ArrayForBinary);
	}
	else
	{
		BinaryRepresent(Value, &ArrayForBinary);
		InverseBinary(&ArrayForBinary);
		AddOneToBinary(&ArrayForBinary);
	}
	return ArrayForBinary;
}
int* WriteToOutputFile(FILE* output, int* BinaryValue)
{
	for (int i = 0, count = 1; i < SIZE_NUMBEROFBITFOR4BYTE; count++)
	{
		if (count % 5 == 0)
		{
			if (fprintf_s(output, " ") != 1)
			{
				printf_s("Error in WriteToOutputFile with printf");
				return -1;
			}
		}
		else
		{
			if (fprintf_s(output, "%d", BinaryValue[i]) != 1)
			{
				printf_s("Error in WriteToOutputFile with printf");
				return -1;
			}
			i++;
		}
	
	}
	return 0;
}
int main()
{
	FILE* input = NULL, *output = NULL;
	/*if (sizeof(int) != 4)
	{
		printf("Incompatibility with the OS");
		return -1;
	}*/
	if (OpenFiles(&input, &output) != 0)
	{
		_fcloseall();
		return -1;
	}
	
	int InputValue = 0;
	if (GetValue(input, &InputValue) != 0)
	{
		_fcloseall();
		return -1;
	}

	printf("%d\n", SumOfEachDigitInValue(InputValue));

	int* BinaryValue = NumberInBinary(InputValue);
	if (BinaryValue == NULL)
	{
		_fcloseall();
		return -1;
	}

	PrintBinary(BinaryValue);

	if (WriteToOutputFile(output, BinaryValue) == -1)
	{
		free(BinaryValue);
		_fcloseall();
		return -1;
	}
	free(BinaryValue);
	_fcloseall();
	return 0;
}
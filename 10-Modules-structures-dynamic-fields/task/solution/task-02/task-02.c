/*
Аргументом командной строки передаётся имя файла, в начало которого
программа добавляет строку, содержащую единственное число - количество
строк в этом файле (с учётом новой добавленной строки).
*/
#include "myErrors.h"

#include <ctype.h>
#include <io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// генерирует случайную строку по заданному алфавиту и диапазону длины
errno_t getRandomString(char** buf, char* alphabet, size_t minLength, size_t maxLength);
// функция подсчета строк в файле
errno_t countLinesInFile(size_t* linesCounter, char* fileName);
// функция, добавляющая строку в начало файла
errno_t addLineToFileBegin(char* fileName, char* line);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        checkError(ERR_WRONG_CMD_ARGS);
    }
    size_t linesCount;
    checkError(countLinesInFile(&linesCount, argv[1]));
    ++linesCount;
    size_t bufferCount = (size_t)log10((double)linesCount) + 2;
    char* linesCountStr = (char*)malloc(sizeof(char) * bufferCount);
    if (!linesCountStr) {
        checkError(errno);
    }
    if (_itoa_s((int)linesCount, linesCountStr, bufferCount, 10)) {
        checkError(errno);
    }

    checkError(addLineToFileBegin(argv[1], linesCountStr));
    printf_s("DONE!\n");

    system("pause");
    return EXIT_SUCCESS;
}

errno_t getRandomString(char** buf, char* alphabet, size_t minLength, size_t maxLength) {
    // статические поля сохраняют свои значения между вызовами функции
    // поэтому при первом вызове функции seed станет равным 1
    if (minLength > maxLength) return ERR_WRONG_FUNC_ARGS;

    static char seed = 0;
    if (!seed) {
        srand((unsigned)(time(NULL)));
        seed = 1;
    }

    size_t length = rand() % (maxLength - minLength + 1) + minLength;
    size_t alphLength = strnlen_s(alphabet, _MAX_FNAME);
    if (*buf != NULL) free(*buf);
    *buf = (char*)malloc(sizeof(char) * (length + 1));
    if (!*buf) {
        return errno;
    }
    (*buf)[length] = '\0';
    for (size_t i = 0; i < length; ++i) {
        (*buf)[i] = alphabet[rand() % alphLength];
    }
    return ERR_SUCCESS;
}

errno_t countLinesInFile(size_t* linesCounter, char* fileName) {
    FILE* file;
    if (fopen_s(&file, fileName, "r")) {
        return errno;
    }
    *linesCounter = 1;
    while (!feof(file)) {
        if (fgetc(file) == '\n')
            ++(*linesCounter);
    }
    fclose(file);
    return ERR_SUCCESS;
}

errno_t addLineToFileBegin(char* fileName, char* line) {
    /*
    Мы не можем "дописывать" что-либо в начало файла.
    Одним из наиболее простых и приемлемых способов решения данной задачи
    является создание временного файла, в начало которого будет записана строка,
    которую необходимо добавить в начало файла, а затем всё содержимое исходного
    файла копируется во временный файл. После этого исходный файл удаляется, а
    временный файл переименовывается в исходный.
    */
    errno_t error = ERR_SUCCESS;
    char* tmpFileName = NULL;
    do {
        // генерируем случайные имена для временного файла до тех пор,
        // пока не получим такое, что файла с таким именем не существует
        // (не лучший вариант решения такой задачи, но остановимся на нём)
        if (tmpFileName != NULL) free(tmpFileName);
        error = getRandomString(&tmpFileName, fileName, 5, 10);
        if (error != ERR_SUCCESS)
            return error;
    } while (!_access(tmpFileName, 0));

    FILE* file, * tmpFile;
    if (fopen_s(&file, fileName, "r") || fopen_s(&tmpFile, tmpFileName, "w")) {
        _fcloseall();
        return errno;
    }

    fprintf_s(tmpFile, "%s\n", line);
    char ch = 0;
    while ((ch = fgetc(file)) != EOF) {
        fputc(ch, tmpFile);
    }

    fclose(file);
    fclose(tmpFile);
    // данные записаны во временный файл, удаляем исходный 
    if (remove(fileName)) {
        remove(tmpFileName);
        return errno;
    }
    // переименовываем временный файл
    if (rename(tmpFileName, fileName)) {
        return errno;
    }

    return ERR_SUCCESS;
}

/*
Реализуйте:
 - функцию, которая инвертирует регистр букв в передаваемой ей строке
 - функцию, которая последовательность любых пробельных символов заменяет одним пробелом

Напишите программу, которая принимает имя файла и изменяет его содержимое,
обрабатывая функциями, описанными выше.
*/
#include "myErrors.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 100
#define BUF_SIZE (BUF_LENGTH + 1)

errno_t invertLettersCase(char* str, char** resultStr);
errno_t shrinkSpaces(char* str, char** resultStrPtr);

main(void) {
    errno_t error = ERR_SUCCESS;
    char buf[BUF_SIZE];
    printf_s("Enter a string (max length %d):\n", BUF_SIZE - 1);
    if (gets_s(buf, BUF_SIZE) == NULL) {
        checkError(ferror(stdin));
    }
    char* invertedCaseString, * shrinkedSpacesString, * fixedString;
    checkError(invertLettersCase(buf, &invertedCaseString));
    checkError(shrinkSpaces(buf, &shrinkedSpacesString));
    checkError(shrinkSpaces(invertedCaseString, &fixedString));
    printf_s("Inverted: %s\nShrinked: %s\nCombo: %s\n", invertedCaseString, shrinkedSpacesString, fixedString);

    system("pause");
    return EXIT_SUCCESS;
}

errno_t invertLettersCase(char* str, char** resultStrPtr) {
    size_t length = strlen(str);
    *resultStrPtr = (char*)malloc(sizeof(char) * (length + 1));
    if (!*resultStrPtr) {
        return errno;
    }
    (*resultStrPtr)[length] = '\0';
    char* ptr = str, * newPtr = *resultStrPtr;
    while (*ptr) {
        if (isupper(*ptr))
            *newPtr = tolower(*ptr);
        else
            *newPtr = toupper(*ptr);

        ++ptr;
        ++newPtr;
    }
    return ERR_SUCCESS;
}

errno_t shrinkSpaces(char* str, char** resultStrPtr) {
    size_t newLength = 0;
    char* ptr = str;
    while (*ptr) {
        ++ptr;
        ++newLength;
        if (isspace(*ptr)) {
            ++newLength;
            do ++ptr;
            while (isspace(*ptr));
        }
    }
    *resultStrPtr = (char*)malloc(sizeof(char) * (newLength + 1));
    if (!*resultStrPtr) {
        return errno;
    }
    (*resultStrPtr)[newLength] = '\0';
    ptr = str;
    char* newPtr = *resultStrPtr;
    while (*ptr) {
        if (isspace(*ptr)) {
            *newPtr = ' ';
            do ++ptr;
            while (isspace(*ptr));
        }
        else {
            *newPtr = *ptr;
            ++ptr;
        }
        ++newPtr;
    }
    return ERR_SUCCESS;
}
/*
Аргументом командной строки передаётся строка A.

На стандартный ввод поочерёдно подаются строки B.

Программа для каждой строки B выводит ответ на вопрос: можно ли из символов
строки A получить строку B.

Программа завершает свою работу, когда B - пустая строка.

Гарантируется, что длина строки B не превосходит длину строки A.
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOLS_COUNT (UCHAR_MAX + 1)
#define SYMBOLS_ARRAY_SIZE (SYMBOLS_COUNT * sizeof(size_t))

// будем в массиве хранить количество встреченных в строке символов
// индекс в массиве соответствует коду символа в таблице ASCII

// массив для строки A
size_t symbols[SYMBOLS_COUNT];
// массив для строки B
size_t symbolsCopy[SYMBOLS_COUNT];

// эта функция будет заполнять массив для строки A
void fillInSymbols(char* str);

// а эта будет заполнять массив для строки B
// и затем сверять значения в двух массивах для получения ответа
bool checkString(char* str);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf_s(stderr, "ERROR: wrong number of arguments");
        return -1;
    }
    size_t bufSize = strlen(argv[1]) + 1;
    char* str = malloc(sizeof(char) * bufSize);
    if (!str) {
        perror("ERROR: couldn't alloc memory");
        exit(errno);
    }

    fillInSymbols(argv[1]);

    do {
        printf_s("Enter a string (empty string to exit):\n");
    } while (gets_s(str, bufSize) &&
        strlen(str) > 0 &&
        printf_s("%s\n\n", checkString(str) ? "True!" : "False!"));
    printf_s("Goodbye!\n");

    free(str);

    system("pause");
    return 0;
}

void fillInSymbols(char* str) {
    size_t length = strlen(str);
    for (size_t i = 0; i < length; ++i) ++symbols[(unsigned char)str[i]];
}

bool checkString(char* str) {
    if (memcpy_s(symbolsCopy, SYMBOLS_ARRAY_SIZE, symbols, SYMBOLS_ARRAY_SIZE)) {
        perror("ERROR: problem's occured on data copying by memcpy_s");
        exit(errno);
    }
    size_t length = strlen(str);
    for (size_t i = 0; i < length; ++i) {
        // если в строке B символ встретился больше раз, чем в строке A
        // то строка B не может быть составлена из символов строки A
        if (symbolsCopy[(unsigned char)str[i]] == 0) return false;
        --symbolsCopy[(unsigned char)str[i]];
    }

    return true;
}

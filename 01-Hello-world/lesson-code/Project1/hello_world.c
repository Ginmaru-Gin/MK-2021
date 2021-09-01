//msdn -- microsoft software developer network
#include <stdio.h> // standart input/output
#include <Windows.h> // for system("pause")
#include <locale.h> // for setlocale()

// int -- целочисленный
// double float -- вещественные
// char -- целочисленный
// no bool -> use 1 as True and 0 as False

int main(void) {
    for (int i = 0; i < 10; ++i) {
        // ...
    }
    setlocale(LC_ALL, "ru-RU");
    int var; // definition
    var = 2;
    int number = 156; // initialization
    char character = 'S';
    printf("Привет мир!\n");
    printf("%cHello ", character);
    printf("world %d(1) %d(2)", var, number);
    printf("\n");
    system("pause");
    return 0;
}
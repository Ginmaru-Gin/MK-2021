#include <stdio.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "ru-RU");

    // ���� �����
    int number = 0;
    printf_s("Enter an integer: ");
    if (!scanf_s("%d", &number)) {
        printf_s("ERROR: wrong input, exit with code 1");
        return 1;
    }

    // ...

    return 0;
}
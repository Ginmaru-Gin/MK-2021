/*
Написать калькулятор для комплексных чисел с использованием структур.
*/
#include <stdio.h>
#include <stdlib.h>

// само комплексное число представим в виде структуры
struct Complex {
    double re, im;
};

// реализуем каждую операцию в отдельной функции
void complexSum(struct Complex* first, struct Complex* second, struct Complex* result);
void complexSub(struct Complex* first, struct Complex* second, struct Complex* result);
void complexMult(struct Complex* first, struct Complex* second, struct Complex* result);
// а также добавим функцию печати комплексного числа в консоли
void printComplex(struct Complex* number);

int main(void) {
    struct Complex first, second, result;
    char operation;
    printf_s("Enter an expression: ");
    scanf_s("(%lf,%lf) %c (%lf,%lf)", &first.re, &first.im, &operation, 1, &second.re, &second.im);

    switch (operation) {
    case '+':
        complexSum(&first, &second, &result);
        break;
    case '-':
        complexSub(&first, &second, &result);
        break;
    case '*':
        complexMult(&first, &second, &result);
        break;
    default:
        printf_s("ERROR: unknown operation\nEXIT WITH ERROR CODE 1");
        return 1;
    }
    printComplex(&result);
    printf_s("\n");

    system("pause");
    return 0;
}

void complexSum(struct Complex* first, struct Complex* second, struct Complex* result) {
    result->re = first->re + second->re;
    result->im = first->im + second->im;
}

void complexSub(struct Complex* first, struct Complex* second, struct Complex* result) {
    result->re = first->re + second->re;
    result->im = first->im + second->im;
}

void complexMult(struct Complex* first, struct Complex* second, struct Complex* result) {
    result->re = first->re * second->re - first->im * second->im;
    result->im = first->re * second->im + second->re * first->im;
}

void printComplex(struct Complex* number) {
    printf_s("(%g,%g)", number->re, number->im);
}
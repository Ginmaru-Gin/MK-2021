/*
Написать рекурсивную функцию, принимающую единственный аргумент - число N - и
возвращающую N-ое число в последовательности Фибоначчи.
Напишите программу, демонстрирующую работу этой функции.
*/
#include <stdio.h>
#include <stdlib.h>

unsigned long long fib(unsigned N) {
    if (N == 1) return 0;
    if (N == 2) return 1;
    return fib(N - 1) + fib(N - 2);
}

int main(void) {
    printf_s("Enter a positive number: ");
    unsigned number = 0;
    scanf_s("%u", &number);
    printf_s("Fib(%u) = %llu\n", number, fib(number));

    system("pause");
    return 0;
}
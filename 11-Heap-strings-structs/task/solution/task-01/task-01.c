/*
Определение 1. n!!…! = n(n−k)(n−2k)…(n mod k), если n не делится на k;
n!!…! = n(n−k)(n−2k)…k, если n делится на k (знаков ! в обоих случаях k штук).
Определение 2. X mod Y — остаток от деления X на Y.

Например, 10 mod 3 = 1; 3! = 3·2·1; 10!!! = 10·7·4·1.

Мы по заданным n и k смогли вычислить значение выражения из определения 1. А вам слабо?

Исходные данные
В единственной строке сначала дано целое число n, 1 ≤ n ≤ 10, затем ровно один пробел, затем k восклицательных знаков, 1 ≤ k ≤ 20.

Результат
Выведите одно число — n!!…!
*/
#include <stdio.h>
#include <string.h>

#define BUF_LENGTH 20
#define BUF_SIZE (BUF_LENGTH + 1)

int main(void) {
    char buf[BUF_SIZE];
    int result = 1, number = 0;

    scanf_s("%d%s", &number, buf, BUF_SIZE);
    // "шаг уменьшения" числа равен количеству восклицательных знаков,
    // т.е. равен длине строки buf
    int decreaseStep = (int)strlen(buf);

    // по заданному правилу считаем ответ
    while (number > 0) {
        result *= number;
        number -= decreaseStep;
    }
    printf_s("%d\n", result);

    return 0;
}
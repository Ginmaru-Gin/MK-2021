#include <stdio.h>
#include <locale.h>

int main(void) {
    // синтаксис функции scanf_s() похож на синтаксис printf_s(),
    // используются те же модификаторы для различных типов переменных
    // основное их отличие в том, что в аргументах функции scanf_s()
    // необходимо передавать не переменную, а её адрес в памяти,
    // который мы можем получить используя унарный оператор &
    int age;
    float pi;
    double e;
    printf_s("Enter your age: ");
    scanf_s("%d", &age); // iVar -- переменная, а &iVar -- адрес этой переменной
    printf_s("Enter Pi and Exp value: ");
    scanf_s("%f%lf", &pi, &e);
    printf_s("So, your age is %d and pi value is %f and e = %lf!\n", age, pi, e);

    system("pause");
    return 0;
}

/*
Опишите структуру, представляющую точку на плоскости, а также некоторые
функции для неё (по своему усмотрению). Реализуйте структуру данных стек,
предназначенную для хранения этих точек. Используйте предоставленный шаблон.

Ваш стек должен быть организован отдельным модулем.

Напишите программу с понятным пользовательским интерфейсом, в которой вы используете
этот модуль, и которая наглядно демонстрирует его функционал.
*/
#include "myErrors.h"
#include "PointsStack.h"

#include <stdlib.h>

int main(void) {
    errno_t error = ERR_SUCCESS;
    Stack* stack;
    checkError(stackNew(&stack));
    printf_s("Stack is %sempty\n", stackIsEmpty(stack) ? "" : "not ");
    system("pause");

    Point point = { 4, 6 };
    checkError(stackPush(stack, &point));
    printf_s("Stack is %sempty\n", stackIsEmpty(stack) ? "" : "not ");
    printf_s("Top: ");
    checkError(stackTop(stack, &point));
    printPoint(&point);
    printf_s("\n");
    system("pause");

    checkError(setPoint(&point, 9, 5));
    checkError(stackPush(stack, &point));
    printf_s("Top: ");
    checkError(stackTop(stack, &point));
    printPoint(&point);
    printf_s("\n");
    system("pause");

    checkError(stackPop(stack));
    printf_s("Top: ");
    checkError(stackTop(stack, &point));
    printPoint(&point);
    printf_s("\n");
    system("pause");

    checkError(stackPop(stack));
    printf_s("Stack is %sempty\n", stackIsEmpty(stack) ? "" : "not ");
    printf_s("Top: ");
    checkError(stackTop(stack, &point));
    printPoint(&point);
    printf_s("\n");
    system("pause");

    checkError(stackDelete(stack));

    system("pause");
    return 0;
}
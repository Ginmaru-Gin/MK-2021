#pragma once

#include <stdbool.h>
#include <stddef.H>

typedef struct Point Point;
typedef struct Stack Stack;

struct Point {
    int x, y;
};

errno_t setPoint(Point* point, int x, int y);
void printPoint(Point* point);

struct Stack {
    Point* points;
    size_t size;
    size_t capacity;
};

errno_t stackNew(Stack** stackPtr);
errno_t stackDelete(Stack* stack);

errno_t stackPush(Stack* stack, Point* point);
errno_t stackPop(Stack* stack); 

errno_t stackTop(Stack* stack, Point* buf);

bool stackIsEmpty(Stack*);

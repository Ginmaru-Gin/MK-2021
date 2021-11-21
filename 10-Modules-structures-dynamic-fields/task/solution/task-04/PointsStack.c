#include "PointsStack.h"

#include "myErrors.h"

#include <errno.h>
#include <stdlib.h>

#define DEFAULT_STACK_SIZE 1

errno_t setPoint(Point* point, int x, int y) {
    if (point == NULL) return ERR_WRONG_FUNC_ARGS;
    point->x = x;
    point->y = y;
    return ERR_SUCCESS;
}

void printPoint(Point* point) {
    printf_s("(%d, %d)", point->x, point->y);
}

// вспомогательная функция
errno_t resizeStack(Stack* stack, size_t newSize) {
    Point* ptr = (Point*)realloc(stack->points, newSize * sizeof(Point));
    if (!ptr) {
        return errno;
    }
    stack->points = ptr;
    stack->capacity = newSize;
    return ERR_SUCCESS;
}

errno_t stackNew(Stack** stackPtr) {
    *stackPtr = (Stack*)malloc(sizeof(Stack));
    if (!*stackPtr) {
        return errno;
    }
    if (!((*stackPtr)->points = (Point*)malloc(sizeof(Point) * DEFAULT_STACK_SIZE))) {
        free(*stackPtr);
        return errno;
    }
    (*stackPtr)->size = 0;
    (*stackPtr)->capacity = DEFAULT_STACK_SIZE;

    return ERR_SUCCESS;
}

errno_t stackDelete(Stack* stack) {
    if (stack == NULL) return ERR_WRONG_FUNC_ARGS;
    if (stack->points != NULL) free(stack->points);
    free(stack);
    return ERR_SUCCESS;
}

errno_t stackPush(Stack* stack, Point* point) {
    if (stack->size == stack->capacity) {
        size_t newSize = stack->capacity * 2;
        errno_t error = resizeStack(stack, newSize);
        if (error) return error;
    }
    stack->points[stack->size] = *point;
    ++stack->size;
    return ERR_SUCCESS;
}

errno_t stackPop(Stack* stack) {
    if (stackIsEmpty(stack)) return 0;
    --stack->size;
    if (stack->size * 2 < stack->capacity) {
        size_t newSize = (size_t)(stack->capacity * 0.75);
        if (resizeStack(stack, newSize)) return errno;
    }
    return ERR_SUCCESS;
}

errno_t stackTop(Stack* stack, Point* buf) {
    if (stackIsEmpty(stack)) {
        return ERR_STACK_IS_EMPTY;
    }
    Point* topPtr = &stack->points[stack->size - 1];
    buf->x = topPtr->x;
    buf->y = topPtr->y;
    return ERR_SUCCESS;
}

bool stackIsEmpty(Stack* stack) {
    return !stack->size;
}

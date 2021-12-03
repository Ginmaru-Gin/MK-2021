#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "myErrors.h"
#include "Client.h"

typedef Client data_t;
typedef data_t* dataPtr_t;

typedef struct {
    dataPtr_t* data;
    size_t size;
    size_t capacity;
} DynamicArray;

typedef DynamicArray* DynamicArrayPtr;

DynamicArrayPtr newDynamicArray(size_t capacity);
errno_t deleteDynamicArray(DynamicArrayPtr arr);

errno_t dynArrAdd(DynamicArrayPtr arr, dataPtr_t client);
errno_t dynArrRemove(DynamicArrayPtr arr, size_t index);

dataPtr_t dynArrGet(DynamicArrayPtr arr, size_t index);
size_t dynArrFind(DynamicArrayPtr arr, dataPtr_t client);

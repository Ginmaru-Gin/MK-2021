#include "dynArr.h"

#include "myErrors.h"

#include <malloc.h>
#include <string.h>

// the next two functions are unical part for our "Client" type
errno_t copyData(dataPtr_t dest, dataPtr_t source) {
    size_t passwdBufSize = strlen(source->password) + 1;
    dest->password = (char*)malloc(sizeof(char) * passwdBufSize);
    if (dest->password == NULL) return errno;
    strcpy_s(dest->password, passwdBufSize, source->password);
    dest->card = source->card;
    dest->phone = source->phone;
    dest->balance = source->balance;
    return ERR_SUCCESS;
}
bool equalsData(dataPtr_t first, dataPtr_t second) {
    return first->card == second->card;
}


errno_t dynArrResize(DynamicArrayPtr arr, size_t newSize) {
    dataPtr_t* tmp = (dataPtr_t*)realloc(arr->data, sizeof(data_t*) * newSize);
    if (!tmp) return errno;
    if (newSize < arr->size) {
        for (size_t i = newSize; i < arr->size; ++i) {
            free(arr->data[i]);
        }
        arr->size = newSize;
    }
    arr->data = tmp;
    arr->capacity = newSize;
    return ERR_SUCCESS;
}

DynamicArrayPtr newDynamicArray(size_t capacity) {
    DynamicArrayPtr arr = (DynamicArrayPtr)malloc(sizeof(DynamicArray));
    if (!arr) return NULL;
    arr->data = (dataPtr_t*)malloc(sizeof(dataPtr_t) * capacity);
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    arr->capacity = capacity;
    arr->size = 0;
    return arr;
}

errno_t deleteDynamicArray(DynamicArrayPtr arr) {
    errno_t error;
    while (!(error = dynArrRemove(arr, arr->size - 1)));
    if (arr->size == 0) {
        free(arr->data);
        free(arr);
    }
    else return error;
    return ERR_SUCCESS;
}

errno_t dynArrAdd(DynamicArrayPtr arr, dataPtr_t client) {
    errno_t error;
    if (arr->size >= arr->capacity) {
        error = dynArrResize(arr, arr->size * 2);
        if (error) return error;
    }
    dataPtr_t* ptr = &arr->data[arr->size];
    *ptr = (dataPtr_t)malloc(sizeof(data_t));
    if (!*ptr) return errno;
    error = copyData(*ptr, client);
    if (error) return error;
    ++arr->size;
    return ERR_SUCCESS;
}

errno_t dynArrRemove(DynamicArrayPtr arr, size_t index) {
    free(arr->data[index]);
    for (size_t i = index + 1; i < arr->size; ++i) {
        arr->data[i - 1] = arr->data[i];
    }
    --arr->size;
    if (arr->size * 2 < arr->capacity) {
        errno_t error = dynArrResize(arr, (size_t)(arr->capacity * 0.75));
        if (error != ERR_SUCCESS) return error;
    }
    return ERR_SUCCESS;
}

dataPtr_t dynArrGet(DynamicArrayPtr arr, size_t index) {
    if (index >= arr->size) return NULL;
    return arr->data[index];
}
size_t dynArrFind(DynamicArrayPtr arr, dataPtr_t client) {
    for (size_t i = 0; i < arr->size; ++i) 
        if (equalsData(arr->data[i], client)) return true;
    return false;
}

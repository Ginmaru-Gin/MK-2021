#include <stdio.h>

#define MAX_ARRAY_SIZE 100
#define INPUT_FILE_NAME "numbers"
#define OUTPUT_FILE_NAME "sorted"

void sort(int[MAX_ARRAY_SIZE]);

int main(void) {
    FILE* input, *output;
    int arr[MAX_ARRAY_SIZE];
    // ...
    sort(arr);
    // ...

    return 0;
}

void sort(int arr[MAX_ARRAY_SIZE]) {
    // ...
}
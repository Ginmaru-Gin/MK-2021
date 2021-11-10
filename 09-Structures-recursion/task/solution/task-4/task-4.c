/*
Выполнить task-3, но с использованием рекурсии в функции getMaxVectorModule
*/
#include <math.h.>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BEGIN_RAND_RANGE -10
#define END_RAND_RANGE 10

struct Point {
    int x, y;
};

struct Vector {
    struct Point begin, end;
};

int getRandInt(int beginRange, int endRange);
void randInitVector(struct Vector* vector, int beginRange, int endRange);
void printVector(struct Vector* vector);
double getVectorModule(struct Vector* vector);

double getMaxVectorModule(struct Vector* vectors, unsigned count);

int main(void) {
    printf_s("Enter a number of vectors: ");
    unsigned vectorsNumber = 0;
    scanf_s("%u", &vectorsNumber);
    struct Vector* vectors = (struct Vector*)malloc(sizeof(struct Vector) * vectorsNumber);
    if (!vectors) return 1;
    printf_s("Vectors:\n");
    for (unsigned i = 0; i < vectorsNumber; ++i) {
        randInitVector(vectors + i, BEGIN_RAND_RANGE, END_RAND_RANGE);
        printVector(vectors + i);
        printf_s("\n");
    }
    printf_s("Max vector module: %g\n", getMaxVectorModule(vectors, vectorsNumber));

    system("pause");
    return 0;
}

int getRandInt(int beginRange, int endRange) {
    static char seed = 0;
    if (!seed) {
        srand((unsigned)(time(NULL)));
        seed = 1;
    }
    return rand() % (endRange - beginRange + 1) + beginRange;
}

void randInitVector(struct Vector* vector, int beginRange, int endRange) {
    vector->begin.x = getRandInt(beginRange, endRange);
    vector->begin.y = getRandInt(beginRange, endRange);
    vector->end.x = getRandInt(beginRange, endRange);
    vector->end.y = getRandInt(beginRange, endRange);
}

void printVector(struct Vector* vector) {
    printf_s("{ (%d, %d), (%d, %d) }", vector->begin.x, vector->begin.y, vector->end.x, vector->end.y);
}

double getVectorModule(struct Vector* vector) {
    return sqrt((vector->end.x - vector->begin.x) * (vector->end.x - vector->begin.x) +
    (vector->end.y - vector->begin.y) * (vector->end.y - vector->begin.y));
}

// вычисляем модуль первого в массиве вектора и делаем рекурсивный вызов для
// подмассива без первого элемента, затем возращаем больший из них.
// конец рекурсии при размере массива = 1, в таком случае просто возвращаем
// модуль этого единственного вектора
double getMaxVectorModule(struct Vector* vectors, unsigned count) {
    double current = getVectorModule(vectors);
    if (count == 1) return current;
    double next = getMaxVectorModule(vectors + 1, count - 1);
    return current < next ? next : current;
}
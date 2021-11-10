#include <math.h.>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BEGIN_RAND_RANGE -10
#define END_RAND_RANGE 10

// очевидно, что структура Point представл€ет некоторую точку на плоскости
struct Point {
    int x, y;
};

// из остального кода видно, что должна быть объ€влена структура "struct Vector"
// котора€ представл€ет, соответственно, вектор, задаваемый точкой-началом
// и точкой-концом (легче всего заметить всЄ это в функции printVector)
struct Vector {
    struct Point begin, end;
};

// функци€ генерации случайного целого числа из заданного диапазона 
int getRandInt(int beginRange, int endRange);
// функци€, задающа€ случайные начало и конец вектора по заданному диапазону
// значений координат
void randInitVector(struct Vector* vector, int beginRange, int endRange);

void printVector(struct Vector* vector);
// функци€, возвращающа€ модуль вектора
double getVectorModule(struct Vector* vector);
// функци€, возвращающа€ значение максимального модул€ вектора в массиве векторов
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

double getMaxVectorModule(struct Vector* vectors, unsigned count) {
    double maxModule = 0;
    for (unsigned i = 0; i < count; ++i) {
        double tmp = getVectorModule(vectors + i);
        if (tmp > maxModule) {
            maxModule = tmp;
        }
    }
    return maxModule;
}

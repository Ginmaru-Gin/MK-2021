#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\nEXIT WITH ERROR CODE 1\n"

#define ARRAY_WIDTH 10
#define ARRAY_HEIGHT 5

void printStaticArray(int [ARRAY_HEIGHT][ARRAY_WIDTH]);
void printArray(int**, int height, int width);

int main(void) {
    srand((unsigned)time(NULL));
    // СТАТИЧЕСКИЕ МАССИВЫ

    // создадим двумерный массив и заполним ячейки соответствующими им номерами
    int staticArr[ARRAY_HEIGHT][ARRAY_WIDTH]; // объявление двумерного массива
    for (int i = 0; i < ARRAY_HEIGHT; ++i) { // "итерирование по строкам"
        for (int j = 0; j < ARRAY_WIDTH; ++j) { // "итерирование по элементам в строке"
            staticArr[i][j] = i * ARRAY_WIDTH + j + 1; // записываем номер текущей ячейки массива
        }
    }
    printf_s("arr[%d][%d]:\n", ARRAY_HEIGHT, ARRAY_WIDTH);
    printStaticArray(staticArr);

    // инициализация двумерного массива:
    int primeNumbers[3][3] = { {2, 3, 5}, {7, 11, 13}, {17, 19, 23} };
    printf_s("initialized array primeNumbers:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf_s("%d\t", primeNumbers[i][j]);
        }
        printf_s("\n");
    }

    // ДИНАМИЧЕСКИЕ МАССИВЫ
    
    // динамический двумерный массив представляет собой массив указателей:
    int height, width;
    printf_s("Enter size (HxW): ");
    scanf_s("%dx%d", &height, &width);
    int** dynamicArr = malloc(height * sizeof(int*));
    if (!dynamicArr) {
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    // теперь нужно выделить память для каждого подмассива
    for (int i = 0; i < height; ++i) {
        // в случае неудачи нужно освободить память,
        // которую мы уже выделили
        if (!(dynamicArr[i] = malloc(width * sizeof(int)))) {
            for (int j = 0; j < i; ++j) {
                free(dynamicArr[j]);
            }
            free(dynamicArr);
            printf_s(ERR_ALLOC_MEM);
            return 1;
        }
    }
    // заполним этот массив таблицей умножения
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            dynamicArr[i][j] = (i + 1) * (j + 1);
        }
    }
    printArray(dynamicArr, height, width);

    // освобождать память дин. массива нужно изнутри
    for (int i = 0; i < height; ++i) {
        free(dynamicArr[i]);
    }
    free(dynamicArr);

    // создадим двумерный массив комплексных чисел, которые будут
    // организованы как массивы из двух вещественных чисел
    // т.е. это будет трехмерный массив
    double*** complexArr = malloc(height * sizeof(double**));
    if (!complexArr) {
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    for (int i = 0; i < height; ++i) {
        if (!(complexArr[i] = malloc(width * sizeof(double*)))) {
            for (int j = 0; j < i; ++j) {
                free(complexArr);
            }
            free(complexArr);
            printf_s(ERR_ALLOC_MEM);
            return 1;
        }
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!(complexArr[i][j] = malloc(2 * sizeof(double)))) {
                // освобождаем предыдущие строки
                for (int n = 0; n < i; ++n) {
                    for (int m = 0; m < width; ++m) {
                        free(complexArr[n][m]);
                    }
                    free(complexArr[n]);
                }
                // освобождаем текущую строку
                for (int n = 0; n < j; ++n) {
                    free(complexArr[i][n]);
                }
                free(complexArr[i]);
                // освобождаем внешний массив
                free(complexArr);
                printf_s(ERR_ALLOC_MEM);
                return 1;
            }
        }
    }
    // память аллоцирована, теперь нагенерируем числа
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 2; ++k) {
                complexArr[i][j][k] = (double)rand() / RAND_MAX * 100;
            }
        }
    }
    // выведем
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf_s("(%.2lf, %.2lf)\t", complexArr[i][j][0], complexArr[i][j][1]);
        }
        printf_s("\n");
    }

    system("pause");
    return 0;
}

void printStaticArray(int arr[ARRAY_HEIGHT][ARRAY_WIDTH]) {
    for (int i = 0; i < ARRAY_HEIGHT; ++i) {
        for (int j = 0; j < ARRAY_WIDTH; ++j) {
            printf_s("%d\t", arr[i][j]);
        }
        printf_s("\n");
    }
}

void printArray(int** arr, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf_s("%d\t", arr[i][j]);
        }
        printf_s("\n");
    }
}

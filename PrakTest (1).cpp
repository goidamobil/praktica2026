#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int isSorted(int arr[], int n, int ascending) {
    if (n <= 1) return 1;
    if (ascending) {
        for (int i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1]) return 0;
    }
    else {
        for (int i = 0; i < n - 1; i++)
            if (arr[i] < arr[i + 1]) return 0;
    }
    return 1;
}

void selectionSort(int arr[], int n, long long* comparisons, long long* swaps, int ascending) {
    int i, j, extreme_idx, temp;
    *comparisons = 0;
    *swaps = 0;

    for (i = 0; i < n - 1; i++) {
        extreme_idx = i;
        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (ascending) {
                if (arr[j] < arr[extreme_idx])
                    extreme_idx = j;
            }
            else {
                if (arr[j] > arr[extreme_idx])
                    extreme_idx = j;
            }
        }
        if (extreme_idx != i) {
            temp = arr[i];
            arr[i] = arr[extreme_idx];
            arr[extreme_idx] = temp;
            (*swaps)++;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand((unsigned int)time(NULL));

    FILE* inputFile, * outputFile;
    int n = 0, i, choice, sortDirection;
    long long comparisons = 0, swaps = 0;

    printf("Программа сортировки выбором\n\n");
    printf("Выберите режим работы:\n");
    printf("1 - Прочитать массив из файла input.txt\n");
    printf("2 - Сгенерировать случайный массив в файл input.txt\n");
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    if (choice == 2) {
        printf("Введите размер массива для генерации: ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Некорректный размер.\n");
            return 1;
        }

        inputFile = fopen("input.txt", "w");
        if (inputFile == NULL) {
            printf("Ошибка создания файла!\n");
            return 1;
        }

        fprintf(inputFile, "%d\n", n);
        for (i = 0; i < n; i++) {
            fprintf(inputFile, "%d ", rand() % 100000);
        }
        fclose(inputFile);
        printf("Файл input.txt успешно сгенерирован.\n\n");
    }

    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Ошибка: Файл input.txt не найден!\n");
        return 1;
    }

    if (fscanf(inputFile, "%d", &n) != 1 || n <= 0) {
        printf("Ошибка: Некорректные данные в файле.\n");
        fclose(inputFile);
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти.\n");
        fclose(inputFile);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(inputFile, "%d", &arr[i]) != 1) {
            printf("Ошибка чтения элемента на индексе %d.\n", i);
            free(arr);
            fclose(inputFile);
            return 1;
        }
    }
    fclose(inputFile);

    if (n <= 100) {
        printf("Исходный массив: ");
        for (i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n\n");
    }
    else {
        printf("Массив на %d элементов успешно загружен.\n", n);
    }

    printf("Выберите направление сортировки:\n");
    printf("1 - по возрастанию\n");
    printf("2 - по убыванию\n");
    printf("Ваш выбор: ");
    if (scanf("%d", &sortDirection) != 1 || (sortDirection != 1 && sortDirection != 2)) {
        printf("Некорректный ввод, будет использована сортировка по возрастанию.\n");
        sortDirection = 1;
    }
    int ascending = (sortDirection == 1);

    if (isSorted(arr, n, ascending)) {
        printf("Массив уже отсортирован в заданном направлении. Сортировка не требуется.\n");
        outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            printf("Ошибка создания файла output.txt!\n");
            free(arr);
            return 1;
        }
        for (i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", arr[i]);
        }
        fclose(outputFile);
        free(arr);
        printf("Результаты сохранены в файл output.txt.\n");
        printf("СТАТИСТИКА\n");
        printf("Размер массива: %d элементов\n", n);
        printf("Направление: %s\n", ascending ? "возрастание" : "убывание");
        printf("Массив был уже отсортирован, перестановок не выполнялось.\n");
        printf("Время работы: 0.000000 секунд (сортировка пропущена)\n");
        return 0;
    }

    printf("Запуск сортировки выбором...\n");

    clock_t start_time = clock();
    selectionSort(arr, n, &comparisons, &swaps, ascending);
    clock_t end_time = clock();

    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Ошибка создания файла output.txt!\n");
        free(arr);
        return 1;
    }

    for (i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }
    fclose(outputFile);
    free(arr);

    printf("Результаты сохранены в файл output.txt.\n\n");
    printf("СТАТИСТИКА\n");
    printf("Размер массива: %d элементов\n", n);
    printf("Направление: %s\n", ascending ? "возрастание" : "убывание");
    printf("Количество сравнений: %lld\n", comparisons);
    printf("Количество перестановок: %lld\n", swaps);
    printf("Время работы: %.6f секунд\n", time_spent);

    return 0;
}
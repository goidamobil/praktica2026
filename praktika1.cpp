#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    FILE* inputFile, * outputFile;
    int n, i;

    printf("Программа сортировки выбором с замером времени\n\n");

    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Ошибка: Не удалось открыть файл input.txt!\n");
        printf("Пожалуйста, создайте файл input.txt в рабочем каталоге программы.\n");
        return 1;
    }

    if (fscanf(inputFile, "%d", &n) != 1 || n <= 0) {
        printf("Ошибка: Некорректный размер массива в файле.\n");
        fclose(inputFile);
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка: Не удалось выделить память.\n");
        fclose(inputFile);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(inputFile, "%d", &arr[i]) != 1) {
            printf("Ошибка при чтении элемента массива на индексе %d.\n", i);
            free(arr);
            fclose(inputFile);
            return 1;
        }
    }
    fclose(inputFile);

    if (n <= 100) {
        printf("Исходный массив: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
    }
    else {
        printf("Исходный массив успешно загружен (элементов: %d). Вывод скрыт, так как массив слишком большой.\n\n", n);
    }

    clock_t start_time = clock();

    selectionSort(arr, n);

    clock_t end_time = clock();

    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Открытие файла для записи результата
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Ошибка: Не удалось создать файл output.txt!\n");
        free(arr);
        return 1;
    }

    if (n <= 100) {
        printf("Отсортированный массив: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
            fprintf(outputFile, "%d ", arr[i]);
        }
        printf("\n\n");
    }
    else {
        for (i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", arr[i]);
        }
        printf("Массив отсортирован и успешно сохранен в файл output.txt.\n\n");
    }

    fclose(outputFile);
    free(arr);

    // Вывод итоговой статистики времени
    printf("Статистика выполнения\n");
    printf("Время работы алгоритма: %.10f секунд\n", time_spent);
    return 0;
}
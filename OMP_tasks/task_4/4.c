/* Написать программу, в которой объявить и присвоить начальные значения целочисленным
массивам a[10] и b[10], определить параллельную область, количество нитей задать равным
2, выделить код для основной (номер 0) и нити с номером 1. Основная нить должна
выполнять поиск min значения элементов массива a, нить с номером 1 - поиск max значения
элементов массива b. Результат выдать на экран. */

#include <stdio.h>
#include <omp.h>
#include <limits.h>


int main(int argc, char *argv[])
{
    int a[10] = {0, 1, 2, -3, 4, 5, 6, 7, 8, 9};
    int b[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            int min = INT_MAX;
            printf("Поток номер %d начал поиск минимума...\n", omp_get_thread_num());
            //
            for (int i = 0; i < 10; i++)
            {
                printf("Поток номер %d ищет минимум...\n", omp_get_thread_num());
                if (min > a[i])
                    min = a[i];
            }
            printf("Минимум: %d \n", min);
        }
        #pragma omp section
        {
            int max = INT_MIN;
            printf("Поток номер %d начал поиск максимума...\n", omp_get_thread_num());
            //
            for (int i = 0; i < 10; i++)
            {
                printf("Поток номер %d ищет максимум...\n", omp_get_thread_num());
                if (max < a[i])
                    max = a[i];
            }
            printf("Максимум: %d \n", max);
        }
    }
}

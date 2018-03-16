/* Написать программу, в которой объявить и присвоить начальные значения элементам
двумерного массива d[6][8], для инициализации значений использовать генератор случайных
чисел. Используя конструкцию директивы sections...section определить три секции для
выполнения следующих операций:
    - первая секция выполняет вычисление среднего арифметического значения элементов
двумерного массива,
    - вторая секция выполняет вычисление минимального и максимального значений
элементов двумерного массива,
    - третья секция выполняет вычисление количества элементов массива, числовые значения
которых кратны 3.
В каждой секции определить и выдать на экран номер исполняющей нити и результат
выполнения вычислений */

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int d[6][8];

    // Заполняем массив случайными значениями от 0 до 50
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            d[i][j] = rand() % 50;
            printf("%d, ", d[i][j]);
        }
        printf("\n");
    }

#pragma omp parallel sections num_threads(3)
    {
#pragma omp section
        {
            int sum = 0, length = 0;
            for (int i = 0; i < 6; i++)
            {
                printf("Нить %d считает среднее арифметическое\n", omp_get_thread_num());
                for (int j = 0; j < 8; j++)
                {
                    sum += d[i][j];
                    length += 1;
                }
            }
            printf("Среднее арифметическое: %d\n", sum / length);
        }
#pragma omp section
        {
            int min = INT_MAX;
            int max = INT_MIN;
            for (int i = 0; i < 6; i++)
            {
                printf("Нить %d считает минимум и максимум\n", omp_get_thread_num());
                for (int j = 0; j < 8; j++)
                {
                    if (d[i][j] < min)
                        min = d[i][j];

                    if (d[i][j] > max)
                        max = d[i][j];
                }
            }
            printf("Минимум: %d, Максимум: %d\n", min, max);
        }

#pragma omp section
        {
            int count3 = 0;
            for (int i = 0; i < 6; i++)
            {
                printf("Нить %d считает количество элементов, кратных 3\n", omp_get_thread_num());
                for (int j = 0; j < 8; j++)
                {
                    if (d[i][j] % 3 == 0)
                        count3 += 1;
                }
            }
            printf("Количество элементов, кратных 3: %d\n", count3);
        }
    }
}
/* Написать программу, в которой объявить и присвоить начальные значения массиву целых
чисел a[30], для инициализации значений использовать генератор случайных чисел.
Используя конструкцию omp parallel for и omp atomic вычислить количество элементов
массива, числовые значения которых кратны 9. Количество нитей задать самостоятельно.
Результат выдать на экран. */

#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int a[10];

    for (int i = 0; i < 10; i++)
        a[i] = rand() % 50;

    int count = 0;
#pragma omp parallel for shared(count) num_threads(4)
    for (int i = 0; i < 10; i++)
    {
        if (a[i] % 9 == 0)
        {
            printf("%d\n", a[i]);
#pragma omp atomic
            count++;
        }
    }

    printf("Количество элементов, кратных 9: %d", count);
}
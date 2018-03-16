/* Написать программу, в которой объявить и присвоить начальные значения целочисленным
массивам a[10] и b[10]. Используя конструкцию parallel for и reduction вычислить средние
арифметические значения элементов массивов a и b, сравнить полученные значения,
результат выдать на экран. */

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 2, 3, 5};
    int b[10] = {2, 5, 7, 8, 2, 34, 5, 7, 2, 95};

    int sum_a = 0, sum_b = 0;
    #pragma omp parallel for reduction(+:sum_a,sum_b) firstprivate(a,b)
    for (int i = 0; i<10; i++) {
        sum_a += a[i];
        sum_b += b[i];
    }

    printf("Ср. арифм a: %d\nСр. арифм b: %d\n", sum_a/10, sum_b/10);
}
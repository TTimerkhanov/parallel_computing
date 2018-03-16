/* Написать параллельную программу возведения числа 210 в квадрат
без операции
умножения.
Пояснение: Квадрат натурального числа N равен сумме первых N нечетных чисел. Например,
32 = 9 это 1+3+5=9; 52 = 25 это 1+3+5+7+9=25; */

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int number = 210;
    long result = 0;
    int add = 1;

#pragma omp parallel for reduction(+: result)
    for (int i = 0; i < number; i++)
    {

#pragma omp critical
        {
            result += add;
            add += 2;
        }
    }

    printf("%ld", result);
}
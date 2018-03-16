/*
 Написать программу, в которой определить две параллельные области, выполнение которых
 зависит от условного оператора #pragma omp parallel if(...), если заданное значение числа
 нитей больше 1, параллельная область выполняется, иначе не выполняется. Число нитей
 перед первой областью задать равным 3, перед второй – равным 1. Внутри параллельных
 областей определить количество нитей и номер каждой нити, результат выдать на экран.
 Убедиться в правильности работы программы.
*/

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    omp_set_dynamic(0);
    omp_set_num_threads(3);

    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        if (omp_in_parallel())
            printf("Нить номер %d, Количество нитей: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    omp_set_num_threads(1);

    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        if (omp_in_parallel())
            printf("Нить номер %d, Количество нитей: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return 0;
}

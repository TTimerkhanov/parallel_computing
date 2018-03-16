/* Написать программу где каждый поток печатает свой идентификатор, количество потоков
всего и строчку «Hello World». Запустить программу с 8 потоками. Всегда ли вывод
идентичен? Почему? */

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
       omp_set_dynamic(0);
    omp_set_num_threads(8);

    #pragma omp parallel 
    {
        printf("Hello World! Это тред номер %d, всего таких нас %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
}
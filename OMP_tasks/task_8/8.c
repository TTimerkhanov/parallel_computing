/* Используя возможности OpenMP, написать программу умножения матрицы на вектор.
Сравнить время выполнения последовательной и параллельных программ. */

#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 100
#define M 112

int main(int argc, char *argv[])
{
    // Инициализация
    static long matrix[N][M];
    static long vector[M];

    // Вектору присваиваиваем значения vector[i] = i*2, i=(1,M)
    for (int i = 0; i < M; i++)
    {
        vector[i] = i;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            matrix[i][j] = i + 1;
        }
    }
    long result_vector[N];

    // Последовательная секция
    double start_time = omp_get_wtime();
    for (int i = 0; i < N; i++)
    {
        result_vector[i] = 0;
        for (int j = 0; j < M; j++)
        {
            result_vector[i] += matrix[i][j] * vector[j];
        }
    }
    double end_time = omp_get_wtime();
    double result_time = (end_time - start_time);

    printf("Время последовательного блока: %f\n", result_time);

    // print_result(result_vector, N);

    
    
    
    
    
    double result_time_parallel;
    double start_time_parallel;
    double end_time_parallel;
    
    // Параллельная секция
    #pragma omp parallel num_threads(4) 
    {
        start_time_parallel = omp_get_wtime();
        
        #pragma omp for 
        for (int i = 0; i < N; i++)
        {
            result_vector[i] = 0;
            for (int j = 0; j < M; j++)
            {
                result_vector[i] += matrix[i][j] * vector[j];
            }
        }
        end_time_parallel = omp_get_wtime();
    }

    result_time_parallel = (end_time_parallel - start_time_parallel);
    printf("Время параллельного блока: %f\n", result_time_parallel);

    // print_result(result_vector, N);

}

void print_result(long array[], long n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%ld\n", array[i]);
    }
}

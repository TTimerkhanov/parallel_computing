#include "iostream"
#include "mpi.h"
#include <ctime>
#include <cstdlib>

#define SIZE 10

int main(int argc, char **argv)
{
    int rank, size, bufElems;
    srand(time(NULL));
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 1)
    {
        int arr[SIZE];
        // Заполняем массив рандомными значениями
        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = rand() % SIZE;
        }
        // Отправляем этот массив всем остальным потокам
        for (int i = 0; i < size; i++)
        {
            if (i != rank)
            {
                MPI_Send(arr, SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    else
    {
        // Проверяем длину входного сообщения
        MPI_Status status;
        MPI_Probe(1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &bufElems);
        // Выделяем память буферу размером опробованного сообщения  
        int *buf = (int *)malloc(sizeof(int) * bufElems);
        // Получаем массив
        MPI_Recv(buf, bufElems, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < bufElems; i++)
        {
            printf("%d ", buf[i]);
        };
        printf("\nНомер процесса: %d\n", rank);
        free(buf);
    }
    MPI_Finalize();
    return 0;
}
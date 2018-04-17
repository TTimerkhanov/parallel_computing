#include "iostream"
#include "mpi.h"
#include <ctime>
#include <cstdlib>

#define SIZE 12

void subarray(int arr[], int subarr[], int start, int end)
{
    int index = 0;
    for (int i = start; i < end; i++)
    {
        subarr[index] = arr[i];
        index++;
    }
}

int main(int argc, char **argv)
{
    int rank, size, bufElems;
    srand(time(NULL));
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0)
    {
        int arr[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = rand() % SIZE;
            printf("%d ", arr[i]);
        };
        printf("\n");

        for (int i = 0; i < size; i++)
        {
            int subarr[SIZE / (size + 1)];
            subarray(arr, subarr, i * SIZE / (size + 1), (i + 1) * SIZE / (size + 1));
            MPI_Send(subarr, SIZE / (size + 1), MPI_INT, i, 0, MPI_COMM_WORLD);
        };
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &bufElems);
        int *buf = (int *)malloc(sizeof(int) * bufElems);
        MPI_Recv(buf, bufElems, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < bufElems; i++)
        {
            printf("%d ", buf[i]);
        };
        printf("\nНомер процесса: %d\n", rank);
        free(buf);
    }
    else
    {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &bufElems);
        int *buf = (int *)malloc(sizeof(int) * bufElems);
        MPI_Recv(buf, bufElems, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
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
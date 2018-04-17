#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int N = 20;
    int partSize = N / size - 1;

    int localarr[N];
    int receive_vector[partSize];

    srand(time(NULL) + rank);

    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
        {
            localarr[i] = rand() % 100;
        }
    }

    MPI_Scatter(localarr, partSize, MPI_INT,
                receive_vector, partSize, MPI_INT, 
                0, MPI_COMM_WORLD);
    int localres[2], globalres[2];

    for (int proc = 0; proc < size; proc++)
    {
        if (rank == proc)
        {
            printf("Rank %2d has values: ", rank);
            for (int i = 0; i < partSize; i++)
                printf(" %d ", receive_vector[i]);
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    localres[0] = 111111;
    for (int i = 0; i < partSize; i++)
    {

        if (receive_vector[i] < localres[0])
        {
            localres[0] = receive_vector[i];
        }
        localres[1] = rank;
    }

    MPI_Reduce(&localres, &globalres, 1, MPI_2INT, MPI_MINLOC, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Rank %d has lowest value of %d\n", globalres[1], globalres[0]);
    }

    MPI_Finalize();

    return 0;
}
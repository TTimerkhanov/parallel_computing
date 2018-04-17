#include <stdio.h>
#include "mpi.h"

#define N 4

template <int rows, int cols>
void printMatrix(int (&matrix)[rows][cols])
{
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    MPI_Init(&argc, &argv);
    int i, rank, size, globalres;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int init[N][N] = {{1, 2, 3, 8},
                      {5, 6, 7, 8},
                      {9, 1, 2, 3},
                      {9, 9, 6, 7}};
 
    int a[N][N];
    // Finding transpose of matrix a[][] and storing it in array trans[][].
    for (i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            a[j][i] = init[i][j];
        }

    int aa[N];

    MPI_Scatter(a, N * N / size, MPI_INT, aa, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    for (i = 0; i < N; i++)
        sum += aa[i];

    MPI_Reduce(&sum, &globalres, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Finalize();

    if (rank == 0)
        printf("%d", globalres);
}

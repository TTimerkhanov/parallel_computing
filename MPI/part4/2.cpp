#define N 4
#include <stdio.h>
#include "mpi.h"

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
    int i, j, k, rank, size;
    int a[N][N] = {{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 1, 2, 3},
                   {4, 5, 6, 7}};

    int b[N][N] = {{2, 4, 2, 1},
                   {5, 6, 7, 8},
                   {9, 1, 2, 3},
                   {4, 5, 6, 7}};
    int c[N][N];
    int aa[N], bb[N], cc[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Scatter(a, N * N / size, MPI_INT, aa, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, N * N / size, MPI_INT, bb, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < N; i++)
        cc[i] = aa[i] * bb[i]; 

    MPI_Gather(cc, N * N / size, MPI_INT, c, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Finalize();
    
    if (rank == 0) 
        printMatrix(c);
}


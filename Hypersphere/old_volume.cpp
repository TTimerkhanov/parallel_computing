#include <stdio.h>
#include <mpi.h>
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

void srand48();
double drand48();

#define iterations 25000000

double getVolumes(int n)
{
    double r = 0;
    double globalres, total0, total1 = 0;
    {

        for (long i = 0; i < iterations; i++)
        {
            total0 = 0.0;
            for (int j = 0; j < n; ++j)
            {
                r = (long double)drand48();
                total0 += r * r;
            }
            if (total0 < 1)
                ++total1;
        }
    }
    MPI_Reduce(&total1, &globalres, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return globalres;
}

int main(int argc, char *argv[])
{
    int Procs;
    int my_rank;
    double globalres;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Procs);
    srand48((long)my_rank);
    for (int i = 2; i < 5; i++)
    {
        globalres = getVolumes(i);
        if (my_rank==0)
        printf("Объем %d-мерной сферы равен %f\n", i, pow(2.0, i) * (globalres / (iterations*Procs)));
    }
}
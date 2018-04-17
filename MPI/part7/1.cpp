#include "iostream"
#include "/usr/include/mpi/mpi.h"
#include <ctime>
#include <cstdlib>
#define SIZE 10

int main(int argc, char *argv[])
{

    MPI_Init(&argc, &argv);

    MPI_Group myGroup;
    MPI_Group first_row_group;
    MPI_Comm first_row_comm;
    MPI_Comm dup_comm_world;
    int group_rank, group_size;

    int process_ranks[5] = {8, 3, 9, 1, 6};

    MPI_Comm_dup(MPI_COMM_WORLD, &dup_comm_world);

    MPI_Comm_group(MPI_COMM_WORLD, &myGroup);

    MPI_Group_incl(myGroup, 5, process_ranks, &first_row_group);

    MPI_Group_rank(first_row_group, &group_rank);
    MPI_Group_size(first_row_group, &group_size);
    // printf("Size #%d\n", group_size);

    MPI_Comm_create(dup_comm_world, first_row_group, &first_row_comm);

    if (first_row_comm != MPI_COMM_NULL)
    {
        int size, rank;

        MPI_Comm_size(first_row_comm, &size);
        MPI_Comm_rank(first_row_comm, &rank);

        // for (int i = 0; i < size; i++)
        // {
        //     printf("Size #%d\n", size);
        // }

        srand(time(NULL));
        int arr[SIZE];

        if (rank == 0)
        {
            // Заполняем массив рандомными значениями
            for (int i = 0; i < SIZE; i++)
            {
                arr[i] = rand() % SIZE;
                printf("%d\n", arr[i]);
            }
        }

        MPI_Bcast(arr, SIZE, MPI_INT, 0, first_row_comm);

        for (int rnk = 0; rnk < size; rnk++)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (rnk == rank)
                    printf("arr[%d] is [%d] from rank %d\n", i, arr[i], rank);
            }
        }

        if (rank == size - 1)
        {
            arr[0] = -26;
            MPI_Send(arr, SIZE, MPI_INT, 0, 25, first_row_comm);
            printf("DATA SENT FROM SIZE - 1\n");
        }

        if (rank == 0)
        {

            int bufElems;
            MPI_Status status;
            MPI_Probe(size - 1, 25, first_row_comm, &status);
            MPI_Get_count(&status, MPI_INT, &bufElems);
            printf("HELLO FROM 1 bufel = %d\n", bufElems);
            
            // Выделяем память буферу размером опробованного сообщения
            int *buf = (int *)malloc(sizeof(int) * bufElems);
            // Получаем массив
            MPI_Recv(buf, bufElems, MPI_INT, size - 1, 25, first_row_comm, MPI_STATUS_IGNORE);
            printf("arr[0] received on first subroutine is %d\n", buf[0]);
        }
    }

    MPI_Finalize();
}
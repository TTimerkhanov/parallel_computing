#include "iostream"
#include "/usr/include/mpi/mpi.h"
#define SIZE 10

int main(int argc, char **argv)
{
    int size, rank;
    int ranks1[5] = {0, 2, 4, 6, 8};

    MPI_Comm comm1, comm2, comm3, comm4, local, icomm, icomm1, dup_comm_world;
    MPI_Group group1, group2, group3, group4, wgroup;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_group(MPI_COMM_WORLD, &wgroup);
    MPI_Group_incl(wgroup, 5, ranks1, &group1);
    MPI_Group_excl(wgroup, 5, ranks1, &group2);

    MPI_Group_incl(wgroup, 5, ranks1, &group3);
    MPI_Group_excl(wgroup, 5, ranks1, &group4);
    // MPI_Group_incl(wgroup, 2, ranks1, &group1);
    // MPI_Group_incl(wgroup, 2, ranks2, &group2);
    // MPI_Comm_group(dup_comm_world, &group1);
    // MPI_Comm_group(dup_comm_world, &group2);
    // MPI_Comm_group(MPI_COMM_WORLD, &group3);
    // MPI_Comm_group(MPI_COMM_WORLD, &group4);
    MPI_Comm_create_group(MPI_COMM_WORLD, group1, 1, &comm1);
    MPI_Comm_create_group(MPI_COMM_WORLD, group2, 2, &comm2);
    MPI_Comm_create_group(MPI_COMM_WORLD, group3, 3, &comm3);
    MPI_Comm_create_group(MPI_COMM_WORLD, group4, 4, &comm4);

    MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
    MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);
    MPI_Comm_create(MPI_COMM_WORLD, group3, &comm3);
    MPI_Comm_create(MPI_COMM_WORLD, group4, &comm4);

    // MPI_Comm_set_name(comm1, "Comm 1");
    // MPI_Comm_set_name(comm2, "Comm 2");
    // MPI_Comm_set_name(comm3, "Comm 3");
    // MPI_Comm_set_name(comm4, "Comm 4");

    int rank1 = -1;
    int rank2 = -1;
    int rank3 = -1;
    int rank4 = -1;
    if (comm1 != MPI_COMM_NULL)
        MPI_Comm_rank(comm1, &rank1);
    if (comm2 != MPI_COMM_NULL)
        MPI_Comm_rank(comm2, &rank2);
    printf("rank1=%d, rank2=%d, rank=%d\n", rank1, rank2, rank);

    char nameout[MPI_MAX_OBJECT_NAME];
    int rlen;
    int a[10], globalres[10];

    if (comm1 != MPI_COMM_NULL)
    {
        MPI_Comm_size(comm1, &size);
        MPI_Comm_rank(comm1, &rank1);
        MPI_Comm_get_name(comm1, nameout, &rlen);

        for (int i = 0; i < 10; i++)
            a[i] = 1;

        MPI_Reduce(&a, &globalres, 10, MPI_INT, MPI_SUM, 0, comm1);

        if (rank1 == 0)
            for (int i = 0; i < 10; i++)
                printf("%d from rank %d and comm 1\n", globalres[i], rank1);
    }

    if (comm2 != MPI_COMM_NULL)
    {
        MPI_Comm_size(comm2, &size);
        MPI_Comm_rank(comm2, &rank2);
        MPI_Comm_get_name(comm2, nameout, &rlen);

        for (int i = 0; i < 10; i++)
            a[i] = 2;

        MPI_Reduce(&a, &globalres, 10, MPI_INT, MPI_SUM, 0, comm2);

        if (rank2 == 0)
            for (int i = 0; i < 10; i++)
                printf("%d from rank %d and comm 2\n", globalres[i], rank2);
    }
    if (comm3 != MPI_COMM_NULL)
    {
        MPI_Comm_size(comm3, &size);
        MPI_Comm_rank(comm3, &rank3);
        MPI_Comm_get_name(comm3, nameout, &rlen);

        for (int i = 0; i < 10; i++)
            a[i] = 3;

        MPI_Reduce(&a, &globalres, 10, MPI_INT, MPI_SUM, 0, comm3);

        if (rank1 == 0)
            for (int i = 0; i < 10; i++)
                printf("%d from rank %d and comm 3\n", globalres[i], rank3);
    }

    if (comm4 != MPI_COMM_NULL)
    {
        MPI_Comm_size(comm4, &size);
        MPI_Comm_rank(comm4, &rank4);
        MPI_Comm_get_name(comm4, nameout, &rlen);

        for (int i = 0; i < 10; i++)
            a[i] = 4;

        MPI_Reduce(&a, &globalres, 10, MPI_INT, MPI_SUM, 0, comm4);

        if (rank2 == 0)
            for (int i = 0; i < 10; i++)
                printf("%d from rank %d and comm 4\n", globalres[i], rank4);
    }

    // printf("rank1=%d, rank2=%d, rank=%d\n", rank1, rank2, rank);
    int tag;

    int rlead;
    if (comm1 != MPI_COMM_NULL)
    {
        tag = 777;
        local = comm1;
        rlead = 1;
        MPI_Intercomm_create(local, 0, MPI_COMM_WORLD, rlead, tag, &icomm);
    }
    if (comm2 != MPI_COMM_NULL)
    {
        tag = 777;
        local = comm2;
        rlead = 0;
        MPI_Intercomm_create(local, 0, MPI_COMM_WORLD, rlead, tag, &icomm);
    }

    if (comm3 != MPI_COMM_NULL)
    {
        tag = 888;
        local = comm3;
        rlead = 3;
        MPI_Intercomm_create(local, 1, MPI_COMM_WORLD, rlead, tag, &icomm1);
    }
    if (comm4 != MPI_COMM_NULL)
    {
        tag = 888;
        local = comm4;
        rlead = 2;
        MPI_Intercomm_create(local, 1, MPI_COMM_WORLD, rlead, tag, &icomm1);
    }

    if (icomm != MPI_COMM_NULL)
    {
        MPI_Comm_rank(icomm, &rank);
        printf("ICOMM RANK %d\n", rank);
    }

    if (rank1 == 0)
    {
        MPI_Send(&a[0], 1, MPI_INT, 0, 12, icomm);
    }
    if (rank2 == 0)
    {
        MPI_Recv(&a[0], 1, MPI_INT, MPI_ANY_SOURCE, 12, icomm, MPI_STATUSES_IGNORE);
        printf("a=%d\n", a[0]);
    }

    if (rank3 == 0)
    {
        MPI_Send(&a[0], 1, MPI_INT, 0, 12, icomm1);
    }
    if (rank4 == 0)
    {
        MPI_Recv(&a[0], 1, MPI_INT, MPI_ANY_SOURCE, 12, icomm1, MPI_STATUSES_IGNORE);
        printf("a=%d\n", a[0]);
    }

    MPI_Finalize();
}
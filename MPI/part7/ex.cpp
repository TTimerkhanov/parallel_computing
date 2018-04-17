
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int rank, size;
	int ranks[2]={0,2};
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Group wgroup,group1,group2;
	MPI_Comm_group(MPI_COMM_WORLD,&wgroup);
	MPI_Group_incl(wgroup,2,ranks,&group1);
	MPI_Group_excl(wgroup,2,ranks,&group2);

	MPI_Comm comm1,comm2, icomm,local;
	MPI_Comm_create(MPI_COMM_WORLD,group1,&comm1);
	MPI_Comm_create(MPI_COMM_WORLD,group2,&comm2);
	
	int rank1=-1;
	int rank2=-1;
	if (comm1!=MPI_COMM_NULL) MPI_Comm_rank(comm1,&rank1);
	if (comm2!=MPI_COMM_NULL) MPI_Comm_rank(comm2,&rank2);
	printf("rank1=%d, rank2=%d, rank=%d\n",rank1,rank2,rank);


	int rlead;
	if (comm1!=MPI_COMM_NULL) { local=comm1; rlead=1;}
	if (comm2!=MPI_COMM_NULL) { local=comm2; rlead=0;}
	int tag=777;
	MPI_Intercomm_create(local,0,MPI_COMM_WORLD,rlead,tag,&icomm);

	int a=-1;
	if (rank1==0) { a=10; MPI_Send(&a,1,MPI_INT,0,12,icomm);}
	if (rank2==0) {MPI_Recv(&a,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,icomm,MPI_STATUSES_IGNORE); printf("a=%d\n",a);}

	if (comm1!=MPI_COMM_NULL) MPI_Comm_free(&comm1);
	if (comm2!=MPI_COMM_NULL) MPI_Comm_free(&comm2);

	MPI_Group_free(&group1);
	MPI_Group_free(&group2);

	MPI_Finalize();
}


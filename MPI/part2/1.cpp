
#include "iostream"
#include "mpi.h"
#include "vector"
#define SIZE 10
#define TASK 4

using namespace std;
void printVector(vector<int> x)
{
	for (int i = 0; i < x.size(); i++)
	{
		printf("%d ", x[i]);
	};
	printf("\n");
}


vector<int> addVector(vector<int>& x, vector<int>& y)
{
	vector<int> result(x.size());
	for (int i = 0; i < x.size(); i++)
	{
		result[i] = x[i] + y[i];
	}
	return result;
}

int main(int argc, char **argv)
{
	int rank, num_threads;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_threads);
	int partSize = SIZE / (num_threads - 1);
	if (rank == 0)
	{
		vector<int> x(SIZE), y(SIZE);
		for (int i = 0; i < SIZE; i++)
		{
			x[i] = i;
			y[i] = 1;
		}
		printVector(x);
		printVector(y);

		for (int i = 1; i < num_threads; i++)
		{
			vector<int> xPart(&x[partSize * (i - 1)], &x[partSize * i]),
				yPart(&y[partSize * (i - 1)], &y[partSize * i]), result(partSize), auxResult(partSize);

			if (TASK == 1)
			{
				MPI_Send(&xPart[0], xPart.size(), MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&yPart[0], yPart.size(), MPI_INT, i, 1, MPI_COMM_WORLD);
				MPI_Recv(&result[0], partSize, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("a. ");
				printVector(result);
			}

			else if (TASK == 4)
			{
				MPI_Send(&xPart[0], xPart.size(), MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&yPart[0], yPart.size(), MPI_INT, i, 1, MPI_COMM_WORLD);

				MPI_Recv(&result[0], partSize, MPI_INT, MPI_ANY_SOURCE, 41, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(&auxResult[0], partSize, MPI_INT, MPI_ANY_SOURCE, 42, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("d. x: ");
				printVector(result);

				printf("d. y: ");
				printVector(auxResult);
			}
		}
	}
	else
	{
		vector<int> xPart(partSize), yPart(partSize), result(partSize);

		if (TASK == 1)
		{
			MPI_Recv(&xPart[0], partSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&yPart[0], partSize, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			result = addVector(xPart, yPart);

			MPI_Send(&result[0], result.size(), MPI_INT, 0, 10, MPI_COMM_WORLD);
		}
		else if (TASK == 4)
		{
			MPI_Recv(&xPart[0], partSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&yPart[0], partSize, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::swap(xPart, yPart);
			MPI_Send(&xPart[0], result.size(), MPI_INT, 0, 41, MPI_COMM_WORLD);
			MPI_Send(&yPart[0], result.size(), MPI_INT, 0, 42, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
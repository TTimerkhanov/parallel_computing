#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

bool is_prime(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    int lo;
    int hi;

    printf("Enter a value :\n");
    scanf("%d", &lo);

    printf("Enter a value :\n");
    scanf("%d", &hi);
    

#pragma omp parallel for ordered schedule(dynamic) num_threads(4)
    for (int i = lo; i <= hi; i++)
    {

        if (is_prime(i))
        {
#pragma omp ordered
            printf("%d\n", i);
        }
    }
}

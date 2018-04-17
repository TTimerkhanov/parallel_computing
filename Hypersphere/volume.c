#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>


# define iterations 25000000

void getVolumes(int n) {
    double r = 0;
    double total0, total1 = 0;

    #pragma omp parallel num_threads(4) 
    {
        unsigned seed = 25234 + 17*omp_get_thread_num();
        #pragma omp for private(total0) reduction(+:total1) 
        for (long i = 0; i < iterations; i++)
        {
            total0 = 0.0;
            for (int j = 0; j < n; ++j)
            {
                    r =  (long double)rand_r(&seed) / RAND_MAX;
                    
                    total0 += r * r;
            }
            if (total0 < 1)
                ++total1;
        }
        
    }
    printf("Объем %d-мерной сферы равен %f\n", n, pow(2.0, n) * (total1 / iterations));

}

int main(int argc, char *argv[])
{
    for(int i=2;i<20;i++) {
        getVolumes(i);
    }

}
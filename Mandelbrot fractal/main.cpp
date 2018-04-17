#include <complex>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <fstream>

typedef std::complex<double> complex;

int MandelbrotCalculate(complex c, int maxiter)
{
    // iterates z = z + c until |z| >= 2 or maxiter is reached,
    // returns the number of iterations.
    complex z = c;
    int n = 0;
    for (; n < maxiter; n++)
    {
        if (std::abs(z) >= 4.0)
            break;
        z = z * z + c;
    }
    return n;
}

template <typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in)
{

    std::vector<double> linspaced;

    double start = static_cast<double>(start_in);
    double end = static_cast<double>(end_in);
    double num = static_cast<double>(num_in);

    if (num == 0)
    {
        return linspaced;
    }
    if (num == 1)
    {
        linspaced.push_back(start);
        return linspaced;
    }


    double delta = (end - start) / (num - 1);

    #pragma omp parallel for
    for (int i = 0; i < num - 1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end); 
    return linspaced;
}



const int DENSITY = 6000;
double atlas[DENSITY][DENSITY];
int main()
{
    double time = omp_get_wtime();

    double real_start = -2.25, real_end = 0.75;
    double imaginary_start = -1.5, imaginary_end = 1.5;

    std::vector<double> real_vector = linspace(real_start, real_end, DENSITY);
    std::vector<double> imaginary_vector = linspace(imaginary_start, imaginary_end, DENSITY);

#pragma omp parallel for nowait
    for (int i = 0; i < DENSITY; i++)
    {
        for (int j = 0; j < DENSITY; j++)
        {
            complex c(real_vector[i], imaginary_vector[j]);
            atlas[i][j] = MandelbrotCalculate(c, 120);
        }
    }

    printf("Test #1: %f s\n", (omp_get_wtime() - time));

    std::ofstream myfile;
    myfile.open("set");

    #pragma omp parallel for
    for (int i = 0; i < DENSITY; i++)
    {
        for (int j = 0; j < DENSITY; j++)
        {
            #pragma omp critical
            myfile << i << "," << j << "," << atlas[i][j] << "\n";
        }
    }
    myfile.close();
}

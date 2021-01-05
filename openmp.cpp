#include<stdlib.h>
#include <iostream>
#include <chrono>
#include <omp.h>

#define MATSIZE 10
#define MAXITERATIONS 10000000

int main()
{
    int matA[MATSIZE][MATSIZE];
    int matB[MATSIZE][MATSIZE];
    int matC[MATSIZE][MATSIZE];


#pragma omp parallel for collapse(2)
    // Generating random values in matA and matB, initializing matC with 0s
    for (int i = 0; i < MATSIZE; i++) {
        for (int j = 0; j < MATSIZE; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
            matC[i][j] = 0;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    int res;
    #pragma omp parallel for shared(matC, matA, matB) private(res) collapse(2)
    for (int i = 0; i < MATSIZE; i++) {
        for (int j = 0; j < MATSIZE; j++) {
            res = 0;
            for(int iter = 0; iter < MAXITERATIONS; iter++) {
                for(int k = 0; k < MATSIZE; k++) {
                    res += matA[i][k] * matB[k][j];
                }
            }
            matC[i][j] = res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " seconds" << std::endl;

    return EXIT_SUCCESS;
}


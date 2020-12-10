#include <iostream>
#include <omp.h>
#include <chrono>

#define vectorsize 1000000
#define iterations 100

double A[vectorsize];

void cpu() {
    std::cout << "--- CPU ---\n";
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for collapse(2)
    for(int i = 0; i < iterations; i++) {
        for(int j = 0; j < vectorsize; j++) {
            A[j] *= 1.1 * 0.9;
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Elapsed time: " << (float) std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()/1000 << " s\n";
}

void simd() {
    std::cout << "--- SIMD ---\n";
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for simd collapse(2)
    for(int i = 0; i < iterations; i++) {
        for(int j = 0; j < vectorsize; j++) {
            A[j] *= 1.1 * 0.9;
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Elapsed time: " << (float) std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()/1000 << " s\n";
}

void gpu() {
    std::cout << "--- GPU ---\n";
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp target teams distribute parallel for collapse(2)
    for(int i = 0; i < iterations; i++) {
        for(int j = 0; j < vectorsize; j++) {
            A[j] *= 1.1 * 0.9;
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Elapsed time: " << (float) std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()/1000 << " s\n";

}

int main() {
    #pragma omp parallel for
    for(int i = 0; i < vectorsize; i++)
        A[i] = 100.0;
    cpu();
    simd();
    gpu();

}
#include <iostream>
#include <chrono>
#include <omp.h>

#define vectorsize 1000000
#define simlength 100000

double A[vectorsize];

void cpu() {
	std::cout << "Starting CPU computation ..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	#pragma omp parallel for collapse(2)
    for(int i = 0; i < simlength; i++)
    {
        for(int j = 1; j < vectorsize-1; j++)
            A[j] *= (A[j-1] + A[j+1])/2;
    }
	auto end = std::chrono::high_resolution_clock::now();
	
	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " seconds" << std::endl;
}

void simd() {
	std::cout << "Starting SIMD computation ..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	#pragma omp parallel for simd collapse(2)
    for(int i = 0; i < simlength; i++)
    {
        for(int j = 1; j < vectorsize-1; j++)
            A[j] *= (A[j-1] + A[j+1])/2;
    }
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " seconds" << std::endl;
}

void gpu() {
	std::cout << "Starting GPU computation ..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	#pragma omp target teams distribute \
							parallel for map(A) collapse(2) device(0)
    for(int i = 0; i < simlength; i++)
    {
        for(int j = 1; j < vectorsize-1; j++)
            A[j] *= (A[j-1] + A[j+1])/2;
    }
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " seconds" << std::endl;
}

int main() {

	#pragma omp parallel for
	for(int i = 0; i < vectorsize; i++)
		A[i] = 99.99999999999999999;

	cpu();
	simd();
	gpu();

	std::cout << omp_get_num_devices() << " devices" << std::endl;
	std::cout << omp_get_max_threads() << " threads" <<std::endl;
	return 0;
}

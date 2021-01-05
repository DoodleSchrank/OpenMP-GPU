#include<pthread.h>
#include<unistd.h> 
#include<stdlib.h>
#include <iostream>
#include <chrono>

#define MATSIZE 10
#define MAXITERATIONS 100000000


//Each thread computes single element in the resulting matrix
void *mult(void* arg) 
{ 
	int *data = (int *)arg;
	int k = 0, i;
    int x = data[0];
	for(int iter = 0; iter < MAXITERATIONS; iter++)
    {
        for (i = 1; i <= x; i++)
            k += data[i]*data[i+x];
    }
	
	int *p = (int*)malloc(sizeof(int));
		*p = k; 
	
	pthread_exit(p);
} 

int main()
{ 

	int matA[MATSIZE][MATSIZE];
    int matB[MATSIZE][MATSIZE];
    int matC[MATSIZE][MATSIZE];

	int i,j,k;

    // Generating random values in matA and matB, initializing matC with 0s
	for (i = 0; i < MATSIZE; i++) {
        for (j = 0; j < MATSIZE; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
            matC[i][j] = 0;
        }
	}
	
	pthread_t *threads;
	threads = new pthread_t[MATSIZE*MATSIZE];
	
	int count = 0; 
	int* data = NULL;
	auto start = std::chrono::high_resolution_clock::now();

	for (i = 0; i < MATSIZE; i++)
		for (j = 0; j < MATSIZE; j++)
			{ 
				
			//storing row and column elements in data 
			data = new int[20];
			data[0] = MATSIZE;
	
			for (k = 0; k < MATSIZE; k++)
				data[k+1] = matA[i][k]; 
	
			for (k = 0; k < MATSIZE; k++)
				data[k+MATSIZE+1] = matB[k][j];
			
			//creating threads 
				pthread_create(&threads[count++], NULL, 
							mult, (void*)(data)); 
				
					} 

	for (i = 0; i < MATSIZE*MATSIZE; i++)
	{ 
	    void *k;
	    //Joining all threads and collecting return value
	    pthread_join(threads[i], &k);
	    matC[i / MATSIZE][i % MATSIZE] = *(int*) k;
	}
	auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " seconds" << std::endl;

    return 0;
} 


#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4
#define NUM_END 200000

int main()
{
	int counter = 0;
	int i;
	
	double start_time, end_time;

	omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();

#pragma omp parallel 
	{
		#pragma omp for schedule(static)
		for (i = 0; i <= NUM_END; i++) {
			if (isPrime(i)){
#pragma omp critical (counter)
				counter++;
			}
			//sum += i;
			//printf("(%d/%d) : %d\n",omp_get_thread_num(),omp_get_num_threads(),i);
		}
	}
	end_time = omp_get_wtime();
	//printf("sum = 1+2+..+%d = %d\n", END_NUM, sum);
	
	printf("Prime Counter (1+2+..+%d) : %d\n", NUM_END, counter);
	printf("time elapsed: %lfs\n", end_time - start_time);
	return 1;
}

int isPrime(int x) {
	int i;
	if (x <= 1) return 0;
	for (i = 2; i<x; i++) {
		if ((x%i == 0) && (i != x)) return 0;
	}
	return 1;  //true=1, false=0;
}



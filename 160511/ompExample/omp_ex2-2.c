#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4
#define NUM_END 8

int main ()
{ 
	int i;
	omp_set_num_threads(NUM_THREADS);
	printf("program starts!\n");
#pragma omp parallel
	{
		printf("before for!\n");

		#pragma omp for
		for (i = 0; i < NUM_END; i++) printf("i=%d (%d/%d)\n",i,omp_get_thread_num(),omp_get_num_threads());

		printf("after for!\n");
	}
	printf("program ends!\n");

	return 1;
}

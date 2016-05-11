#include <omp.h>
#include <stdio.h>

void main()
{	
	omp_set_num_threads(8);
#pragma omp parallel
	{
		printf("Hello World! Thread#: %d , Total Thread#:%d\n", omp_get_thread_num(),omp_get_num_threads());
	}
}

#include <omp.h>
#include <stdio.h>

void main()
{	
#pragma omp parallel
	{
		printf("Hello World!\n");
	}
}

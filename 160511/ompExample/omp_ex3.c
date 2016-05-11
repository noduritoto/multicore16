#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

#define NX 1000
#define NM NX
#define NY NX

int a[NX * NM];
int b[NM * NY];
int m[NX * NY];

#define A(i, n) a[(i) + NX * (n)]
#define B(n, j) b[(n) + NM * (j)]
#define M(i, j) m[(i) + NX * (j)]

void printMatrix(int* mat, int X, int Y)
{
	int i,j;
	for (j=0;j<Y;j++) {
		for (i=0;i<X;i++) {
			printf("%4d ",mat[i+j*X]);
		}
		printf("\n");
	}
}

int main()
{
    int i, j, n;
	double t1,t2;
    /* Initialize the Matrix arrays */

	omp_set_num_threads(NUM_THREADS);
	t1=omp_get_wtime();
#pragma omp parallel for default(shared) private(n, i)
    for (n = 0; n < NM; n++) {
	for (i = 0; i < NX; i++) {
	    A(i, n) =3;
	}
    }
#pragma omp parallel for default(shared) private(n, j)
    for (j = 0; j < NY; j++) {
	for (n = 0; n < NM; n++) {
	    B(n, j) = 2;
	}
    }
 
#pragma omp parallel for default(shared) private(i, j)
    for (j = 0; j < NY; j++) {
	for (i = 0; i < NX; i++) {
	    M(i, j) = 0;
	}
    }
 
    /* Matrix-Matrix Multiplication */
#pragma omp parallel for default(shared) private(i, j, n)
    for (j = 0; j < NY; j++) {
	for (n = 0; n < NM; n++) {
	    for (i = 0; i < NX; i++) {
		M(i, j) = M(i, j) + A(i, n) * B(n, j);
	    }
	}
    }
	t2=omp_get_wtime();

//	printMatrix(m,NX,NY);
	printf("computation time:%lf, using %d threads\n",t2-t1,NUM_THREADS);
    return 0;
}


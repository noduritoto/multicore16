#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4
#define M 8
#define N 8

void mxv_row(int m,int n,double *a,double *b,double *c);

int main()
{
	double* Mat;
	double* Vec;
	double* Result_Vec;
	int i,j;

	Mat = (double*)malloc(M*N*sizeof(double));
	Vec = (double*)malloc(N*sizeof(double));
	Result_Vec = (double*)malloc(N*sizeof(double));

	for (i=0;i<M;i++)
		for (j=0;j<N;j++) Mat[i*N+j]=1.0;

	for (i=0;i<N;i++) Vec[i]=2.0;

	mxv_row(M,N,Result_Vec,Mat,Vec);

	for (j=0;j<N;j++) printf("%.1lf ",Result_Vec[j]);
	printf("\n");

	return 0;
}


void mxv_row(int m,int n,double *a,double *b,double *c)
{
	int i, j;
	double sum;

#pragma omp parallel for default(none) private(i,j,sum) shared(m,n,a,b,c)
	for (i=0; i<m; i++) {
		sum = 0.0;
		for (j=0; j<n; j++)
			sum += b[i*n+j]*c[j];
		a[i] = sum;
	} 
}

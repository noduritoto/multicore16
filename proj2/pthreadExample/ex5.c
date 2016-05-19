#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
 {
   double      *a;
   double      *b;
   double     sum; 
   int     veclen; 
 } DOTDATA;

#define NUMTHRDS 4
#define VECLEN 100000
   DOTDATA dotstr; 
   pthread_t callThd[NUMTHRDS];
   pthread_mutex_t mutexsum;

void *dotprod(void *arg)
{
   int i, start, end, len ;
   long offset;
   double mysum, *x, *y;
   offset = (long)arg;
 
   len = dotstr.veclen;
   start = offset*len;
   end   = start + len;
   x = dotstr.a;    y = dotstr.b;
   mysum = 0;
   for (i=start; i<end ; i++) mysum += (x[i] * y[i]);
   pthread_mutex_lock (&mutexsum);
   dotstr.sum += mysum;
   printf("Thread %ld did %d to %d: mysum=%f global sum=%f\n",offset,start,end,mysum,dotstr.sum);
   pthread_mutex_unlock (&mutexsum);
   pthread_exit((void*) 0);
}

int main (int argc, char *argv[])
{
  long i;
  double *a, *b;
  void *status;

  a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
  b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
  
  for (i=0; i<VECLEN*NUMTHRDS; i++) {
    a[i]=1;
    b[i]=a[i];
  }

  dotstr.veclen = VECLEN; 
  dotstr.a = a; 
  dotstr.b = b; 
  dotstr.sum=0;

  pthread_mutex_init(&mutexsum, NULL);

  for(i=0;i<NUMTHRDS;i++) pthread_create(&callThd[i], NULL, dotprod, (void *)i);

  for(i=0;i<NUMTHRDS;i++) pthread_join(callThd[i], &status);
  printf ("Sum =  %f \n", dotstr.sum);

  free (a);
  free (b);
  pthread_mutex_destroy(&mutexsum);
  pthread_exit(NULL);
} 


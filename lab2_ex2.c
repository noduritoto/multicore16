#include <pthread.h> 
#include <stdio.h> 

#define NUM_THREAD 2
#define NUM_END 1000

int sum(int* arr);

typedef struct _thread_data {
  int* arr;
  int istart;
  int iend;
  int result;
} thread_data;

void *sumThread(void* t) 
{ 
  int i,istart, iend;
  int ans=0;

  istart=((thread_data*)t)->istart;
  iend=((thread_data*)t)->iend;
  for (i=istart;i<iend;i++) ans+=((thread_data*)t)->arr[i];
  ((thread_data*)t)->result=ans;
  pthread_exit(NULL);
} 


int main (int argc, char *argv[]) { 
  int int_arr[NUM_END];
  int i,s;

  for (i=0;i<NUM_END;i++) int_arr[i]=i+1;
  s=sum(int_arr);
  printf("sum=%d\n",s);
  return 0;
}


int sum(int* arr)
{
  pthread_t threads[NUM_THREAD]; 
  thread_data t[NUM_THREAD];
  void* status;
  int result=0;
  int i,rc;

  for (i=0;i<NUM_THREAD;i++) {
    t[i].istart=(i*NUM_END)/NUM_THREAD;
    t[i].iend=((i+1)*NUM_END)/NUM_THREAD;
    t[i].arr=arr;
    rc = pthread_create(&threads[i], NULL, sumThread, (void *)&t[i]); 
  }
  for(i=0;i<NUM_THREAD;i++) {
    pthread_join(threads[i], &status);
    result += t[i].result;
  }
  return result;
} 


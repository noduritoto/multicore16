#include <pthread.h> 
#include <stdio.h> 

static long num_steps = 100000; 

void *c(void* i)
{
   double x;
    int i;
    int i_start, i_end;
    double step;

    i_start = my_id * (num_steps/num_threads);
    i_end = i_start + (num_steps/num_threads);
    step = 1.0/(double)num_steps;
    
    for (i=i_start;i<i_end;i++) { 
      x=(i+0.5)*step;
      sum=sum+4.0/(1.0+x*x);
    }
    sum = sum*step;

}
void main(int argc, char

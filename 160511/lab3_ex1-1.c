#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4
#define END_NUM 10000

int main ()
{
        int i;
        int sum=0;
        double start_time, end_time;
        omp_set_num_threads(NUM_THREADS);
        start_time = omp_get_wtime( );
#pragma omp parallel
        {
                #pragma omp for reduction(+:sum)
                for (i = 1; i <= END_NUM; i++) {
                        sum+=i;
                        //printf_f("(%d/%d) : %d\n",omp_get_thread_num(),omp_get_num_threads(),i);
                }
        }
        end_time = omp_get_wtime( );
        printf("sum = 1+2+..+%d = %d\n",END_NUM,sum);
        printf("time elapsed: %lfs\n",end_time-start_time);
        return 1;
}



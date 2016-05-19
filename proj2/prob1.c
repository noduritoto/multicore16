#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//#define NUM_THREADS 4
#define NUM_END 200000

int main(int argc, char* argv[])
{
        int counter = 0;
        int i;

        double start_time, end_time;
	
	if (argc != 3) {
		printf("input error! \n");
   		fputs("error! wrong option! ex> ./a.out <scheduleType-int> <numThread-int> \n", stderr);
    		exit(1);
	}
        omp_set_num_threads(atoi(argv[2]));
	//printf("%d : thread num", atoi(argv[2]));
	printf("hello world! start count prime number \n");
        start_time = omp_get_wtime();

	switch(atoi(argv[1])){
		case 1:
			printf("schedule(static)\n");
        		start_time = omp_get_wtime();
			#pragma omp parallel
        		{
				#pragma omp for reduction(+:counter) schedule(static)
                			for (i = 0; i <= NUM_END; i++) {
                        			if (isPrime(i)){
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

			break;
		
		case 2:
			printf("schedule(dynamic, 4)\n");
		    	start_time = omp_get_wtime();
                        #pragma omp parallel
                        {       
                                #pragma omp for reduction(+:counter) schedule(dynamic, 4)
                                        for (i = 0; i <= NUM_END; i++) {
                                                if (isPrime(i)){
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

			break;
		
		case 3:
			printf("schedule(guided, 4)\n");
                        start_time = omp_get_wtime();
                        #pragma omp parallel
                        {       
                                #pragma omp for reduction(+:counter) schedule(guided, 4)
                                        for (i = 0; i <= NUM_END; i++) {
                                                if (isPrime(i)){
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

			break;
		
		default:
			printf("wrong 1st argument!");
			exit(1);
	}

#pragma omp parallel
        {
#pragma omp for reduction(+:counter) schedule(dynamic, 2)
                for (i = 0; i <= NUM_END; i++) {
                        if (isPrime(i)){

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



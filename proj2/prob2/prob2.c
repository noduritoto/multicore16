#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PARKING_SPACES 10
#define NUM_CARS 40

int places = 10;
pthread_mutex_t mutex;
pthread_cond_t conditionVar;


//void enter();
//void leave();
void *parking(void* carNum); //carNum is thread id, same..

int main(int argc, char *argv[]){

	pthread_t cars[NUM_CARS];
	int rc ,i; //rc is pthread state code
	
	rc = pthread_mutex_init(&mutex, NULL);	
	if(rc != 0){ printf("init error!! \n"); }
	
	rc =pthread_cond_init (&conditionVar, NULL);
	if(rc != 0){ printf("init error!! \n"); }
	
	srand( (unsigned)time(NULL)+(unsigned)getpid());

	printf("hello world!! \n\n");	
	printf("num of available places is :%d\n -- start --\n\n", places);
	for(i=0; i<NUM_CARS; i++){
		rc=pthread_create(&cars[i], NULL, parking, (void*)i);
		
		if(rc){
			printf("ERROR code is %d\n", rc); 
      			exit(-1);
		} 	
	}

	for(i=0; i<NUM_CARS; i++){
		pthread_join(cars[i], NULL);
	}	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&conditionVar);
	pthread_exit(NULL);
}

/*
void enter(){
	printf("enter function\n");	
	pthread_mutex_lock(&mutex);
	while(places == 0){
		pthread_cond_wait(&conditionVar, &mutex);
	}
	places --;
	pthread_mutex_unlock(&mutex);
}

void leave(){
	printf("leave function\n");
	pthread_mutex_lock(&mutex);
	places ++;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&conditionVar);
}
*/

void *parking(void *carNum){
	int carNumber, state;
	carNumber =  (int)carNum;
	//srand( (unsigned)time(NULL)+(unsigned)getpid());
	//printf("It's me, thread #%d!\n", carNumber); 
	while(1){
		
		//enter processing////////////////////////////////
		state = usleep(rand()%100000);
		if(state != 0) { printf("usleep error! \n");}
		state =pthread_mutex_lock(&mutex);
		if(state != 0) { printf("mutex lock  error! \n");}
       		while(places == 0){
			printf("=== condition Variable Area : Wait !! \n");
               		pthread_cond_wait(&conditionVar, &mutex);
        	}
        	places --;
		printf("%d is entered.\n", carNumber);
		printf("num of available places is :%d\n", places);
        	pthread_mutex_unlock(&mutex);
		//////////////////////////////////////////////////

		//leave processing////////////////////////////////
		//usleep(rand()%200000);
		pthread_mutex_lock(&mutex);
        	places ++;
		printf("%d is left.\n", carNumber);
		printf("num of available places is :%d\n", places);
        	pthread_mutex_unlock(&mutex);
        	pthread_cond_signal(&conditionVar);
		///////////////////////////////////////////////////
		pthread_exit(NULL);
	}
} 

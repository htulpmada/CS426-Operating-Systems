#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/wait.h>

#define MAX_TIME 5
#define NUM_SEATS 3
#define OFFICE_HOURS 20

pthread_mutex_t helpMutex;

sem_t studentSem;
sem_t taSem;

int open = NUM_SEATS;
int NUM_STUDENTS = 5;
int waiting = 0;
int slp = 0;

void *studentFunction(void *arg){
	int num = *((int *) arg);
	int progTime = (rand() % MAX_TIME);
	printf("student: %d, programming for %d sec\n",num, progTime);
	sleep(progTime);
	while(1){
		progTime = (rand() % MAX_TIME) + 1;
		pthread_mutex_lock(&helpMutex);
		if(open > 0){
			waiting++;
			open--;
			printf("student %d sits down, # waiting: %d\n",num,waiting);
			sem_post(&studentSem);
			pthread_mutex_unlock(&helpMutex);
			sem_wait(&taSem);
			if(slp==1){
				printf("student %d woke up the TA\n",num);
				slp=0;
			}
			printf("student %d is currently seeing the TA\n",num);
		}
		else{
			printf("Office full, student %d will return\n", num);
			pthread_mutex_unlock(&helpMutex);
		}
		printf("student: %d, programming for %d sec\n",num, progTime);
		sleep(progTime);
	}

}

void *taFunction(void *arg){
	int helpTime = 0;
	while(1){
		helpTime = (rand() % MAX_TIME) + 1;
		if(waiting > 0){
			if(slp==1){
				//printf("TA Woken up\n");
				//slp = 0;
			}
			sem_wait(&studentSem);
			pthread_mutex_lock(&helpMutex);
			waiting--;
			open++;
			printf("helping student for %d seconds, students waiting: %d\n",helpTime,waiting);
			sem_post(&taSem);
			pthread_mutex_unlock(&helpMutex);
			sleep(helpTime);
		}
		else{
			if(slp==0){
				slp = 1;
				printf("nobody to help TA is Sleeping\n");
				//sleep(helpTime);
			}
		}
	}
}

int main(int argc, char **argv){

	if(argc < 2){
		printf("invalid arguments\n");
		exit(0);
	}
	
	NUM_STUDENTS = atoi(argv[1]);
	printf("Office Open for %d seconds\n",OFFICE_HOURS);

	pthread_t taThread;
	pthread_t studentThread[NUM_STUDENTS];
	
	int index[NUM_STUDENTS];
	for(int i = 0; i < NUM_STUDENTS; i++ ){
		index[i]=i;
	}
	
	sem_init(&studentSem, 0, 0);
	sem_init(&taSem, 0, 0);
	pthread_mutex_init(&helpMutex, NULL);
	pthread_create(&taThread, NULL, taFunction, NULL);

	for(int i = 0; i < NUM_STUDENTS; i++){
		pthread_create(&studentThread[i], 0, studentFunction, (void*) &index[i]);
	}
	sleep(OFFICE_HOURS);
	printf("Office closed\n");
	abort();

}


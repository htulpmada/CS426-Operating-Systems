#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "pid_manager.h"
#include "pid_manager.c"

int MAXTIME = 5;
int numThread = 3;
void *testPid(void *args);


int main(){
    int go;
    int sTime[numThread];
    pthread_t t[numThread];
    srand(time(NULL));
    go = allocate_map();
    if(go!=0){exit(1);}
    
    for(int i = 0; i < numThread; i++){
        sTime[i] = (rand() % MAXTIME);
    }

    for(int i = 0; i < numThread; i++){
        go = pthread_create(&t[i], NULL, testPid,(void *) &sTime[i]);
        if(go!=0){exit(1);}
    }
    
    for(int i = 0; i < numThread; i++){
        go = pthread_join(&t[i], NULL);
        if(go!=0){exit(1);}
    }
    //wait(NULL);
    exit(0);

}

void *testPid(void *args){
    int sTime;
    int p;
    
    sTime = *((unsigned int *) args);
//    sleep(sTime);
    p = allocate_pid();
    printf("test: %d\n",p);
    sleep(sTime);
    printf("slept for %d seconds\n",sTime);
    release_pid(p);
    
    return NULL;
}
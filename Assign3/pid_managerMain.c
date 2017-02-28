#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "pid_manager.h"
#include "pid_manager.c"

int MAXTIME = 10;
int numThread = 30;
void *testPid(void *args);


int main(){
    int go;
    int sTime[numThread];
    pthread_t t[numThread];

    go = allocate_map();
    if(go!=0){exit(1);}
    
    for(int i = 0; i < numThread; i++){
        sTime[i] = (rand() % MAXTIME);
    }

    for(int i = 0; i < numThread; i++){
        go = pthread_create(&t[i], NULL, testPid,(void *) &sTime[i]);
//        sleep(sTime[i]-1);
      if(go!=0){exit(1);}
    }
    
    for(int i = 0; i < numThread; i++){
        go = pthread_join(t[i], NULL);
        if(go!=0){exit(1);}
    }
    wait(NULL);
    exit(0);

}

void *testPid(void *args){
    int sTime;
    int p;
    
    sTime = *((unsigned int *) args);
    p = allocate_pid();
    printf("testing thread: %d\n",p);
    sleep(sTime);
    release_pid(p);
    printf("thread: %d sleeping for %d Seconds\n",p,sTime);

    return NULL;
}
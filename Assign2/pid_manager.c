//////////////////
//  Adam Pluth  //
//  CS 426 OS   //
//   2/14/17    //
// pid_manager  //
//     3.20     //
//////////////////


#include <stdio.h> // fprintf, printf
#include <string.h>

#include "pid_manager.h"

int go;

int allocate_map(){
    for(int i = 0; i < MAX_PID; i++){
            pid_map[i] = 0;
    }

    go = pthread_mutex_init(&lock, NULL); 

    if(go!=0){go = -1;}
    return go;
}

int allocate_pid(){
    int go;
    go = pthread_mutex_lock(&lock);

    if(go!=0){return go;}
    else if(availible < 1){return -1;}
    int i;
    for(i = 0; i < MAX_PID; i++){
            if(pid_map[i] == 0){
                availible--;
                pid_map[i] = 1;
                return i + MIN_PID;
            }
    }
    return go;
}

void release_pid(int pid){
    int go;
    
    if(pid < MIN_PID || pid > MAX_PID){return;}

    go = pthread_mutex_lock(&lock);
    if(go!=0){return;}
    pid_map[MIN_PID + pid] = 0;
    availible++;
    go = pthread_mutex_unlock(&lock);

    return;
}



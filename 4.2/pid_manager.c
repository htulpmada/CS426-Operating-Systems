//////////////////
//  Adam Pluth  //
//  CS 426 OS   //
//   2/14/17    //
// pid_manager  //
//     4.20     //
//////////////////


#include <stdio.h> 
#include <string.h>

#include "pid_manager.h"

int go = 0;

int allocate_map(){
    for(int i = 0; i < MAX_PID; i++){
            pid_map[i] = 0;
    }

    return go;
}

int allocate_pid(){
    
    int go = 0;
    
    if(availible < 1){return -1;}
    int i = 0;
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
    int go = 0;
    
    if(pid < MIN_PID || pid > MAX_PID){return;}

    if(go!=0){return;}
    pid_map[MIN_PID + pid] = 0;
    availible++;

    return;
}



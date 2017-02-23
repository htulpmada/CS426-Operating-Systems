//////////////////
//  Adam Pluth  //
//  CS 426 OS   //
//   2/14/17    //
// pid_manager  //
//     3.20     //
//////////////////


#include <stdio.h> 
#include <string.h>

#include "pid_manager.h"

int go;

int main(){
    
    go = allocate_map();
    
    if(!go) printf("Success!\n");
    
    else printf("didn't work\n");
    
    for(int i = 1; i != T; i++){
        go = allocate_pid();
        printf("pid: %d allocated\n",go);
        
        release_pid(go);
        printf("pid: %d released\n",go);
    }
    printf("pids availible: %d\n",availible);
    
    return 0;
}

int allocate_map(){
    
    for(int i = 0; i < MAX_PID; i++){
            pid_map[i] = 0;
    }
    return go;
}

int allocate_pid(){
    int go;

    if(availible < 1){return -1;}

    int i;
    for(i = 0; i <= MAX_PID; i++){
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
    
    if(pid < MIN_PID || pid > MAX_PID){printf("Invalid PID\n");return;}

    pid_map[MIN_PID + pid] = 0;
    availible++;

    return;
}



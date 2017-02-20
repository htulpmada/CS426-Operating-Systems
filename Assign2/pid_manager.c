//////////////////
//  Adam Pluth  //
//  CS 426 OS   //
//   2/14/17    //
// pid_manager  //
//     3.20     //
//////////////////


#include <stdio.h> // fprintf, printf
#include <unistd.h> // fork()
//#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait();
#include <stdlib.h> // wait();
#include <string.h>

#include "pid_manager.h"

int allocate_pid(){
	for(int i = 0; i < MAX_PID; i++){
		if(pid_map[i] == 0){
			pid_map[i] = 1;
			return i + MIN_PID;
		}
	}
	return 1;
}

int allocate_map(){
	for(int i = 0; i < MAX_PID; i++){
		pid_map[i] = 0;
	}
	return 1;
}

void release_pid(int pid){
	pid_map[MIN_PID + pid] = 0;
}



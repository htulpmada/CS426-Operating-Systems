#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pid_manager.c"

int numThread = 100;

int main()
{
    int time[RANGE];
    allocate_map();
    for(int i = 0; i < numThread; i++){
        int j = allocate_pid();
        fprintf(stdout, "Allocated PID: %d \n", j);
        release_pid(j);
    }
}

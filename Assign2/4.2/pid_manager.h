
#ifndef PID_MANAGER_H
#define PID_MANAGER_H

#include <pthread.h>

int MAX_PID = 5000;
int MIN_PID = 300;
int RANGE = 4700;
int pid_map[4700];
int availible = 4700;
pid_t id;

int allocate_pid();
int allocate_map();

void release_pid(int pid);



#endif /* PID_MANAGER_H */


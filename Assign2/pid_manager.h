
#ifndef PID_MANAGER_H
#define PID_MANAGER_H

#include <pthread.h>

int MAX_PID = 5000;
int MIN_PID = 500;
int RANGE = 4500;
int pid_map[4500];
int availible = 499;
pid_t id;
pthread_mutex_t lock;

int allocate_pid();
int allocate_map();

void release_pid(int pid);



#endif /* PID_MANAGER_H */


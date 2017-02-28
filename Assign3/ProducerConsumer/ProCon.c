//////////////////
//  Adam Pluth  //
//  CS 426 OS   //
//   2/22/17    //
//  producer-   //
//  consumer    //
//////////////////

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "buffer.h"

#define MAXTIME 10
#define numThread 30

int go;
int index = 0;
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t lock;

void produce(void *args);
void consume(void *args);


int main(int argc, char** argv) {
    
    
    // 1. Get command line arguments argv[1],argv[2],argv[3]
    if(argc < 3){
        printf("Wrong Arguments\n");
        exit(1);
    }

    int slp = atoi(argv[1]);
    int pros = atoi(argv[2]);
    int cons = atoi(argv[3]);
    
    pthread_t p[pros];
    pthread_t c[cons];

    for(int i = 1; i < argc; i++){
        printf("%s\n",argv[i]);
    }
    
    //2. Initialize buffer
    go = pthread_mutex_init(&lock, NULL); 
    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
    //3. Create producer thread(s)
    for(int i = 0; i <= pros; i++){
        go = pthread_create(&p[i], NULL, produce,(void *) slp);
        if(go!=0){exit(1);}
    }

    //4. Create consumer thread(s)
    for(int i = 0; i <= cons; i++){
        go = pthread_create(&c[i], NULL, consume,(void *) slp);
        if(go!=0){exit(1);}
    }
    //5. Sleep
    sleep(slp);
    for(int i = 0; i < BUFFER_SIZE; i++){
        printf("%d :",buffer[i]);
    }
    //6. Exit 
    exit(0);

}

void produce(void *args){

    while(1){//add empty and full semaphores
        int j = rand() % MAXTIME;
        sleep(j);
        go = pthread_mutex_lock(&lock);
        insert_item(j);
        printf("Inserted: %d\n",j);
        go = pthread_mutex_unlock(&lock);
        
    }
}

void consume(void *args){

    while(1){
        int j = rand() % MAXTIME;
        sleep(j);
        go = pthread_mutex_lock(&lock);
        remove_item();
        printf("Removed Item\n");
        go = pthread_mutex_unlock(&lock);
        
    }
}



int insert_item(buffer_item item) {
    buffer[index] = item;
    index++;
/* insert item into buffer
return 0 if successful, otherwise
return -1 indicating an error condition */
    return 0;
}
int remove_item(buffer_item item){
    buffer[index] = NULL;
    index--;
    
/* remove an object from
placing it in item
return 0 if successful, otherwise
return -1 indicating an error condition */
    return 0;
}
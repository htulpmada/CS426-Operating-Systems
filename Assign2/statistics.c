//////////////////
//  Adam Pluth  //
//  CS 426 OS   //
//   2/14/17    //
//  Statistics  //
//////////////////


#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h> // wait();
#include <sys/types.h> // pid_t
#include <pthread.h> // pthread_attr_t


int a,mi,ma;

pthread_attr_t attr1;
pthread_attr_t attr2;
pthread_attr_t attr3;

void avg(char** argv);
void min(char** argv);
void max(char** argv);


int main(int argc, char** argv) {
    
            // program start //
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    pthread_t id1;
    pthread_t id2;
    pthread_t id3;

    pthread_create(&id1,&attr1,avg,argv);
    pthread_create(&id2,&attr2,min,argv);
    pthread_create(&id3,&attr3,max,argv);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    pthread_join(id3,NULL);
    printf("The Average value is %d\n",a);
    printf("The Minimum value is %d\n",mi);
    printf("The Maximum value is %d\n",ma);
    return 0;
}

void avg(char** argv){
    a = 0;
    int size  = sizeof(argv)/sizeof(argv[0][0]);
    for (int i=1; i < size;i++){
        a+=atoi(argv[i]);
    }
    a=a/(size-1);
    pthread_exit(0);
}

void min(char** argv){
    mi = atoi(argv[1]);
    int size  = sizeof(argv)/sizeof(argv[0][0]);
    for (int i=2; i < size;i++){
        if(atoi(argv[i])< mi){mi = atoi(argv[i]);}
    }
    pthread_exit(0);
}

void max(char** argv){
    ma = atoi(argv[1]);
    int size  = sizeof(argv)/sizeof(argv[0][0]);
    for (int i=2; i < size;i++){
        if(atoi(argv[i]) > ma){ma = atoi(argv[i]);}
    }
    pthread_exit(0);
}


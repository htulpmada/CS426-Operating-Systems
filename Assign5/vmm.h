#include "stdlib.h"
#include "stdio.h"
#include <pthread.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#define FRAMES 256
#define PAGES 256
#define TRANS 16
#define PSIZE 256

typedef struct
{
	int lAddress;
	int pAddress;
	int pNum;
	int offset;
	int value;
} _address;

int pTable[Pages];
int tTable[TRANS][2];
int pMem[FRAMES][PSIZE];
int pFault = 0;
int fNum = 0;
int tCount = 0;//max 15
int tHit = 0;


struct addr adr = {0x00000000,0,0,0,0};



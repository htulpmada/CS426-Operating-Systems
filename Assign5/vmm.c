#include <stdlib.h>
#include <stdio.h>


#define FCOUNT 16
#define FSIZE 256
#define PSIZE 256
#define TSIZE 16
#define LMEMSIZE 256
#define PMEMSIZE 65536 // 2^16
#define PTABLESIZE 256

typedef struct
{
        int fNum;
        int valid;
} page_item;

typedef struct {
        int pNum;
        int fNum;
        int valid;
} table_item;


int main(int argc, char** argv){

	//init vars
	int totMemAcs = 0;
	int totPageFts = 0;
	int totTlbHits = 0;
	char pMem[PMEMSIZE];
	page_item dPage = {.valid = 0};
	page_item pTable[PTABLESIZE];
	
	//check args
	if(argv<3){
		printf("Sorry Wrong Args...../n");
	}

	//open files for reading then check for NULL
	FILE* backfp;
	FILE* addrfp;
	
	backfp = fopen("BACKING_STORE.bin","r");
        
        
	addrfp = fopen("addresses.txt","r");
	if(addrfp == NULL){
		printf("Sorry Wrong address file...../n");
		return 1;
	}
	if(backfp == NULL){
		printf("Sorry Wrong BACKING_STORE file...../n");
		return 1;
	}

	// init table and frames
	for(int i = 0; i < PTABLESIZE; i++){
		pTable[i] = dPage;
	}
	int emptyFrames[FCOUNT];
	int nextF = 0;
	int tHead = 0;
	int tempTSIZE = 0;
	table_item tlb[TSIZE];
	//vars for reading file
	char line[256];
	int pAddr,lAddr,pNum,pOffset,fNum;
	
	while(fgets(line, sizeof(line), addrfp)!=NULL){
		lAddr = atoi(line);
		// chop off only the 8 bits we need
		pNum = (lAddr & 0x0000FFFF) >> 8;
		pOffset = (lAddr & 0x000000FF);
		fNum = -1;
		if(tempTSIZE > 0){
			for(int z = 0; z < tempTSIZE; z++){
				int pos = (z + tHead);
				pos = pos % TSIZE;
				if(tlb[pos].valid && tlb[pos].pNum == pNum){
					totTlbHits++;
					fNum = tlb[pos].fNum;
				}
			}
		
		}
		if(fNum == -1){
			if(pTable[pNum].valid){
				fNum = pTable[pNum].fNum;
			}
			else{
				totPageFts++;
				fNum = nextF;
				if(emptyFrames[fNum] != 0){
					for(int h = 0; h < PTABLESIZE; h++){
						if(pTable[h].valid && pTable[h].fNum == fNum){
							pTable[h].valid = 0;
							break;
						}
					}
					for(int h = 0; h < tempTSIZE; h++){
						if(tlb[h].valid && tlb[h].fNum == fNum){
							tlb[h].valid = 0;
break;
						}
					}
				}
				// find item at newly read address
				fseek(backfp,(pNum * PSIZE), SEEK_SET);
				fread(&pMem[fNum*FSIZE], 1, PSIZE, backfp);
				pTable[pNum].fNum = fNum;
				pTable[pNum].valid = 1;
				emptyFrames[fNum] = 1;
				nextF = ++nextF % FCOUNT;
			}
			table_item newItem = {.pNum = pNum, .fNum = fNum, .valid = 1};
			tlb[tHead] = newItem;
			tHead = ++tHead % TSIZE;
			if(tempTSIZE < TSIZE){++tempTSIZE;}
		}
		pAddr = (fNum * FSIZE) + pOffset;
		char val = pMem[pAddr];
		printf("Virtual address: %d Physical address: %d Value: %d\n", lAddr, pAddr, val);
		totMemAcs++;
	}
	fclose(addrfp);
	fclose(backfp);
	printf("Number of Translated Addresses = %d\n", totMemAcs);
	printf("Page Faults = %d\n", totPageFts);
   	double pageFtRate = 1.0 * totPageFts / totMemAcs;
   	printf("Page Fault Rate = %.3f\n", pageFtRate);
   	printf("TLB Hits = %d\n", totTlbHits);
   	double TlbHitRate = 1.0 * totTlbHits / totMemAcs;
   	printf("TLB Hit Rate = %.3f\n", TlbHitRate);

	return 0;

}

////////////////
// Adam Pluth //
// CS 426 OS  //
//  2/14/17   //
//  shell.c   //
////////////////


#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <string.h>

#define MAX_LINE 80
#define HISTORY_LENGTH 10

void splitProcess(int* conCurr, char** args){
    pid_t pid = fork();
    if(pid == 0){
        // child
        execvp(args [0], args);
        // only continues if exec fails
        printf("Command Not Recognized!!\n");
        return;
    }
    else if(pid > 0){
        if(!conCurr){
            wait(NULL);
        }
    }
    else{
        fprintf(stderr, " fork() Failure\n");
        return;
    }
}


void displayHist(int CurrHistoryLen, char** history){
    printf("printing history\n");
    int bottomIndex = (CurrHistoryLen - 10) >= 0 ? (CurrHistoryLen - 10) : 0;
        for (int i = (CurrHistoryLen - 1); i >= bottomIndex; --i) {
          printf("%d: %s\n", i+1, history[i % 10]);
    }
}

int executeHist(int* conCurr, 
        int CurrHistoryLen, 
        char** history, 
        char** args, 
        char** line, 
        char** linePointer){
    
    char c = args[0][1];
    if(strcmp(args[0], "!!")==0){
            printf("last command\n");
    
        if( CurrHistoryLen < 1 ){
            printf("No Commands Yet\n");
            return 0;
        }
    
        free(line);
        line = malloc(MAX_LINE);
        int index = (CurrHistoryLen - 1) % 10;
        strcpy(line, history[index]);
        printf("%s", line);
        free(*linePointer);
        
        conCurr = parse(line, args, linePointer);
        
    }
    else if(isdigit(c)){
        // !n
        printf("!");
        printf("%c",c);
        printf("\n");

        args[0][0] = '0';
        int index = atoi(args[0]);
        if(index < 1 || index > ((CurrHistoryLen - 1) % 10)){
            printf("there is no history in that range\n");
            return 0;
        }
        else{
            free(line);
            line = malloc(MAX_LINE);
            strcpy(line, history[(index-1) % 10]);
            printf("%s", line);
            free(*linePointer);
            conCurr = parse(line, args, linePointer);
        }
    }
    else{
        // !a or !symbol
        return 0;
    }
    return 1;
}

int parse(char* line, char** args, char** linePointer) {
	// new pointers for parsing
	char* copy = malloc(MAX_LINE);
	linePointer = copy;
	
	strcpy(copy,line);
	char* temp = strtok(copy, " ");
	
	// tokenize line
	int i = 0;
	while(i != MAX_LINE / 2){
		if (temp == NULL){
			args[i-1][strlen(args[i-1])-1] = '\0';
			break;
		}
		args[i] = temp;
		temp = strtok(NULL, " ");
                i++;
	}
	if ( strcmp(args[i-1], "&") == 0) {
		args[i-1] = NULL;
		return 1;
	}
	return 0;
}




int main(void) {

	// command line args
	char *args[MAX_LINE/2 + 1]; 
	int argc = 0;

	// flag for main loop
	int should_run = 1;
	
	// used to track history
	char* history[HISTORY_LENGTH] = {NULL};
	int CurrHistoryLen = 0;

	// allocate memory for processing
	char** linePointer = malloc(sizeof(char *));
	*linePointer = NULL;
	char* line = NULL;
	int valid = 0;
	
	while(should_run){
		// print shell message
            printf("osh>");
            fflush(stdout);
            // reset data from last iteration
            free(*linePointer);
            if(valid != 0){
            	free(line);
            }
            valid = 0;
            line = malloc(MAX_LINE);
            char* args[MAX_LINE/2 + 1] = {(char *) NULL};
            // run concurrent?
            int* conCurr = 0;
		
            if(fgets(line, MAX_LINE, stdin)){
                if(strchr(line, '\n') == NULL){
                    fprintf(stderr, "Sorry %d Characters Is All You Get\n",MAX_LINE);
                    continue;
		}
		else if(strlen(line) == 1){
                    // no args
                    continue;
		}
		else{
                    conCurr = parse(line, args, linePointer);
		}
		// check requested command(s)
		if(strcmp(args[0], "exit") == 0){
                    printf("exiting\n");
                    should_run = 0;
                    continue;
                }
		else if(strcmp(args[0], "history") == 0){
                    displayHist(CurrHistoryLen, history);
                }
		else if(args[0][0] == '!'){
                    valid = executeHist(conCurr, CurrHistoryLen, history, args, line, linePointer);
                }
                else{
                    // any system calls go here
                    printf("System call:  ");
                    printf("%s",args[0]);
                    printf("\n");
                }
                //valid = 1;
                if(CurrHistoryLen>= HISTORY_LENGTH){
                    free(history[CurrHistoryLen % HISTORY_LENGTH]);
                }
                history[CurrHistoryLen++ % HISTORY_LENGTH] = line;
                
                splitProcess(conCurr, args);
                
	}
            else{// fget didn't work
            printf("\n");
            should_run = 0;
        }
    } //EOL end of loop
            
    printf("shell ran\n");
    return 0;
}

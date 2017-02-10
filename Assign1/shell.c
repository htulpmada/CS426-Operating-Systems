#include <stdio.h> // fprintf, printf
#include <unistd.h> // fork()
#include <sys/types.h> // pid_t
#include <string.h>

#define MAX_LINE 80
#define HISTORY_LENGTH 10

int main(void) {

	// command line args
	char *args[MAX_LINE/2 + 1]; 
	int argc = 0;

	// flag for main loop
	int should_run = 1;
	
	// used to track history
	char * history[HISTORY_LENGTH] = {NULL};
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
		int background = 0;
		
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
			//	background = parse(line, args, linePointer);
			}

			// check requested command(s)
			if(strcmp(args[0], "exit") == 0){printf("exiting");break;}
			else if(strcmp(args[0], "history") == 0){}
			else if(strcmp(args[0][0], "!") == 0){}

		}
		
	}

	printf("shell ran\n");
	return 0;
}

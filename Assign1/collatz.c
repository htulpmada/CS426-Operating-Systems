////////////////
// Adam Pluth //
// CS 426 OS  //
//  2/14/17   //
//  collatz   //
////////////////


#include <stdio.h> // fprintf, printf
#include <unistd.h> // fork()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait();
#include <stdlib.h> // wait();

pid_t id;

void collatz(int i);

int main(int argc, char** argv) {

	// program start //

	if ( argc == 2 && argv[argc-1] > 0){
		// valid input, fork process
		id = fork();

		// Error
		if ( id < 0 ) {
			fprintf(stderr, "Failed to Fork Process");
			return 1;
		}
		// Fork child 
		else if (id == 0) {
			collatz(atoi(argv[1]));
		}
		// Fork Parent
		else {
			wait(NULL);
		}
	}
	else{
		// Invalid input
		printf("Please enter a single positive integer\n");
		return 0;
	}


	return 0;
}

void collatz(int i){
	// base case
	if(i == 1){
		printf("%d\n",i);
	}
	// i is even
	else if ( i % 2 == 0) {
		printf("%d\n",i);
		collatz( i / 2 );
	}
	// i is odd
	else{
		printf("%d\n",i);
		collatz( 3 * i + 1 );
	}
}

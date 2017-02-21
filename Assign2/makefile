
all: pid stats 
	
pid:
	gcc -Wall -g -std=c99 -o pid_manager pid_managerMain.c -pthread
	

stats:
	gcc -Wall -g -std=c99 -o statistics statistics.c -pthread
	
clean:
	rm pid_manager statistics

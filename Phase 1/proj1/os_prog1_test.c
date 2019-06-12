//
//  os_prog1_test.c
//  
//
//  Created by Michael Geiger on 4/13/17.
//
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	pid_t pid_list[50];		// List of child process PIDs
	pid_t par;				// Parent pid
	pid_t child;			// PID of completed child
	int lim;				// Upper limit on number of processes
	int i, j;
	char fname[10];			// File name for program to be run
	
	lim = atoi(argv[1]);
	
	// Get and print parent PID
	par = getpid();
	printf("Parent pid is %d\n", (int)par);
	
	// Fork 10 child processes from parent process only
	for (i = 0; i < lim; i++) {

		// Make sure we're in the parent
		if (par == getpid()) {
			pid_list[i] = fork();
			if (pid_list[i] < 0) {
				fprintf(stderr, "Fork %d failed", i+1);
				return -1;
			}
			else if (pid_list[i] == 0) {
				//printf("Running child with pid %d\n", (int)getpid());
				sprintf(fname, "./test%d", i%5 + 1);
				execlp(fname, NULL);
			}
			else
				printf("Started child %d with pid %d\n", i+1, (int)pid_list[i]);
		}
	}

	// Set up parent to wait around for children
	if (par == getpid()) {
		for (j = 0; j < lim; j++) {
			child = wait(NULL);
			for (i = 0; i < lim; i++) {
				if (child == pid_list[i]) {
					printf("Child %d (PID %d) finished\n", i+1, child);
					break;
				}
			}
		}
	}
	return 0;
}

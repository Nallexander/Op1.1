/**
 * Game of luck: Implementation of the Gamemaster
 *
 * Course: Operating Systems and Multicore Programming - OSM lab
 * assignment 1: game of luck.
 *
 * Author: Nikos Nikoleris <nikos.nikoleris@it.uu.se>
 *
 */

#include <stdio.h> /* I/O functions: printf() ... */
#include <stdlib.h> /* rand(), srand() */
#include <unistd.h> /* read(), write() calls */
#include <assert.h> /* assert() */
#include <time.h>   /* time() */
#include <signal.h> /* kill(), raise() and SIG???? */

#include <sys/types.h> /* pid */
#include <sys/wait.h> /* waitpid() */

#include "common.h"

#define RAND() rand()%(Max+1)
#define SEED() srand((unsigned)time(NULL)^getpid())

int main(int argc, char *argv[])
{
        int i, seed;

        /* TODO: Use the following variables in the exec system call. Using the
	 * function sprintf and the arg1 variable you can pass the id parameter
	 * to the children
	 */

	char arg0[] = "./shooter";
	char arg1[10];
	char *args[] = {arg0, arg1, NULL};

	pid_t pid;
	int pfd[2];
	int send_pipe[6][2]; 
	int recieve_pipe[6][2];

	/* TODO: initialize the communication with the players */
	for (i = 0; i < NUM_PLAYERS; i++) {
	  pipe(send_pipe[i]);
	  pipe(recieve_pipe[i]);
	}

	for (i = 0; i < NUM_PLAYERS; i++) {
		/* TODO: spawn the processes that simulate the players */	  	
	  switch(pid=fork()){
	  case -1: // ERROR
	    perror("Could not create child process!\n");
	    exit(EXIT_FAILURE);
	  case 0: // CHILD PROCESS
	    // SHOOTER
	    execv(arg0, args);
	    printf("Executing in child process!\n");
	    exit(EXIT_SUCCESS);
	  default: // PARENT PROCESS
	    printf("Executing in parent process!\n");
	    printf("Child ID: %ld\n", (long) &pid);
	    break;
	  }
	}

	//seed = (int)(srand((unsigned)time(NULL)^getpid()));
	//int test = RAND();
	seed = rand();
	for (i = 0; i < NUM_PLAYERS; i++) {
		seed++;
		/* TODO: send the seed to the players */ 
		close(send_pipe[i][0]);
		write(send_pipe[i][1], seed, sizeof(seed));
		close(send_pipe[i][1]);
		printf("Sent %d to %d\n", seed, send_pipe[i][1]);
	}

	/* TODO: get the dice results from the players, find the winner */
	for (i = 0; i < NUM_PLAYERS; i++) {

	}
	printf("Master waiting for children\n");
	pid = wait(&pid);
	printf("master: player %d WINS\n", winner);
	
	/* TODO: signal the winner */


	/* TODO: signal all players the end of game */
	for (i = 0; i < NUM_PLAYERS; i++) {
	  close(pfd[0]);
	}

	printf("master: the game ends\n");

	/* TODO: cleanup resources and exit with success */
	for (i = 0; i < NUM_PLAYERS; i++) {

	}

	return 0;
}

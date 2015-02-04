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
	char arg2[3];
	arg2[2] = NULL;
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
	    shooter(i, send_pipe[i][0], recieve_pipe[i][1]);
	    /*if (dup2(send_pipe[i][0], STDIN_FILENO) < 0){
	      perror("Duplicate send descriptor failed!");
	      }
	    if (dup2(recieve_pipe[i][1], STDOUT_FILENO) < 0){
	      perror("Duplicate recieve descriptor failed!");
	      }
	    printf("SEND_PIPE[i][0] = %d\narg2[0] = %d\n", send_pipe[i][0], arg2[0]);
	    printf("Executing in child process!\n");	    
	    sprintf(arg1, "%d", i);
	    execv(arg0, args);
	    */
	    printf("Exiting\n");
	    exit(EXIT_SUCCESS);
	  default: // PARENT PROCESS
	    close(send_pipe[i][0]);
	    printf("Executing in parent process!\n");
	    printf("Child ID: %ld\n", (long) &pid);
	    break;
	  }
	}

	//seed = (int)(srand((unsigned)time(NULL)^getpid()));
	//int test = RAND();
	seed = time(NULL);
	printf("seed = %d", seed);
	for (i = 0; i < NUM_PLAYERS; i++) {
		seed++;
		/* TODO: send the seed to the players */ 
		
		write(send_pipe[i][1], &seed, sizeof(int));
		
		printf("Sent %d to %d\n", &seed, send_pipe[i][1]);
	}
	printf("Master waiting for children\n");
	/* TODO: get the dice results from the players, find the winner */
	int results = 0;
	for (i = 0; i < NUM_PLAYERS; i++) {
	  printf("Waiting for child to return score with descriptor %d\n", recieve_pipe[i][0]);
	  
	  read(recieve_pipe[i][0], &results, sizeof(int)); 
	  
	  
	}
	
	
	printf("master: player %d WINS\n", winner);
	
	/* TODO: signal the winner */


	/* TODO: signal all players the end of game */
	for (i = 0; i < NUM_PLAYERS; i++) {
	  
	  
	}

	printf("master: the game ends\n");

	/* TODO: cleanup resources and exit with success */
	for (i = 0; i < NUM_PLAYERS; i++) {
	  pid = wait(&pid);
	  close(send_pipe[i][1]);
	}

	return 0;
}

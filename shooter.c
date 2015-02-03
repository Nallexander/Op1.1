/**
 * Game of luck: Implementation of the players (shooters) binary
 *
 * Course: Operating Systems and Multicore Programming - OSM lab
 * assignment 1: game of luck.
 *
 * Author: Nikos Nikoleris <nikos.nikoleris@it.uu.se>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "common.h"

int main(int argc, char *argv[])
{
	int id = 0;
	int seed_rd_fd = argv[2][0];
	int score_wr_fd = argv[2][1];
	printf("seed_rd_fd = %d\n", seed_rd_fd);

	if (argc == 3)
		id = strtol(argv[1], NULL, 10);

	shooter(id, seed_rd_fd, score_wr_fd);
	
	return 0;
}

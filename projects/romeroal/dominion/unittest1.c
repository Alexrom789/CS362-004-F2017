/********************************************************************************************************************
* Name: Alejandro Romero
* Date: 10/16/2017
* Description: This is a unit test for the isGameOver() function of dominion.c. This test is used to determine if the
  game ends as it properly should when one of the end game conditions are met. 
********************************************************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <time.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTFUNCTION "isGameOver()"

int main() {

	int i, j = 0;
	int r = 0;
	int randomCard = 0;
	time_t t;
	struct gameState *G = malloc(sizeof(struct gameState));

	srand((unsigned)time(&t));


	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	//check game state in which there are no more province cards.
	G->supplyCount[province] = 0;
	r = isGameOver(G);

	printf("\t Testing return value when province count is set to 0.\n\t Expected return value: 1. Actual return value: %d\n", r);
	assert(r == 1);
	printf("\t PASS!\n");


	//Check gamestate when supply cards piles are all greater than 0.
	for (i = 0; i < treasure_map + 1; i++) {
		G->supplyCount[i] = 10;
	}
	r = isGameOver(G);

	printf("\t Testing return value when all supply card piles are greater than 0.\n\t Expected return value: 0. Actual return value: %d\n", r);
	assert(r == 0);
	printf("\t PASS!\n");

	//Test that game ends when three random card piles are empty

	printf("\t Testing 100 game states in which three random card piles are empty.\n");

	for (j = 0; j < 100; j++) {

		for (i = 0; i < 3; i++) {

			randomCard = rand() % 25;		

			if (G->supplyCount[randomCard] == 0) {
				i--;
			}

			G->supplyCount[randomCard] = 0;

		}

		r = isGameOver(G);
		assert(r == 1);

		for (i = 0; i < treasure_map + 1; i++) {
			G->supplyCount[i] = 10;
		}

	}

	printf("\t PASS!\n");


	printf("\n >>>>>Testing complete for %s: All test succesfully passed. <<<<<\n\n", TESTFUNCTION);

	return 0;

}
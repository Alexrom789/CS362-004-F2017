/********************************************************************************************************************
* Name: Alejandro Romero
* Date: 10/16/2017
* Description: This is a unit test for the updateCoins() function of dominion.c. This test is used to determine if the
  coins are properly updated as they are added to players hand and bonuses are applied.
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

#define TESTFUNCTION "updateCoins()"

int main() {

	int i, j = 0;
	int coins = 0;
	int randomCoin = 0;
	time_t t;
	struct gameState *G = malloc(sizeof(struct gameState));

	srand((unsigned)time(&t));


	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	//Test function for all players
	for (i = 0; i < MAX_PLAYERS; i++) {

		coins = 0;
		randomCoin = rand() % 3;		//Random copper/silver/gold coin.

		//Sets each players hand to contain coin cards.
		for (j = 0; j < G->handCount[i]; j++) {

			if (randomCoin == 0) {
				G->hand[i][j] = copper;
				coins += 1;
			}

			if (randomCoin == 1) {
				G->hand[i][j] = silver;
				coins += 2;
			}

			if (randomCoin == 2) {
				G->hand[i][j] = gold;
				coins += 3;
			}

		}


		//Test function
		updateCoins(i, G, 0);

		printf("\t FOR PLAYER  %d:\n", i + 1);

		printf("\t Testing if coin count was updated.\n\t +0: Expected coin count: %d. Actual coin count: %d \n", coins, G->coins);
		assert(coins == G->coins);
		printf("\t PASS!\n");


		//Test again to see if bonus effects work correctly.
		coins += 1;
		updateCoins(i, G, 1);

		printf("\t Testing if coin count was updated with bonus.\n\t +1: Expected coin count: %d. Actual coin count: %d \n", coins, G->coins);
		assert(coins == G->coins);
		printf("\t PASS!\n");


	}

	printf("\n >>>>>Testing complete for %s: All test succesfully passed. <<<<<\n\n", TESTFUNCTION);

	return 0;

}
/********************************************************************************************************************
* Name: Alejandro Romero
* Date: 10/16/2017
* Description: This is a unit test for the smithy card. It test various conditions of the game state to make sure 
  the card functions as it should.
********************************************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {

	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 100;
	int newCards = 3;
	int discarded = 1;
	int numPlayers = 2;
	struct gameState G, testG;
	int success_flag = 1;
	int cardpiles_same = 1;


	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, remodel, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	//Check if player who played smithy card has handcount go up by 3.
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.handCount[0] != G.handCount[0] + newCards - discarded) {
		success_flag = 0;
		printf("\tFAIL: Players hand count was incorrect after smithy was played. Expected %d, got %d\n", G.handCount[0] + newCards - discarded, testG.handCount[0]);
	}
	else {
		printf("\tPASS: Players hand count after playing smithy was correct. (+3)\n");
	}

	//Check that card came from the players own deck.
	if (testG.deckCount[0] != G.deckCount[0] - newCards) {
		success_flag = 0;
		printf("\tFAIL: Players deck count after playing smithy was not correct. Expected %d, got %d\n", G.deckCount[0] - newCards, testG.deckCount[0]);
	}
	else {
		printf("\tPASS: Players deck count after playing smithy was correct. (-3)\n");
	}

	//Check that other players state (handcount, deckcount and score) remains unchanged.
	if (testG.handCount[1] != G.handCount[1] || testG.deckCount[1] != G.deckCount[1] || scoreFor(1, &testG) != scoreFor(1, &G)) {
		success_flag = 0;
		printf("\tFAIL: Player 2's state has been altered.(hand count, deck count or score may have changed)\n");
	}
	else {
		printf("\tPASS: Player 2's hand count, deck count and score unchanged after player 1 played smithy\n");
	}



	//check that victory cards piles remain unchanged.
	if (testG.supplyCount[estate] != G.supplyCount[estate] || testG.supplyCount[duchy] != G.supplyCount[duchy] || testG.supplyCount[province] != G.supplyCount[province]) {
		success_flag = 0;
		printf("\tFAIL: Number of victory point cards have changed.\n");
	}
	else {
		printf("\tPASS: Number of victory point cards after playing smithy has remained the same.\n");
	}

	//check that kingdom card piles remain unchanged.
	for (i = 0; i < 10; i++) {

		if (testG.supplyCount[k[i]] != G.supplyCount[k[i]]) {
			success_flag = 0;
			cardpiles_same = 0;
			//printf("\tFAIL: Kingdom card pile of  did not contain the same number of cards\n");
		}
		else {
			cardpiles_same = 1;
			//printf("\tPASS: Kingdom card pile  contained the same number of cards.\n");
		}

	}

	if (cardpiles_same) {
		printf("\tPASS: Kingdom card pile  contained the same number of cards.\n");
	}
	else {
		printf("\tFAIL: Kingdom card pile of  did not contain the same number of cards\n");
	}


	if (success_flag) {
		printf("\n >>>>>Testing complete for %s: All test succesfully passed. <<<<<\n\n", TESTCARD);
	}
	else {
		printf("\n >>>>>Testing complete for %s: At least one test has failed. <<<<<\n\n", TESTCARD);
	}

	return 0;
}




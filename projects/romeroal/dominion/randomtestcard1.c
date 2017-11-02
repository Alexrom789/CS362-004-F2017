/***********************************************************************************************************************
* Name: Alejandro Romero
* Date: 11/1/2017
* Description: This is a random test for the Village card. It test various conditions of the game state to make sure
the card functions as it should.
************************************************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define TESTCARD "Village"

int main() {

	struct gameState GS;

	int seed = 1000;
	int testsPassed = 0, allPassedFlag = 0;
	int numPlayers = 2, currPlayer = 0;
	int deckSize, handSize, startHand, currHand, startNumActions, currNumActions;
	int handCountFail = 0, actionCountFail = 0;
	int i = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;

	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, remodel, tribute, smithy, council_room };

	srand(time(NULL));


	for (i = 0; i < 100000; i++) {

		//Intialize a game state randomly check that the variables are reasonable.
		initializeGame(numPlayers, k, seed, &GS);

		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);

		GS.deckCount[0] = deckSize - handSize;
		GS.handCount[0] = handSize;
		GS.numActions = rand() % 10;
		handPos = GS.hand[currPlayer][GS.handCount[currPlayer] - 1];


		//check the players starting hand and number of actions.
		startHand = GS.handCount[0];
		startNumActions = GS.numActions;


		//Activate the card
		cardEffect(village, choice1, choice2, choice3, &GS, handPos, &bonus);


		//check the players starting hand and number of actions after using card.
		currHand = GS.handCount[0];
		currNumActions = GS.numActions;
		
		//purposely test for a poor condition
		if (rand() % 100 == 1) {	
			currNumActions += 1;
		}


		
		allPassedFlag = 1;

		//run tests

		printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

		if (currHand != startHand) {
			printf("FAIL: drawn cards.\n");
			handCountFail++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: drawn cards.\n");
		}

		if (currNumActions != startNumActions + 2) {
			printf("FAIL: number of actions.\n");
			actionCountFail++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: number of actions.\n");
		}


		if (allPassedFlag == 1) {
			printf("All test successfull. \n");
			testsPassed++;
		}

	}


	printf(" \n");
	printf("----------------- Random test results for %s ----------------\n", TESTCARD);
	printf("\tPASSED: %d\n", testsPassed);
	printf("\tFAILED (hand): %d\n", handCountFail);
	printf("\tFAILED (actions): %d\n\n", actionCountFail);



	return 0;

}
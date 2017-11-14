/***********************************************************************************************************************
* Name: Alejandro Romero
* Date: 11/1/2017
* Description: This is a random test for the Smithy card. It test various conditions of the game state to make sure
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

#define TESTCARD "Smithy"


int main() {

	struct gameState GS;

	int seed = 1000;
	int testsPassed = 0, allPassedFlag = 0;
	int numPlayers = 2, currPlayer = 0;
	int deckSize, handSize, startDeck, currDeck, startHand, currHand, startDiscard, currDiscard;
	int deckCountFail = 0, handCountFail = 0, failedDiscardCount = 0;
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
		handPos = GS.hand[currPlayer][GS.handCount[currPlayer] - 1];


		//check state of the player's starting Deck, Hand, and Discard piles.
		startDeck = GS.deckCount[0];
		startHand = GS.handCount[0];
		startDiscard = GS.playedCardCount;


		//Activate the card
		cardEffect(smithy, choice1, choice2, choice3, &GS, handPos, &bonus);


		//check state of the player's Deck, Hand, and Discard piles after using the card.
		currDeck = GS.deckCount[0];
		currHand = GS.handCount[0];
		currDiscard = GS.playedCardCount;


	
		allPassedFlag = 1;

		//run tests

		printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

		if (currDeck != (startDeck - 3)) {
			printf("FAIL: Deck count.\n");
			deckCountFail++;
			allPassedFlag = 0;
		}
		else {
			printf("\tDeck count - PASS\n");
		}

		if (currHand != (startHand + 2)) {
			printf("PASS: Deck count.\n");
			handCountFail++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: card drawn.\n");
		}

		if (currDiscard != (startDiscard + 1)) {
			printf("FAIL: Cards discarded.\n");
			failedDiscardCount++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: Cards discarded.\n");
		}


		if (allPassedFlag == 1) {
			printf("All test successfull. \n");
			testsPassed++;
		}

	}

	printf(" \n");
	printf("----------------- Random test results for %s ----------------\n", TESTCARD);
	printf("\tPASSED: %d\n", testsPassed);
	printf("\tFAILED (deck): %d\n", deckCountFail);
	printf("\tFAILED (hand): %d\n", handCountFail);
	printf("\tFAILED (discard): %d\n\n", failedDiscardCount);



	return 0;

}
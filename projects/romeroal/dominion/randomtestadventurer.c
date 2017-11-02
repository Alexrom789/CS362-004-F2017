/***********************************************************************************************************************
* Name: Alejandro Romero
* Date: 11/1/2017
* Description: This is a random test for the Adventurer card. It test various conditions of the game state to make sure 
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

#define TESTCARD "adventurer"


int main() {

	struct gameState GS;

	int seed = 1000;
	int testsPassed = 0, allPassedFlag = 0;
	int testDraw = 0, failedDiscard = 0;
	int numPlayers = 2, currPlayer = 0, deckSize, handSize, randCard, randKCard;
	int copper, silver, gold;
	int beforeCoins = 0, afterCoins = 0;
	int i, j, n;
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;

	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, remodel, tribute, smithy, council_room };

	srand(time(NULL));


	for (i = 0; i < 100000; i++) {

		//Intialize a game state randomly check that the variables are reasonable.
		initializeGame(numPlayers, k, seed, &GS);
		beforeCoins = 0;
		afterCoins = 0;

		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);

		GS.deckCount[0] = deckSize - handSize;
		GS.handCount[0] = handSize;



		//Radomize each player's starting deck 
		for (j = 0; j < numPlayers; j++) {

			for (n = 0; n < GS.deckCount[j]; n++) {

				randCard = rand() % 51;	

				if (randCard == 1) {
					GS.deck[j][n] = copper;
				}
				else if (randCard == 2) {
					GS.deck[j][n] = silver;
				}
				else if (randCard == 3) {
					GS.deck[j][n] = gold;
				}
				else {
					randKCard = rand() % 10;
					GS.deck[j][n] = k[randKCard];
				}

			}

		}


		//check state of the player's treasure
		for (j = 0; j < GS.handCount[currPlayer]; j++) {
			if (GS.hand[currPlayer][j] == copper || GS.hand[currPlayer][j] == silver || GS.hand[currPlayer][j] == gold) {
				beforeCoins += 1;
			}
		}


		//Activate the card
		cardEffect(adventurer, choice1, choice2, choice3, &GS, handPos, &bonus);


		//check the state of the player's treasure after using card
		for (j = 0; j < GS.handCount[currPlayer]; j++) {
			if (GS.hand[currPlayer][j] == copper || GS.hand[currPlayer][j] == silver || GS.hand[currPlayer][j] == gold) {
				afterCoins += 1;
			}
		}

		
		copper = 0;
		silver = 0;
		gold = 0;


		//check state of discard pile
		for (j = 0; j < GS.discardCount[currPlayer]; j++) {

			if (GS.discard[currPlayer][j] == copper) {
				copper += 1;
			}
			else if (GS.discard[currPlayer][j] == silver) {
				silver += 1;
			}
			else if (GS.discard[currPlayer][j] == gold) {
				gold += 1;
			}

		}
	
		allPassedFlag = 1;

		//run tests

		printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

		if (afterCoins != (beforeCoins + 2)) {
			printf("FAIL: Drawn cards.\n");
			testDraw++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: Drawn cards.\n");
		}

		if (afterCoins < beforeCoins) {
			printf("FAIL: Card count. \n");
			testDraw++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: Card count.\n");
		}


		if (gold != 0) {
			printf("FAIL: Gold.\n");
			failedDiscard++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: Gold.\n");
		}

		if (silver != 0) {
			printf("FAIL: Silver.\n");
			failedDiscard++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: Silver.\n");
		}

		if (copper != 0) {
			printf("FAIL: copper.\n");
			failedDiscard++;
			allPassedFlag = 0;
		}
		else {
			printf("PASS: copper.\n");
		}


		if (allPassedFlag == 1) {
			printf("All test successfull. \n");
			testsPassed++;
		}

	}

	printf(" \n");
	printf("----------------- Random test results for %s ----------------\n", TESTCARD);
	printf("\tPASSED: %d\n", testsPassed);
	printf("\tFAILED (draw): %d\n", testDraw);
	printf("\tFAILED (discard): %d\n\n", failedDiscard);



	return 0;

}
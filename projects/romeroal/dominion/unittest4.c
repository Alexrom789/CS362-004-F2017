/********************************************************************************************************************
* Name: Alejandro Romero
* Date: 10/16/2017
* Description: This is a unit test for the getCost() function of dominion.c. 
  It test to make sure each card returns the correct cost.
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

#define TESTFUNCTION "getCost()"

int main() {

	int i = 0;
	int r = 0;

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	//Check each case in the range -5 to 30
	for (i = 0; i < 27; i++) {

		r = getCost(i);

		switch (i) {

		case curse:
			assert(r == 0);
			break;

		case estate:
			assert(r == 2);
			break;

		case duchy:
			assert(r == 5);
			break;

		case province:
			assert(r == 8);
			break;

		case copper:
			assert(r == 0);
			break;

		case silver:
			assert(r == 3);
			break;

		case gold:
			assert(r == 6);
			break;

		case adventurer:
			assert(r == 6);
			break;

		case council_room:
			assert(r == 5);
			break;

		case feast:
			assert(r == 4);
			break;

		case gardens:
			assert(r == 4);
			break;

		case mine:
			assert(r == 5);
			break;

		case remodel:
			assert(r == 4);
			break;

		case smithy:
			assert(r == 4);
			break;

		case village:
			assert(r == 3);
			break;

		case baron:
			assert(r == 4);
			break;

		case great_hall:
			assert(r == 3);
			break;

		case minion:
			assert(r == 5);
			break;

		case steward:
			assert(r == 3);
			break;

		case tribute:
			assert(r == 5);
			break;

		case ambassador:
			assert(r == 3);
			break;

		case cutpurse:
			assert(r == 4);
			break;

		case embargo:
			assert(r == 2);
			break;

		case outpost:
			assert(r == 5);
			break;

		case salvager:
			assert(r == 4);
			break;

		case sea_hag:
			assert(r == 4);
			break;

		case treasure_map:
			assert(r == 4);
			break;

		}

		printf("\t PASS!: Input i = %d. Returned value = %d \n", i, r);

	}

	printf("\n >>>>>Testing complete for %s: All test succesfully passed. <<<<<\n\n", TESTFUNCTION);

	return 0;

}
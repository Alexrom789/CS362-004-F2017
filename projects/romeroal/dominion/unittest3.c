/********************************************************************************************************************
* Name: Alejandro Romero
* Date: 10/16/2017
* Description: This is a unit test for the compare() function of dominion.c. This test is used to determine if values 
  are properly compared to each other.
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

#define TESTFUNCTION "compare()"

int main() {

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	int testFailed = 0;
	int a, b, r;

	printf("Testing if two int values are compared properly with < operator.\n");
	a = 1;
	b = 2;
	r = compare(&a, &b);
	if (r == -1) 
	{
		printf("PASS!\n");
	}
	else
	{
		printf("FAIL!\n");
		testFailed = 1;
	}

	printf("Testing if two int values are compared properly with > operator.\n");
	a = 2;
	b = 1;
	r = compare(&a, &b);
	if (r == 1) 
	{
		printf("PASS!\n");
	}
	else
	{
		printf("FAIL!\n");
		testFailed = 1;
	}

	printf("Testing if two int values are compared properly with = operator.\n");
	a = 1;
	r = compare(&a, &b);
	if (r == 0) 
	{
		printf("PASS!\n");
	}
	else
	{
		printf("FAIL!\n");
		testFailed = 1;
	}

	printf("Testing if two character values are compared properly.\n");
	char c1 = 'A';
	char c2 = 'B';
	r = compare(&c1, &c2);
	if (r == -1) 
	{
		printf("PASS!\n");
	}
	else
	{
		printf("FAIL!\n");
		testFailed = 1;
	}

	printf("Testing if two float values are compared properly.\n");
	float f1 = 3.25;
	float f2 = 7.50;
	r = compare(&f1, &f2);
	if (r == -1) 
	{
		printf("PASS!\n");
	}
	else
	{
		printf("FAIL!\n");
		testFailed = 1;
	}

	if (testFailed == 0) 
	{
		printf("\n >>>>>Testing complete for %s: All test succesfully passed. <<<<<\n\n", TESTFUNCTION);
	}
	else
	{
		printf("\n >>>>>Testing complete for %s: At least one test has failed. <<<<<\n\n", TESTFUNCTION);
	}
	return 0;

}
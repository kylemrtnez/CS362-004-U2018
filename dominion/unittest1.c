/**********************************************************************
* unittest1.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              isGameOver() in dominion.c
***********************************************************************/    

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main()
{
    // variables for game initialization
    struct gameState GS;
    int numPlayers = 2;
    int seed = 100;
    int kcards[10] = { adventurer, gardens, embargo, village, minion, mine, 
                       cutpurse, sea_hag, tribute, smithy };

    // initialize the game state
    initializeGame(numPlayers, kcards, seed, &GS);

    /* unit tests
        Conditions to test for:
           - provinces have run out
           - 3 supply piles are 0
    */
    /* 
      provinces have run out 
    */
    printf("***Testing end condition: Provinces have run out (provinces == 0)***\n");
    assert(!isGameOver(&GS));
    printf("isGameOver(): PASSED - Game does not end after initialization\n") ;

    GS.supplyCount[province] = 1;
    assert(!isGameOver(&GS));
    printf("isGameOver(): PASSED - Game does not end when stack is 1 card left\n");

    GS.supplyCount[province] = 0;
    assert(isGameOver(&GS));
    printf("isGameOver(): PASSED - Game ends when stack is 0\n");

    printf("***PASSED: Provinces have run out end condition***\n\n");

    // reset game state
    memset(&GS, 23, sizeof(struct gameState));
    initializeGame(numPlayers, kcards, seed, &GS);

    // 3 supply piles have reached 0
    printf("***Testing end condition: 3 supply piles have run out***\n");
    assert(!isGameOver(&GS));
    printf("isGameOver(): PASSED - Game does not end after initialization\n");

    GS.supplyCount[gardens] = 0;
    assert(!isGameOver(&GS));
    printf("isGameOver(): PASSED - Game does not end after 1 pile empty\n");

    GS.supplyCount[embargo] = 0;
    assert(!isGameOver(&GS));
    printf("isGameOver(): PASSED - Game does not end after 2 piles empty\n");

    GS.supplyCount[adventurer] = 0; // game should be over
    assert(isGameOver(&GS));
    printf("isGameOver(): PASSED - Game ends after 3 piles empty\n");

    GS.supplyCount[sea_hag] = 0; // if 4 piles end on same round - can happen since game ends at end of turn vs. immediately
    assert(isGameOver(&GS));
    printf("isGameOver(): PASSED - Game ends after 4 piles empty\n");

    // test function call
    return 0;
}
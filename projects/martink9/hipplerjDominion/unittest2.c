/**********************************************************************
* unittest1.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              scoreFor() in dominion.c
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

    // test for tie - even turns
    int startCoppers = 7;
    int startEstates = 3;
    int player0 = 0;

    // test starting deck values - should be 7 coppers and 3 estates
    printf("***  Testing fullDeckCount()  ***\n");

    assert(fullDeckCount(player0, copper, &GS) == startCoppers);
    assert(fullDeckCount(player0, estate, &GS) == startEstates);
    printf("fullDeckCount(): PASSED - correct values after initialization\n");

    // test adding an estate to discard
    GS.discard[player0][GS.discardCount[player0]] = estate;
    GS.discardCount[player0]++;
    assert(fullDeckCount(player0, estate, &GS) == startEstates + 1);
    printf("fullDeckCount(): PASSED - correct values after adding to discard\n");

    // test adding an estate to deck
    GS.deck[player0][GS.deckCount[player0]] = estate;
    GS.deckCount[player0]++;
    assert(fullDeckCount(player0, estate, &GS) == startEstates + 2);
    printf("fullDeckCount(): PASSED - correct values after adding to deck\n");

    // test adding an estate to hand
    GS.deck[player0][GS.deckCount[player0]] = estate;
    GS.deckCount[player0]++;
    assert(fullDeckCount(player0, estate, &GS) == startEstates + 3);
    printf("fullDeckCount(): PASSED - correct values after adding to hand\n");

    printf("***  fullDeckCount(): PASSED - Correctly computes card numbers  ***\n\n");

    return 0;
}
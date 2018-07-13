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

int checkDeck(struct gameState *state, int player, int card)
{
    int count = 0;
    for (int i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == card)
        {
            count++;
        }
    }
    return count;
}

int checkDiscard(struct gameState *state, int player, int card)
{
    int count = 0;
    for (int i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == card)
        {
            count++;
        }
    }
    return count;
}

int checkHand(struct gameState *state, int player, int card)
{
    int count = 0;
    for (int i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == card)
        {
            count++;
        }
    }
    return count;
}


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
    int numAdventurers = 0; // how many adventurers there should be
    int oneAdventurer = 1;
    int adventurerCount = 0; // how many adventurers there are
    int player0 = 0;
    int gainToDiscard = 0;
    int gainToDeck = 1;
    int gainToHand = 2;

    printf("***  Testing gainCard()  ***\n");
    // test starting deck values - should be 0
    adventurerCount += checkDiscard(&GS, player0, adventurer);
    adventurerCount += checkHand(&GS, player0, adventurer);
    adventurerCount += checkDeck(&GS, player0, adventurer);
    assert(adventurerCount == numAdventurers);

    // test gaining to discard
    printf("gainCard(): Testing gaining to discard\n");

    numAdventurers++;
    gainCard(adventurer, &GS, gainToDiscard, player0);
    adventurerCount = checkDiscard(&GS, player0, adventurer);
    assert(adventurerCount == numAdventurers); // test after adding to discard
    printf("gainCard(): PASSED - added to discard\n");

    adventurerCount = checkDiscard(&GS, player0, adventurer) +
                      checkHand(&GS, player0, adventurer) +
                      checkDeck(&GS, player0, adventurer);
    assert(adventurerCount == numAdventurers); // test after checking hand and deck
    printf("gainCard(): PASSED - correct values after adding to discard\n");

    // test gaining to deck
    printf("gainCard(): Testing gaining to deck\n");

    numAdventurers++;
    gainCard(adventurer, &GS, gainToDeck, player0);
    adventurerCount = checkDeck(&GS, player0, adventurer);
    assert(adventurerCount == oneAdventurer); // test after adding to deck
    printf("gainCard(): PASSED - added to deck\n");

    adventurerCount = checkDiscard(&GS, player0, adventurer) +
                      checkHand(&GS, player0, adventurer) +
                      checkDeck(&GS, player0, adventurer);
    assert(adventurerCount == numAdventurers); // test after checking hand and discard
    printf("gainCard(): PASSED - correct values after adding to discard\n");

    // test gaining to hand
    printf("gainCard(): Testing gaining to hand\n");

    numAdventurers++;
    gainCard(adventurer, &GS, gainToHand, player0);
    adventurerCount = checkHand(&GS, player0, adventurer);
    assert(adventurerCount == oneAdventurer); // test after adding to hand
    printf("gainCard(): PASSED - added to discard\n");

    adventurerCount = checkDiscard(&GS, player0, adventurer) +
                      checkHand(&GS, player0, adventurer) +
                      checkDeck(&GS, player0, adventurer);
    assert(adventurerCount == numAdventurers); // test after checking deck and discard
    printf("gainCard(): PASSED - correct values after adding to discard\n");

    printf("***  fullDeckCount(): PASSED - Correctly computes card numbers  ***\n\n");

    return 0;
}
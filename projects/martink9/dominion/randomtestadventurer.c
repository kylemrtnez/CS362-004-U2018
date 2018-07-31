/**********************************************************************
* randomtestcard1.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Date: 08/05/2018
* Description: This file contains a random test for the Adventurer card
*               effect found in dominion.c
***********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

// int adventurerEffect(struct gameState *gstate, int curPlayer, int tempHand[], int tempCount)
// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

int testCard(struct gameState *prestate, struct gameState *postState);
int checkCard(int players, struct gameState *post, int ch1, int ch2, int ch3, int hp, int *bonus);
/**********************************************************************
* checkCard
* Description: Takes a provided gamestate and calls the card to be
*               tested on it. Then compares the state of what should
*               have happened vs. what actually happened
* Parameters: 
* Returns: 
***********************************************************************/
int checkCard(int players, struct gameState *post, int ch1, int ch2, int ch3, int hp, int *bonus)
{
  // set up pre and post game state's for checking validity
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  // invoke the card action
  cardEffect(adventurer, ch1, ch2, ch3, post, hp, bonus);

  // testCard
  return testCard(&pre, post);
}

/**********************************************************************
* testCard()
* Description: Tests the adventrurer card
* Parameters: 
* Returns: 1 if tests passed, 0 if a test failed
***********************************************************************/
int testCard(struct gameState *prestate, struct gameState *postState)
{
  assert(prestate->whoseTurn == postState->whoseTurn);
  int testStatus = 1;
  int curPlayer = prestate->whoseTurn;


  // check handcounts
  int preHc = prestate->handCount[curPlayer] + 2;
  int postHc = postState->handCount[curPlayer];

  if (preHc == postHc)
    printf("PASSED - pre-handcount == post-handcount\n");
  else
  {
    printf("FAILED - pre-handcount != post-handcount\n");
    testStatus = 0;
  }

  // check that newly drawn cards are treasures
  int newDraw1, newDraw2;

  newDraw1 = postState->hand[curPlayer][postHc - 2];
  newDraw2 = postState->hand[curPlayer][postHc - 1];

  if (newDraw1 == copper || newDraw1 == silver || newDraw1 == gold)
    printf("PASSED - new draw 1 == a treasure\n");
  else
  {
    printf("FAILED - new draw 1 != a treasure\n");
    testStatus = 0;
  }

  if (newDraw2 == copper || newDraw2 == silver || newDraw2 == gold)
    printf("PASSED - new draw 2 == a treasure\n");
  else
  {
    printf("FAILED - new draw 2 != a treasure\n");
    testStatus = 0;
  }

  return testStatus;
}

/**********************************************************************
* Main
***********************************************************************/
int main(int argc, char **argv)
{
  char *cardToTest = "Adventurer";
  printf("*** RANDOM TESTING %s CARD EFFECT ***\n", cardToTest);

  int i, p, c1, c2, c3, handPos, testFails, testPasses;
  testFails = testPasses = 0;

  struct gameState GS;
  int numPlayers = 2;
  int seed = 100;
  int kcards[10] = {adventurer, gardens, embargo, village, minion, mine,
                    cutpurse, sea_hag, tribute, smithy};
  int r, coinBonus = 0;


  srand(seed);

  // initialize the game state
  for (i = 0; i < 100; i++)
  {
    r = initializeGame(numPlayers, kcards, seed, &GS);

    // randomize player turn and deck
    p = GS.whoseTurn = rand() % 2;

    // randomize choice options - must be pseudo random
    c1 = (rand() % 2) + 1; 
    c2 = (rand() % 2) + 1; 
    c3 = (rand() % 2) + 1; 

    // add adventurer to be played
    handPos = GS.handCount[p];
    GS.handCount[p]++;
    GS.hand[p][handPos] = adventurer;

    // test the card effect
    int testResult = checkCard(p, &GS, c1, c2, c3, handPos, &coinBonus);

    // tally score
    if (testResult == 1)
      testPasses++;
    else
      testFails++;

  }

  printf("Pass count: %d\n", testPasses);
  printf("Fail count: %d\n", testFails);
  printf("Pass ratio: %d\n", testPasses / (testPasses + testFails));

  printf("*** COMPLETE: %s CARD EFFECT TESTS ***\n", cardToTest);
  return 0;
}
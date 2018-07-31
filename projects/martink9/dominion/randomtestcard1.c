/**********************************************************************
* randomtestcard1.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Date: 08/05/2018
* Description: This file contains a random test for the smithy card
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
  memcpy(&pre, post, sizeof(struct gameState));

  // invoke the card action
  cardEffect(smithy, ch1, ch2, ch3, post, hp, bonus);

  // testCard
  return testCard(&pre, post);
}

/**********************************************************************
* testCard()
* Description: Tests the smithy card
* Parameters: 
* Returns: 1 if tests passed, 0 if a test failed
***********************************************************************/
int testCard(struct gameState *prestate, struct gameState *postState)
{
  assert(prestate->whoseTurn == postState->whoseTurn);
  int testStatus = 1;
  int curPlayer = prestate->whoseTurn;

  // check handcounts - s/b + 2 (+3 draws, -1 smithy)
  int preHc = prestate->handCount[curPlayer] + 2;
  int postHc = postState->handCount[curPlayer];

  if (preHc == postHc)
    printf("PASSED - pre-handcount == post-handcount (%d vs %d)\n", preHc, postHc);
  else
  {
    printf("FAILED - pre-handcount != post-handcount (%d vs %d)\n", preHc, postHc);
    testStatus = 0;
  }

  return testStatus;
}

/**********************************************************************
* Main
***********************************************************************/
int main(int argc, char **argv)
{
  char *cardToTest = "SMITHY";
  printf("*** RANDOM TESTING %s CARD EFFECT ***\n", cardToTest);

  int i, p, c1, c2, c3, handPos, testFails, testPasses;
  testFails = testPasses = 0;

  struct gameState GS;
  int numPlayers = 2;
  int seed = 100;
  int kcards[10] = {adventurer, gardens, embargo, village, minion, mine,
                    cutpurse, sea_hag, tribute, smithy};
  int r, cbonus = 0;


  srand(seed);

  // initialize the game state
  for (i = 0; i < 1000; i++)
  {
    // initializeGame already has randomness baked in
    r = initializeGame(numPlayers, kcards, seed, &GS);
    // randomize player turn
    p = GS.whoseTurn = rand() % 2;

    // randomize choice options - must be pseudo random
    c1 = (rand() % 2) + 1; 
    c2 = (rand() % 2) + 1; 
    c3 = (rand() % 2) + 1;     

    // add smithy to be played
    handPos = GS.handCount[p];
    GS.handCount[p]++;
    GS.hand[p][handPos] = smithy;

    cbonus = rand() % 10;

    // test the card effect
    int testResult = checkCard(p, &GS, c1, c2, c3, handPos, &cbonus);

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
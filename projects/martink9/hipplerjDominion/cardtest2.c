/**********************************************************************
* cardtest2.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              smithy card effect in dominion.c
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

/**********************************************************************
* Smithy Test Cases:
***********************************************************************/
int main(int argc, char **argv)
{
  struct gameState GS;
  int numPlayers = 2;
  int player0 = 0;
  int seed = 100;
  int kcards[10] = {adventurer, gardens, embargo, village, minion, mine,
                    cutpurse, sea_hag, tribute, smithy};
  int r, coinBonus = 0;
  int smithyHandPos = 5;

  printf("*** Smithy card effect: Testing begins ***\n");
  /**********************************************************************
  * Test case: Deck has more than 3 cards
  ***********************************************************************/
  // initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);
  assert(GS.deckCount[player0] > 3); // make sure our test state is valid


  // add smithy to simulate playing it
  GS.handCount[player0]++;
  GS.hand[player0][smithyHandPos] = smithy;
  int handSize = GS.handCount[player0];

  cardEffect(smithy, -1, -1, -1, &GS, smithyHandPos, &coinBonus);
  #if (NOISY_TEST)
  {
    printf("Hand size: %d vs GS hand size: %d\n", handSize, GS.handCount[player0]);
  } 
  #endif

  if (handSize + 2 == GS.handCount[player0]) // only +2 cards because smithy itself is discarded
    printf("PASSED 1: Hand count correct.\n");
  else
    printf("FAILED 1: Hand count incorrect.\n");

  /**********************************************************************
  * Test case: Deck has 3 cards
  ***********************************************************************/
  // initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);
  GS.deckCount[player0] = 3;
  GS.discardCount[player0] = 2;
  for (int i = 0; i < 2; i++)
  {
    GS.discard[player0][i] = estate;
  }

  assert(GS.deckCount[player0] == 3); // make sure our test state is valid

  // add smithy to simulate playing it
  GS.handCount[player0]++;
  GS.hand[player0][smithyHandPos] = smithy;
  handSize = GS.handCount[player0];

  cardEffect(GS.hand[player0][smithyHandPos], -1, -1, -1, &GS, smithyHandPos, &coinBonus);
  #if (NOISY_TEST)
  {
    printf("Hand size: %d vs GS hand size: %d\n", handSize, GS.handCount[player0]);
  } 
  #endif

  if ((handSize + 2) == GS.handCount[player0]) // only + 2 cards because smithy itself is discarded
    printf("PASSED 2: Hand count correct.\n");
  else
    printf("FAILED 2: Hand count incorrect.\n");

  /**********************************************************************
  * Test case: Deck has less than 3 cards
  ***********************************************************************/
  // initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);
  // move 3 cards to discard
  GS.deckCount[player0] = 2;
  GS.discardCount[player0] = 3;
  for (int i = 0; i < 3; i++)
  {
    GS.discard[player0][i] = estate;
  }

  assert(GS.deckCount[player0] < 3); // make sure our test state is valid


  // add smithy to simulate playing it
  GS.handCount[player0]++;
  GS.hand[player0][smithyHandPos] = smithy;
  handSize = GS.handCount[player0];
  cardEffect(smithy, -1, -1, -1, &GS, smithyHandPos, &coinBonus);
  #if (NOISY_TEST)
  {
    printf("Hand size: %d vs GS hand size: %d\n", handSize, GS.handCount[player0]);
  } 
  #endif

  if (handSize + 2 == GS.handCount[player0]) // only +2 cards because smithy itself should be discarded
    printf("PASSED 3: Hand count correct.\n");
  else
    printf("FAILED 3: Hand count incorrect.\n");

  printf("*** Smithy card effect: Testing complete ***\n\n");
  return 0;
}

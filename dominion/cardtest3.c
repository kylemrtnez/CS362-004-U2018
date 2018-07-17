/**********************************************************************
* cardtest3.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              village card effect in dominion.c
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/**********************************************************************
* Village Test Cases:
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

  printf("*** Village card effect: Testing begins ***\n");
  /**********************************************************************
  * Test case: Deck has more than 3 cards
  ***********************************************************************/
  // initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);

  // add village to hand
  GS.hand[player0][GS.handCount[player0]] = village;
  GS.handCount[player0]++;

  // log numActions
  int numActionsCheck = GS.numActions;
  // log num cards
  int numHandCheck = GS.handCount[player0];

  // play village
  cardEffect(village, -1, -1, -1, &GS, GS.hand[player0][GS.handCount[player0] - 1], &coinBonus);

  // check vs the logged figures
  // Hand s/b -1 for the played village, +1 for the draw in village effect
  if (GS.handCount[player0] == numHandCheck)
    printf("PASSED: hand counts correct\n");
  else
    printf("FAILED: hand counts incorrect\n");

  // Actions s/b +2
  if (GS.numActions == numActionsCheck + 2)
    printf("PASSED: Number of actions correct\n");
  else
    printf("FAILED: Number of actions incorrect\n");

  printf("*** Village card effect: Testing complete ***\n\n");

  return 0;
}
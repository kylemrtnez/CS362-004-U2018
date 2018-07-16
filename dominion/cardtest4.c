/**********************************************************************
* cardtest3.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              sea hag card effect in dominion.c
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 0

/**********************************************************************
* Prototypes
***********************************************************************/
int paveDeck(struct gameState *state, int playerNum);
int paveHand(struct gameState *state, int playerNum);
void printDeck(struct gameState *state, int printUntil, int player);
void printDiscard(struct gameState *state, int printUntil, int player);

/**********************************************************************
* Sea Hag Test Cases:
***********************************************************************/
int main(int argc, char **argv)
{
  struct gameState GS;
  int numPlayers = 4;
  int player0 = 0;
  int seed = 100;
  int kcards[10] = {adventurer, gardens, embargo, village, minion, mine,
                    cutpurse, sea_hag, tribute, smithy};
  int r, coinBonus = 0;

  // initialize game and pave all players hands and decks (makes all cards estates)
  r = initializeGame(numPlayers, kcards, seed, &GS);

  for (int i = 0; i < numPlayers; i++)
  {
    paveHand(&GS, i);
    paveDeck(&GS, i);
  }
  // make top card in all decks a copper
  for (int i = 0; i < numPlayers; i++)
  {
    GS.deck[i][GS.deckCount[i] - 1] = copper;
  }

  // player 0 gets a sea hag in hand
  GS.handCount[player0]++;
  GS.hand[player0][GS.handCount[player0]] = sea_hag;

  printf("*** Sea hag card effect: Testing begins ***\n");
  // player 0 plays a sea hag
  cardEffect(sea_hag, -1, -1, -1, &GS, GS.hand[player0][GS.handCount[player0] - 1], &coinBonus);


#if (NOISY_TEST)
{
  for (int i = 0; i < numPlayers; i++)
  {
    printf("Deck count: %d\n", GS.deckCount[i]);
  }
  printf("\n");

  printf("Decks:")
  for (int i = 0; i < numPlayers; i++)
  {
    printDeck(&GS, GS.deckCount[i], i);
    printf("\n");
  }
  printf("\n");

  printf("Disards:")
  for (int i = 0; i < numPlayers; i++)
  {
    printDiscard(&GS, GS.discardCount[i], i);
    printf("\n");
  }
}
#endif

  // all other players have a curse on top of their deck and a copper in the discard
  for (int i = 1; i < numPlayers; i++)
  {
    if (GS.deck[i][GS.deckCount[i] - 1] == curse)
    {
      printf("Sea hag test PASSED: player %d's top deck is: %d (s/b %d)\n",
             i,
             GS.deck[i][GS.deckCount[i] - 1],
             curse);
    }
    else
    {
      printf("Sea hag test FAILED: player %d's top deck is: %d (s/b %d)\n",
             i,
             GS.deck[i][GS.deckCount[i] - 1],
             curse);
    }

    if (GS.discard[i][GS.discardCount[i] - 1] == copper)
    {
      printf("Sea hag test PASSED: player %d's top discard is: %d (s/b %d)\n",
             i,
             GS.discard[i][GS.discardCount[i] - 1],
             copper);
    }
    else
    {
      printf("Sea hag test FAILED: player %d's top discard is: %d (s/b %d)\n",
             i,
             GS.discard[i][GS.discardCount[i] - 1],
             copper);
    }
  }

  // player 0's top card should be copper
  if (GS.deck[player0][GS.deckCount[player0] - 1] == copper)
  {
    printf("Sea hag test PASSED: player %d's top deck is: %d (s/b %d)\n",
           player0,
           GS.deck[player0][GS.deckCount[player0] - 1],
           copper);
  }
  else
  {
    printf("Sea hag test FAILED: player %d's top deck is: %d (s/b %d)\n",
           player0,
           GS.deck[player0][GS.deckCount[player0] - 1],
           copper);
  }
  // player 0 should have sea hag discarded
  if (GS.discard[player0][GS.discardCount[player0] - 1] == sea_hag)
  {
    printf("Sea hag test PASSED: player %d's top discard is: %d (s/b %d)\n",
           player0,
           GS.deck[player0][GS.deckCount[player0] - 1],
           sea_hag);
  }
  else
  {
    printf("Sea hag test FAILED: player %d's top discard is: %d (s/b %d)\n",
           player0,
           GS.discard[player0][GS.discardCount[player0] - 1],
           sea_hag);
  }

  printf("*** Sea hag card effect: Testing complete ***\n");
  return 0;
}


/**********************************************************************
* Description: Helper function for unit testing. "Paves" over the 
*              provided player's deck, turning all cards to estates.
***********************************************************************/
int paveDeck(struct gameState *state, int playerNum)
{
  for (int i = 0; i < state->deckCount[playerNum]; i++)
  {
    // pave over initialized decks, giving only estates. We will hand-place treasures
    state->deck[playerNum][i] = estate;
  }
  return 0;
}

/**********************************************************************
* Description: Helper function for unit testing. "Paves" over the 
*              provided player's hand, turning all cards to estates.
***********************************************************************/
int paveHand(struct gameState *state, int playerNum)
{
  for (int i = 0; i < state->handCount[playerNum]; i++)
  {
    // pave over initialized decks, giving only estates. We will hand-place treasures
    state->hand[playerNum][i] = estate;
  }
  return 0;
}

/**********************************************************************
* Description: Prints a specified deck, card by card
***********************************************************************/
void printDeck(struct gameState *state, int printUntil, int player)
{
  for (int i = 0; i < printUntil; i++)
  {
    printf("Player %d Deck pos %d: %d\n", player, i, state->deck[player][i]);
  }
}

/**********************************************************************
* Description: Prints a specified discard pile, card by card
***********************************************************************/
void printDiscard(struct gameState *state, int printUntil, int player)
{
  for (int i = 0; i < printUntil; i++)
  {
    printf("Player %d Discard pos %d: %d\n", player, i, state->discard[player][i]);
  }
}
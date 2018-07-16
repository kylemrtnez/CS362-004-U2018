/**********************************************************************
* cardtest1.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              adventurer card effect in dominion.c
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/**********************************************************************
* Prototypes
***********************************************************************/
int paveDeck(struct gameState *state, int playerNum);
int paveHand(struct gameState *state, int playerNum);
void printDeck(struct gameState *state, int printUntil, int player);
void printHand(struct gameState *state, int printUntil, int player);
void addAdventurer(struct gameState *state, int handPos, int player);

/**********************************************************************
* Unit test for the Adventurer card implementation
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

  printf("*** Adventurer card effect: Testing begins ***\n");
  /**********************************************************************
    * Test case: First 2 cards are treasures
    ***********************************************************************/
  // initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);

  // set up player 0's initialized deck and hand for testing
  r = paveDeck(&GS, player0);
  r = paveHand(&GS, player0);

  addAdventurer(&GS, 5, player0);
  // first two cards are treasure cards
  GS.deck[player0][3] = copper;
  GS.deck[player0][4] = silver;

  GS.handCount[player0]--; // should get rid of the adventurer we are about to play
  cardEffect(adventurer, -1, -1, -1, &GS, 5, &coinBonus);

  // stops after 2 cards
  if (GS.deckCount[player0] == 3)
    printf("PASSED 1: deck count correct.\n");
  else 
    printf("FAILED 1: deck count incorrect.\n");

  if (GS.handCount[player0] == 7)
    printf("PASSED 1: hand count correct.\n");
  else 
    printf("FAILED 1: hand count incorrect.\n");


  // no cards discarded
  if (GS.discardCount[player0] == 0)
    printf("PASSED 1: discard count correct.\n");
  else 
    printf("FAILED 1: discard count incorrect.\n");


  /**********************************************************************
    * Test case: Last 2 cards are treasures
    ***********************************************************************/
  // re-initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);

  // set up player 0's initialized deck and hand for testing
  r = paveDeck(&GS, player0);
  r = paveHand(&GS, player0);

  // last two cards are treasure cards
  GS.deck[player0][0] = gold;
  GS.deck[player0][1] = copper;

  addAdventurer(&GS, 5, player0);
  GS.handCount[player0]--; // should get rid of the adventurer we are about to play
  cardEffect(adventurer, -1, -1, -1, &GS, 5, &coinBonus);

  // no cards left in deck
  if (GS.deckCount[player0] == 0)
    printf("PASSED 2: deck count correct.\n");
  else 
    printf("FAILED 2: deck count incorrect.\n");

  if (GS.handCount[player0] == 7)
    printf("PASSED 2: hand count correct.\n");
  else 
    printf("FAILED 2: hand count incorrect.\n");

  // all other cards discarded
  if (GS.discardCount[player0] == 3)
    printf("PASSED 2: discard count correct.\n");
  else 
    printf("FAILED 2: discard count incorrect.\n");

  /**********************************************************************
    * Test case: Space in between treasure cards
    ***********************************************************************/
  // re-initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);

  // set up player 0's initialized deck and hand for testing
  r = paveDeck(&GS, player0);
  r = paveHand(&GS, player0);

  // two cards are treasure cards - space in between
  GS.deck[player0][1] = silver;
  GS.deck[player0][4] = gold;

  addAdventurer(&GS, 5, player0);
  GS.handCount[player0]--; // should get rid of the adventurer we are about to play
  cardEffect(adventurer, -1, -1, -1, &GS, 5, &coinBonus);

  // 1 card left in deck
  if (GS.deckCount[player0] == 1)
    printf("PASSED 3: deck count correct.\n");
  else 
    printf("FAILED 3: deck count incorrect.\n");

  if (GS.handCount[player0] == 7)
    printf("PASSED 3: hand count correct.\n");
  else 
    printf("FAILED 3: hand count incorrect.\n");
  // 2 cards discarded
  if (GS.discardCount[player0] == 2)
    printf("PASSED 3: discard count correct.\n");
  else 
    printf("FAILED 3: discard count incorrect.\n");


  /**********************************************************************
    * Test case: 1 treasure in deck, shuffles to find another
    ***********************************************************************/
  // re-initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);

  // set up player 0's initialized deck and hand for testing
  r = paveDeck(&GS, player0);
  r = paveHand(&GS, player0);

  // two cards are treasure cards
  GS.deck[player0][3] = copper;
  GS.discard[player0][0] = silver;
  GS.discardCount[player0]++;
  // decrease amount of cards in game by 1 to account for added discard
  GS.deckCount[player0]--;

  addAdventurer(&GS, 5, player0);
  GS.handCount[player0]--; // should get rid of the adventurer we are about to play
  cardEffect(adventurer, -1, -1, -1, &GS, 5, &coinBonus);

  // 2 extra treasures in hand, deck + discard should account for rest
  if (GS.deckCount[player0] + GS.discardCount[player0] == 3)
    printf("PASSED 4: deck count + discard count correct after shuffle.\n");
  else
    printf("FAILED 4: deck count + discard count incorrect after shuffle.\n");

  if (GS.handCount[player0] == 7)
    printf("PASSED 4: hand count correct.\n");
  else 
    printf("FAILED 4: hand count incorrect.\n");


  /**********************************************************************
    * Test case: 1 treasure in deck and discard, shuffles only once
    ***********************************************************************/
  // re-initialize the game state
  r = initializeGame(numPlayers, kcards, seed, &GS);

  // set up player 0's initialized deck and hand for testing
  r = paveDeck(&GS, player0);
  r = paveHand(&GS, player0);

  // two cards are treasure cards
  GS.discard[player0][0] = gold;
  GS.discardCount[player0]++;
  // decrease amount of cards in game by 1 to account for added discard
  GS.deckCount[player0]--;

  addAdventurer(&GS, 5, player0);
  GS.handCount[player0]--; // should get rid of the adventurer we are about to play
  cardEffect(adventurer, -1, -1, -1, &GS, 5, &coinBonus);

  // 2 extra treasures in hand, deck + discard should account for rest
  if (GS.deckCount[player0] + GS.discardCount[player0] == 4)
    printf("PASSED 5: deck count + discard count correct after shuffle.\n");
  else
    printf("FAILED 5: deck count + discard count incorrect after shuffle.\n");

  if (GS.handCount[player0] == 6)
    printf("PASSED 5: hand count correct.\n");
  else 
    printf("FAILED 5: hand count incorrect.\n");


  printf("*** Adventurer card effect - tests complete ***\n\n");

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
    printf("Deck pos %d: %d\n", i, state->deck[player][i]);
  }
}
/**********************************************************************
* Description: Prints a specified hand, card by card
***********************************************************************/
void printHand(struct gameState *state, int printUntil, int player)
{
  for (int i = 0; i < printUntil; i++)
  {
    printf("Hand pos %d: %d\n", i, state->hand[player][i]);
  }
}
/**********************************************************************
* Helper function to add adventurer to test player's hand. Purpose is
* to mainly couple the handcount increment with the addition.
***********************************************************************/
void addAdventurer(struct gameState *state, int handPos, int player)
{
  state->handCount[player]++;
  state->hand[player][handPos] = adventurer;
}
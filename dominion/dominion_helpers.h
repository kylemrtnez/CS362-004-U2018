#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

// Assignment 2: Refactored card effects as functions
int adventurerEffect(struct gameState *gstate, int curPlayer, int tempHand[], int tempCount);
int smithyEffect(struct gameState *gstate, int curPlayer, int handPosition);
int mineEffect(struct gameState *gstate, int curPlayer, int choiceA, int choiceB, int handPosition);
int salvagerEffect(struct gameState *gstate, int curPlayer, int choiceA, int handPosition);
int greathallEffect(struct gameState *gstate, int curPlayer, int handPosition);

#endif

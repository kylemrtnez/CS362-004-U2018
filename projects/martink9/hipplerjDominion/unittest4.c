/**********************************************************************
* unittest1.c
* Author: Kyle Martinez (martink9@oregonstate.edu)
* Description: This file contains a unit test for the function
*              getCost() in dominion.c
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    printf("***  Testing getCost(): Implemented cards only  ***\n");
    int cost = 0;

    cost = getCost(estate);
    assert(cost == 2);

    cost = getCost(duchy);
    assert(cost == 5);

    cost = getCost(province);
    assert(cost == 8);

    cost = getCost(copper);
    assert(cost == 0);

    cost = getCost(silver);
    assert(cost == 3);

    cost = getCost(gold);
    assert(cost == 6);

    cost = getCost(adventurer);
    assert(cost == 6);

    cost = getCost(council_room);
    assert(cost == 5);

    cost = getCost(feast);
    assert(cost == 4);

    cost = getCost(gardens);
    assert(cost == 4);

    cost = getCost(mine);
    assert(cost == 5);

    cost = getCost(remodel);
    assert(cost == 4);

    cost = getCost(smithy);
    assert(cost == 4);

    cost = getCost(village);
    assert(cost == 3);

    cost = getCost(baron);
    assert(cost == 4);

    cost = getCost(great_hall);
    assert(cost == 3);

    cost = getCost(minion);
    assert(cost == 5);

    cost = getCost(steward);
    assert(cost == 3);

    cost = getCost(tribute);
    assert(cost == 5);

    cost = getCost(ambassador);
    assert(cost == 3);

    cost = getCost(cutpurse);
    assert(cost == 4);

    cost = getCost(embargo);
    assert(cost == 2);

    cost = getCost(outpost);
    assert(cost == 5);

    cost = getCost(sea_hag);
    assert(cost == 4);

    cost = getCost(salvager);
    assert(cost == 4);

    cost = getCost(treasure_map);
    assert(cost == 4);

    printf("***  PASSED: getCost() returns correct costs  ***\n\n");

    return 0;
}
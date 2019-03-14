#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "smithy"

int main(){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int flag = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState testG, G;
    int check = 0;

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    initializeGame(numPlayers, k, seed, &G);

    //transfer over game state to test struct
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = smithy;
    testG.handCount[currentPlayer] += 1;

    check = G.handCount[currentPlayer] + 1;
    if (check == testG.handCount[currentPlayer])
    {
        printf("TEST 1 PASSED:\n Player %d's hand count is now %d\n", currentPlayer + 1, testG.handCount[currentPlayer]);
    }
    else
    {
        printf("TEST 1 FAILED:\n Player %d's hand count is %d, but should be %d\n", currentPlayer + 1, testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1);
        flag = -1;
    }

    //check if 3 cards get selected 
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    if(G.handCount[currentPlayer] + 3 == testG.handCount[currentPlayer]){//includes smithy bug syntax
        printf("TEST 2 PASSED:\n 3 additional cards were selected.\n");
    }
    else{
        printf("TEST 2 FAILED:\n Actual: %d\n Expected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 3);
        flag = -1;
    }

    //check that no other players states are affected.
    if (testG.handCount[currentPlayer + 1] != G.handCount[currentPlayer + 1] && testG.deckCount[currentPlayer+1] != G.deckCount[currentPlayer+1]){
        printf("TEST 3 FAILED:\n Player 2's pile was messed with.\n");
        flag = -1;
    }
    else{
        printf("TEST 3 PASSED:\n Only player 1's pile was affected.\n");
    }

    //check that 3 cards come from their own pile
    if(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - 3){
        printf("TEST 4 PASSED:\n 3 cards came from player 1's own pile.\n");
    }
    else
    {
        printf("TEST 4 FAILED:\n 3 cards did not come from player 1's own pile.\n discard pile for test %d for G %d ", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]);
        flag = -1;
    }
    
    //no state change should occur to any of the victory cards
    if ((testG.supplyCount[province] == G.supplyCount[province]) && (testG.supplyCount[estate] == G.supplyCount[estate]) && (testG.supplyCount[duchy] == G.supplyCount[duchy])){
        printf("TEST 5 PASSED:\n None of the victory cards were affect.\n");
    }
    else{
        printf("TEST 5 FAILED:\n Victory cards were affected.\n");
        flag = -1;
    }
        if (flag == 0)
        {
            printf("ALL TESTS HAVE PASSED.\n");
        }
        else
        {
            printf("TEST FAILED.\n");
        }
    return 0;
}
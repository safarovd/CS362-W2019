#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "mine"

int main(){
    int choice1 = 3, choice2 = 5, choice3 = 0, bonus = 0, handpos = 3;
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

   // testG.handCount[currentPlayer] = 2;
   // testG.hand[currentPlayer][testG.handCount[currentPlayer]-1] = copper;

    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = mine;
    testG.handCount[currentPlayer] += 1;

    check = G.handCount[currentPlayer] + 1;
    if (check == testG.handCount[currentPlayer])
    {
        printf("TEST 1 PASSED:\n Player %d's hand count is now %d\n", currentPlayer + 1, testG.handCount[currentPlayer]);
    }
    else
    {
        printf("TEST 1 FAILED:\n Player %d's hand count is %d, but should be %d\n", currentPlayer + 1, testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1 );
        flag = -1;
    }

    //check if 1 card gets trashed and one gets selected and mine was disgarded
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

    if (G.handCount[currentPlayer] == testG.handCount[currentPlayer])
    { 
        printf("TEST 2 PASSED:\n 1 card was selected and replaced.\n");
    }
    else
    {
        printf("TEST 2 FAILED:\n Actual: %d\n Expected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1);
        flag = -1;
    }
//check that the correct card gets replaced by a silver
    if (testG.hand[currentPlayer][handpos] == silver){
        printf("TEST 3 PASSED:\n Copper at hand position 3 was replaced with a silver.\n");
    }
    else{
        printf("TEST 3 FAILED:\n Copper at hand position %d was replaced with a %d.\n", handpos, testG.hand[currentPlayer][handpos]);
        flag = -1;
    }

    cardEffect(mine, choice1, 8, choice3, &testG, handpos, &bonus);

    //check that the correct card gets replaced by a gold
    if (testG.hand[currentPlayer][handpos] == gold)
    {
        printf("TEST 6 FAILED:\n Copper at hand position 3 was replaced with a gold.\n");
        flag = -1;
    }
    else
    {
        printf("TEST 6 PASSED:\n Copper at hand position %d was not replaced with a gold, but instead a %d.\n", handpos, testG.hand[currentPlayer][handpos]);

    }
    //check if victory cards are affected at all
    if ((testG.supplyCount[province] == G.supplyCount[province]) && (testG.supplyCount[estate] == G.supplyCount[estate]) && (testG.supplyCount[duchy] == G.supplyCount[duchy]))
    {
        printf("TEST 4 PASSED:\n None of the victory cards were affect.\n");
    }
    else
    {
        printf("TEST 4 FAILED:\n Victory cards were affected.\n");
        flag = -1;
    }

    //check to see if the correct piles are used.
    if (testG.handCount[currentPlayer + 1] != G.handCount[currentPlayer + 1] && testG.deckCount[currentPlayer + 1] != G.deckCount[currentPlayer + 1])
    {
        printf("TEST 5 FAILED:\n Player 2's pile was messed with.\n");
        flag = -1;
    }
    else
    {
        printf("TEST 5 PASSED:\n Only player 1's pile was affected.\n Surrounding game state is safe.\n");
    }

    if (flag == 0)
    {
        printf("ALL TESTS HAVE PASSED.\n");
        }
        else
        {
            printf("TESTS FAILED.\n");
        }
    return 0;
}
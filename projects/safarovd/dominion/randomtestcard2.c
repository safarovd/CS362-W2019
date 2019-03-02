#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define TESTCARD "village"

int main()
{
    srand(time(NULL));
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, i, dSize, hSize, z;
    int seed = 1000;
    //int arr[4] = {1, 2, 3, 4};
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 0;
    struct gameState testG, G;

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    for(i = 0; i < 1000; i++){
        numPlayers = 2;

        printf("\n<------------------------VILLAGE TEST LOOP %d------------------------->\n\n", i + 1);

        initializeGame(numPlayers, k, seed, &G);

        dSize = rand() % (MAX_DECK + 1);
        hSize = rand() % (dSize + 1);

        //transfer over game state to test struct
        //memcpy(&testG, &G, sizeof(struct gameState));

        G.deckCount[0] = dSize - hSize;
        G.handCount[0] = hSize;

        for (z = 0; z < numPlayers; z++)
        {
            printf("\n**PLAYER %d**\n\n", z + 1);

            memcpy(&testG, &G, sizeof(struct gameState));

            //check if 1 card get selected and 2 actions
            cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

            if (G.deckCount[z] - 1 == testG.deckCount[z])
            {
                printf("    TEST 1 PASSED:\n     1 additional card was selected.\n");
            }
            else if (G.deckCount[z] - 1 != testG.deckCount[z] && z == 1)
            {
                printf("    TEST 1 PASSED:\n     Card Deck Not Affected: %d cards\n     Expected: %d\n", testG.deckCount[z], G.deckCount[z]);
            }

            printf("\n    next test...\n\n");

            if (G.numActions + 2 == testG.numActions)
            {
                printf("    TEST 2 PASSED:\n     2 additional action cards were selected.\n");
            }
            else
            {
                printf("    TEST 2 FAILED:\n     Actual: %d\n     Expected: %d\n", testG.numActions, G.numActions + 2);
            }

            printf("\n    next test...\n\n");

            //check if victory cards are affected at all
            if ((testG.supplyCount[province] == G.supplyCount[province]) && (testG.supplyCount[estate] == G.supplyCount[estate]) && (testG.supplyCount[duchy] == G.supplyCount[duchy]))
            {
                printf("    TEST 3 PASSED:\n     None of the victory cards were affect.\n");
            }
            else
            {
                printf("    TEST 3 FAILED:\n     Victory cards were affected.\n");
            }

            if(z < 1){
                    printf("\n    next test...\n\n");

                    //check to see if the correct piles are used.
                    if (testG.handCount[z + 1] != G.handCount[z + 1] && testG.deckCount[z + 1] != G.deckCount[z + 1])
                    {
                        printf("    TEST 4 FAILED:\n     Player %d's pile was messed with.\n", z + 2);
                    }
                    else
                    {
                        printf("    TEST 4 PASSED:\n     Only player %d's pile was affected.\n", z + 1);
                    }
            }
            else{
                printf("\n    next test...\n\n");

                if (testG.handCount[z - 1] != G.handCount[z - 1] && testG.deckCount[z - 1] != G.deckCount[z - 1])
                {
                    printf("    TEST 4 FAILED:\n     Player %d's pile was messed with.\n", z - 1);
                }
                else
                {
                    printf("    TEST 4 PASSED:\n     Only player %d's pile was affected.\n", z + 1);
                }
            }
        }
    }
    return 0;
}
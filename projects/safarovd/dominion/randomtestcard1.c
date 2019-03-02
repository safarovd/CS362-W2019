#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "smithy"

int main()
{
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, i, z;
    int seed = 1000;
    //int arr[4] = {1, 2, 3, 4};
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int dSize, hSize;
    struct gameState testG, G;
    srand(time(NULL));
    int testhand, testdeck, testdiscard;

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    for (i = 0; i < 1000; i++)
    {
        int numPlayers = 2;//(arr[(rand() % 4)]);

        printf("\n<------------------------SMITHY TEST LOOP %d------------------------->\n\n", i + 1);

        initializeGame(numPlayers, k, seed, &G);

        dSize = rand() % (MAX_DECK + 1);
        hSize = rand() % (dSize + 1);

        //transfer over game state to test struct
        //memcpy(&testG, &G, sizeof(struct gameState));

        G.deckCount[0] = dSize - hSize;
        G.handCount[0] = hSize;

        memcpy(&testG, &G, sizeof(struct gameState));
//test the smithy card
        for (z = 0; z < numPlayers; z++)
        {
            cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

            printf("\n**PLAYER %d**\n\n", z + 1);

            //store the new numbers for hand, deck and discard in new variables
            testdeck = testG.deckCount[z];

            testhand = testG.handCount[z];

            testdiscard = testG.playedCardCount;
            //test if 3 cards were drawn to hand
            if(z == 0){
                if (testhand == (G.handCount[z] + 3))
                    printf("    TEST 1 PASSED:\n     %d were drawn to hand.\n     Expected: %d\n", testhand, G.handCount[z] + 3);

                printf("\n    next test...\n\n");

                //test if 3 cards including smithy were removed
                if (testdeck == (G.deckCount[z] - 4))
                    printf("    TEST 2 PASSED:\n     %d were drawn out of the deck.\n     Expected: %d\n", testdeck, G.deckCount[z] - 4);

                printf("\n    next test...\n\n");

                //test if 1 card was discarded
                if (testdiscard == (G.playedCardCount + 1))
                    printf("    TEST 3 PASSED:\n     %d discarded\n     Expected: %d\n", testdiscard, G.playedCardCount + 1);
            }
            else if (testhand != (G.handCount[z] + 3) && testdeck != (G.deckCount[z] - 4) && testdiscard != (G.playedCardCount + 1))
            {
                printf("    TEST %d PASSED:\n     Player %d's hand and deck are unaffected by player 1's moves.\n",z + 3, z + 1);
            }
        }
    }

    return 0;
}

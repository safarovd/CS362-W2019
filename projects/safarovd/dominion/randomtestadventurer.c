#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "Adventurer"

int main()
{
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, i, j, c;
    int seed = 1000;
    int numPlayers = 2;
    //int arr[3] = {1, 2, 3};
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int cplayer = 0;
    int dSize, hSize;
    struct gameState testG, G;
    srand(time(NULL));
    int rcard, rking, basecount, testcount, disc, diss, disg;

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    for(c = 0; c < 1000; c++){
        basecount = 0;
        testcount = 0;
        disc = 0;
        diss = 0;
        disg = 0;

        initializeGame(numPlayers, k, seed, &G);

        dSize = rand() % (MAX_DECK + 1);
        hSize = rand() % (dSize + 1);

        G.deckCount[cplayer] = dSize - hSize;
        G.handCount[cplayer] = hSize;

//randomly set base deck with treasure cards 

        i = 0;
        while (i < numPlayers){
            j = 0;
            while(j < G.deckCount[i]){
                rcard = rand() % (51);
                rking = rand() % (10);
                if(rcard == 4)
                    G.deck[i][j] = 4;
                else if(rcard == 5)
                    G.deck[i][j] = 5;
                else if(rcard == 6)
                    G.deck[i][j] = 6;
                else
                    G.deck[i][j] = k[rking]; 
                j++;
            }
            i++;
        }

//count to see how many treasure cards are in hand at base state
        i = 0;
        while(i < G.handCount[cplayer])
        {
            if(G.hand[cplayer][i] == 4 || G.hand[cplayer][i] == 5 || G.hand[cplayer][i] == 6)
                basecount++;
            i++;
        }

        memcpy(&testG, &G, sizeof(struct gameState));

        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
//check to see if any of the treasure cards were discaded by mistake
        j = 0;
        while (j < testG.discardCount[cplayer])
        {
            if (testG.discard[cplayer][j] == 4)
                disc += 1;
            else if (testG.discard[cplayer][j] == 5)
                diss += 1;
            else if (testG.discard[cplayer][j] == 6)
                disg += 1;
            j++;
        }

        //check if copper, silver ror gold has been selected after adventure card has been executed 
        i = 0;
        while (i < testG.handCount[cplayer])
        {
            if (testG.hand[cplayer][i] == 4 || testG.hand[cplayer][i] == 5 || testG.hand[cplayer][i] == 6)
                testcount++;
            i++;
        }

        printf("\n\n<------------------------ADVENTURER TEST LOOP %d------------------------->\n\n", c + 1);

        if(basecount + 2 == testcount){
            printf("TEST 1 PASSED:\n Test state gained 2 treasure cards. \n");
        }
        else{
            printf("TEST 1 FAILED:\n Test state did not gain 2 treasure cards.\n Actual: %d \n Expected: %d \n", testcount, basecount + 2);
        }

        printf("\nnext test...\n\n");

        if (testG.handCount[cplayer + 1] == G.handCount[cplayer + 1])
        {
            printf("TEST 2 PASSED:\n Player 2's hand wasn't affected. PLAYER NUM: %d\n", cplayer);
        }

        printf("\nnext test...\n\n");

        if (disc == 0 || diss == 0 || disg == 0){
            printf("TEST 3 PASSED:\n None of the treasure cards were discarded. \n");
        }

        printf("\nnext test...\n\n");

        if(testG.deckCount[cplayer] < G.deckCount[cplayer])
        {
            printf("TEST 4 PASSED:\n Treasure cards were taken out of current player's deck");
        }
    }

    return 0;
}
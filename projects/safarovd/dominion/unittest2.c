#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "isGameOver"

int main(){
    int check, i, endGame = 3;
    int numPlayers = 2;
    int numProvince = 8;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState testG, G;
    int flag;

    initializeGame(numPlayers, k, seed, &G);

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    //transfer over game state to test struct
    memcpy(&testG, &G, sizeof(struct gameState));

    check = isGameOver(&testG);
    //Test to see if game ends at the start.
    if(check == 1)
    {
        printf("TEST 1 FAILED: Game ended with %d provinces.\n", testG.supplyCount[province]);
        flag = -1;
    }
    else
    {
        printf("TEST 1 PASSED: Number of provinces is %d\n", testG.supplyCount[province]);
    }

    //test if the game ends when there are 0 provinces.
    testG.supplyCount[province] = 0;
    check = isGameOver(&testG);
    if ((testG.supplyCount[province] == (G.supplyCount[province] - numProvince)) && check == 1)
    {
        printf("TEST 2 PASSED:\n GAME OVER! \n Number of provinces is %d\n Expected: %d\n", testG.supplyCount[province], (G.supplyCount[province]-8));
    }
    else
    {
        printf("TEST 2 FAILED: Game did not end. There are %d provinces.\n", testG.supplyCount[province]);
        flag = -1;
    }

    //test if the game ends if there are no supply piles left
    testG.supplyCount[province] = G.supplyCount[province];
    printf("RUNNING TEST 3....");
    for (i = 0; i < endGame; i++){
        testG.supplyCount[i] = 0;//empty supply card
        check = isGameOver(&testG);
        if(i < 2 && check == 1){
            assert(check != isGameOver(&G));
            printf("TEST 3 FAILED:\n Three supply piles haven't been emptied yet.");
        }
        else if(i == 2 && check == 1){
            assert(check == !isGameOver(&G));
            printf("\n Supply pile number %d is at %d\n", i + 1, testG.supplyCount[i]);
            printf("TEST 3 PASSED:\n GAME IS OVER! \n Supply piles are all at %d.\n" , testG.supplyCount[i]);
        }
        else {
            printf("\n Supply pile number %d is at %d\n", i + 1, testG.supplyCount[i]);
        }
    }
    //output test results
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
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define TESTCARD "supplyCount"

int main(){
    srand(time(NULL));
    int check = 0;
    int currentCard = 0;
    //int result = 0;
    int i = 0;
    int seed = 1000;
    //int arr[27];
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState testG, G;
    int r = rand() % 27;
    int flag;

    initializeGame(numPlayers, k, seed, &G);

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    //transfer over game state to test struct
    memcpy(&testG, &G, sizeof(struct gameState));

    check = supplyCount(currentCard, &G);
    //0 in supply of the current card
    testG.supplyCount[currentCard] = 0;
    //test for if there is a supply pile for the first card
    if (check != testG.supplyCount[currentCard]){
        printf("TEST 1 PASSED:\n Test output: %d\n Expected output: %d\n", testG.supplyCount[currentCard], (G.supplyCount[currentCard] - 10) );
    }
    else{
        printf("TEST 1 FAILED:\n Test output: %d\n Expected output: %d\n", testG.supplyCount[currentCard], (G.supplyCount[currentCard] - 10));
        flag = -1;
    }
    check = supplyCount(currentCard, &G);
    //10 in supply of the current card
    testG.supplyCount[currentCard] = 10;
    //test for if there is a supply pile for the first card
    if (check == testG.supplyCount[currentCard])
    {
        printf("TEST 2 PASSED:\n Test output: %d\n Expected output: %d\n", testG.supplyCount[currentCard], G.supplyCount[currentCard]);
    }
    else
    {
        printf("TEST 2 FAILED:\n Test output: %d\n Expected output: %d\n", testG.supplyCount[currentCard], G.supplyCount[currentCard]);
        flag = -1;
    }
    //store a random int in the card supply
    for(i = 0; i < 27; i++){
        testG.supplyCount[i] = r;
    }
    check = supplyCount(r, &testG);

    //check if all the supply card counts amount to their desired amount after the function is run. Check at random.
    if(check == r){
        printf("TEST 3 PASSED:\n Test output: %d\n Expected output: %d\n", supplyCount(r, &testG), r);
    }
    else {
        printf("TEST 3 FAILED:\n Test output: %d\n Expected output: %d\n", supplyCount(r, &testG), r);
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
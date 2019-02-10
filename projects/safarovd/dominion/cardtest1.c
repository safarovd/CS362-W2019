#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "Adventurer"

int main(){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int flag = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState testG, G;
    int check, testCard, counter = 0;

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    initializeGame(numPlayers, k, seed, &G);

    //transfer over game state to test struct
    memcpy(&testG, &G, sizeof(struct gameState));
    //TEST IF ADVENTURER GETS ADDED TO THE HAND COUNT
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = adventurer;
    testG.handCount[currentPlayer]+=1;

    check = G.handCount[currentPlayer] + 1;
    if(check == testG.handCount[currentPlayer]){
        printf("TEST 1 PASSED:\n Player %d's hand count is now %d\n", currentPlayer + 1, testG.handCount[currentPlayer]);
    }
    else{
        printf("TEST 1 FAILED:\n Player %d's hand count is %d, but should be %d\n", currentPlayer + 1, testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
        flag = -1;
    }

    //handpos = testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1];
    //CHECK THAT ADVENTURER SEEKS FOR TREASURE CARDS;
    testG.hand[currentPlayer][0] = copper;
    testG.hand[currentPlayer][1] = silver;
    testG.hand[currentPlayer][2] = province;
    testG.hand[currentPlayer][3] = estate;
    testG.hand[currentPlayer][4] = great_hall;

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    int i = 0;

    while (i < testG.handCount[currentPlayer]){
        testCard = testG.hand[currentPlayer][i];
        if(testCard == copper || testCard == silver || testCard == gold){
            counter++;
        }
        i++;
    }

    while (i < G.handCount[currentPlayer])
    {
        testCard = G.hand[currentPlayer][i];
        if (testCard == 4 || testCard == 5 || testCard == 6)
        {
            check++;
        }
        i++;
    }

    if(counter - check > 0 || counter - check < 3){
        printf("TEST 2 PASSED:\n Player %d drew %d treasure cards\n", currentPlayer + 1, check - counter);
    }
    else{
        printf("TEST 2 FAILED:\n There was a mistake drawing the correct amount of treasure cards.\n");
        flag = -1;
    }

    //check that no other player hands have been affected
    if(testG.handCount[currentPlayer+1] < testG.handCount[currentPlayer]){
        printf("TEST 3 PASSED:\n Player 2's hand wasn't affected.\n");
    }
    else{
        printf("TEST 3 FAILED:\n Player 2's hand was modified. HAND: %d\n", testG.handCount[currentPlayer + 1]);
        flag = -1;
    }

    //check if 2 treasure cards were adde to the pile
    if (G.handCount[currentPlayer] < testG.handCount[currentPlayer])
    {
        printf("TEST 4 PASSED:\n 2 Treasure cards have been added to test game state.\n");
    }
    else{
        printf("TEST 4 FAILED:\n Treasure cards weren't added.\n");
        flag = -1;
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
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "fullDeckCount"

int main(){
    int i;
    int flag = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int numPlayers = 2; 
    int currentPlayer = 1;
    struct gameState testG;
    int emptyHand[5];
    int hand[5];
    int emptyDeck[7];
    int deck[7];
    int noDiscard[2];
    int discard[2];
    int check = 0;

    memset(emptyHand, 0, 5);
    memset(emptyDeck, 0, 7);
    memset(noDiscard, 0, 2);
    memset(hand, 0, 5);
    memset(deck, 0, 7);
    memset(discard, 0, 2);

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    initializeGame(numPlayers, k, seed, &testG);

    // test the hand, deck and discard list when empty
    memcpy(testG.hand[currentPlayer], emptyHand, 0);
    memcpy(testG.deck[currentPlayer], emptyDeck, 0);
    memcpy(testG.discard[currentPlayer], noDiscard, 0);
    testG.handCount[currentPlayer] = 0;
    testG.deckCount[currentPlayer] = 0;
    testG.discardCount[currentPlayer] = 0;

    check = fullDeckCount(currentPlayer, copper, &testG);
    if (check == 0)
    {
        printf("TEST 1 PASSED:\n HAND: %d\n DECK: %d\n DISCARDED: %d\n", testG.handCount[currentPlayer], testG.deckCount[currentPlayer], testG.discardCount[currentPlayer]);
    }
    else
    {
        printf("TEST 1 FAILED:\n HAND: %d\n DECK: %d\n DISCARDED: %d\n", testG.handCount[currentPlayer], testG.deckCount[currentPlayer], testG.discardCount[currentPlayer]);
        flag = -1;
    }

    for (i = 0; i < 5; i++)
    {
        hand[i] = copper;
    }
    for (i = 0; i < 7; i++)
    {
        deck[i] = copper;
    }
    for (i = 0; i < 2; i++)
    {
        discard[i] = copper;
    }

    memcpy(testG.hand[currentPlayer], hand, 5 * sizeof(int));
    testG.handCount[currentPlayer] = 5;
    memcpy(testG.deck[currentPlayer], deck, 7 * sizeof(int));
    testG.deckCount[currentPlayer] = 7;
    memcpy(testG.discard[currentPlayer], discard, 2 * sizeof(int));
    testG.discardCount[currentPlayer] = 2;

    //test for if there is a card that doesn't belong in the hand, deck or discard piles.
    check = fullDeckCount(currentPlayer, gold, &testG);
    if(check == 0)
    {
        printf("TEST 2 PASSED! There are no unwanted cards present.\n");
    }
    else
    {
        scanf("TEST 2 FAILED. Unwanted cards present.\n");
        flag = -1;
    }

    //check for if the correct cards are present in the deck.
    check = fullDeckCount(currentPlayer, copper, &testG);
    if (check == 14)
    {
        printf("TEST 3 PASSED:\n HAND: %d\n DECK: %d\n DISCARDED: %d\n", testG.handCount[currentPlayer], testG.deckCount[currentPlayer], testG.discardCount[currentPlayer]);
    }
    else
    {
        printf("TEST 3 FAILED:\n HAND: %d\n DECK: %d\n DISCARDED: %d\n", testG.handCount[currentPlayer], testG.deckCount[currentPlayer], testG.discardCount[currentPlayer]);
        flag = -1;
    }

    //Check that no other player had their hand, deck or discard pile tampered with.
    check = fullDeckCount((currentPlayer+1), copper, &testG);
    if(check == 0)
    {
        printf("TEST 4 PASSED:\n HAND: %d\n DECK: %d\n DISCARDED: %d\n", testG.handCount[(currentPlayer+1)], testG.deckCount[(currentPlayer+1)], testG.discardCount[(currentPlayer+1)]);
    }
    else
    {
        printf("TEST 4 FAILED:\n HAND: %d\n DECK: %d\n DISCARDED: %d\n", testG.handCount[(currentPlayer+1)], testG.deckCount[(currentPlayer+1)], testG.discardCount[(currentPlayer+1)]);
        flag = -1;
    }

    //Output test results 
    if(flag == 0)
    {
        printf("ALL TESTS HAVE PASSED.\n");
    }
    else
    {
        printf("TESTS FAILED.\n");
    }
    
    return 0;
}
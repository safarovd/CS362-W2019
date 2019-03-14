#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define TESTCARD "getCost"

int main(){
    srand(time(NULL));
    int i = 0, counter = 1;
    int flag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState testG, G;
    int cost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    int cardvalue[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    char *cardname[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    int r = rand() % 27;
    int check = 0;

    printf("<<<---------------------TESTING: %s()---------------------->>>\n", TESTCARD);

    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));
//TEST IF EVERY CARD IN THE LIST HAS THE CORRECT MATCHING COST
    for(i = 0; i < 27; i++){
        if (getCost(cardvalue[i]) == cost[cardvalue[i]]){
            counter++;
            if(counter == 27){
                printf("TEST 1 PASSED:\n Price for all cards match correctly\n");
            }
        }
        else{
            printf("TEST 1 FAILED:\n Price for %s is %d\n", cardname[cardvalue[i]], cost[cardvalue[i]]);
            flag = -1;
        }

    }

    //CHECK A BAD CASE
    if (getCost(-10) == -1)
    {
        printf("TEST 2 PASSED:\n BAD CASES ARE NOT ACCEPTED\n");
    }
    else
    {
        printf("TEST 2 FAILED! BAD CASE WAS ACCEPTED.");
        flag = -1;
    }

    //TEST IF THE CARDS AT RANDOM MATCH
    check = getCost(r);
    if(check == cost[r]) {
        printf("TEST 3 PASSED:\n Price for %s chosen at random is %d\n", cardname[r], cost[r]);
    }
    else{
        printf("TEST 3 FAILED:\n Price for %s chosen at random is %d\n", cardname[r], cost[r]);
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
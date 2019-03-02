CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out:
	make clean; make tests; make runtests;

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

tests: randomtestadventurer.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o 
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)


runtests: randomtestadventurer randomtestcard1 randomtestcard2 
	./randomtestadventurer >> randomtestadventurer.out
	gcov -f randomtestadventurer.c >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
	./randomtestcard1 >> randomtestcard1.out
	gcov -f randomtestcard1.c >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	
	./randomtestcard2 >> randomtestcard2.out
	gcov -f randomtestcard2.c >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player tests runtests

clean:
	rm -f *.o playdom.exe playdom player player.exe tests randomtestcard2.out randomtestcard1.out randomtestadventurer.out tests.exe *.gcov *.gcda *.gcno *.so *.out randomtestadventurer randomtestadventurer.exe randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe

CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: testme

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	./testme

coverage: testme.c
	gcov -b ./testme

clean:
	rm testme

cleanall:
	rm testme *.gcda *.gcno *.gcov *.out
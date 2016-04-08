CC = gcc

CFLAGS = -Wall -g



clean: 
	rm ./mygenerator

	rm ./examine

	rm *.o


all: generate examine



generate: mygenerator.c

	$(CC) $(CFLAGS) -o mygenerator mygenerator.c

	./mygenerator datafile 10000



examine: examine.c generate


	$(CC) -fopenmp $(CFLAGS) -o examine examine.c

	./examine -1 -1 datafile -1 -1

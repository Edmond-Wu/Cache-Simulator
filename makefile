CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -m32

c-sim : c-sim.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm c-sim


CC=gcc

# The line with -DDEBUG can be used for development. When
# building your code for evaluation, however, the line *without*
# the -DDEBUG will be used.
#

CFLAGS=-c -Wall -g -DDEBUG -std=c99 -O0


all: q_evaluate

q_evaluate: q_evaluate.o list.o emalloc.o
	$(CC) q_evaluate.o list.o emalloc.o -o q_evaluate

q_evaluate.o: q_evaluate.c list.h emalloc.h
	$(CC) $(CFLAGS) q_evaluate.c

list.o: list.c list.h emalloc.h
	$(CC) $(CFLAGS) list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o q_evaluate

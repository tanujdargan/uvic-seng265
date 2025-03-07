
CC=gcc

# The line with -DDEBUG can be used for development. When
# building your code for evaluation, however, the line *without*
# the -DDEBUG will be used.
#

CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99 -O0

all: tester

tester: tester.o emalloc.o
	$(CC) tester.o emalloc.o -o tester

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o tester 

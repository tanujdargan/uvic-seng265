
CC=gcc

# The line with -DDEBUG can be used for development. When
# building your code for evaluation, however, the line *without*
# the -DDEBUG will be used.
#

CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99 -O0


all: tester

tester: tester.o 
	$(CC) tester.o -o tester

clean:
	rm -rf *.o tester 

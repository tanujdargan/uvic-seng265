
CC=gcc

# The line with -DDEBUG can be used for development. When
# building your code for evaluation, however, the line *without*
# the -DDEBUG will be used.
#

CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99 -O0


all: spf_analyzer

spf_analyzer: spf_analyzer.o list.o emalloc.o
	$(CC) spf_analyzer.o list.o emalloc.o -o spf_analyzer

spf_analyzer.o: spf_analyzer.c list.h emalloc.h
	$(CC) $(CFLAGS) spf_analyzer.c

list.o: list.c list.h emalloc.h
	$(CC) $(CFLAGS) list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o spf_analyzer 

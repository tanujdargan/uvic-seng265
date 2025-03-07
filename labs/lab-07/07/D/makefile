
CC=gcc

# The line with -DDEBUG can be used for development. When
# building your code for evaluation, however, the line *without*
# the -DDEBUG will be used.
#

CFLAGS=-c -Wall -g -DDEBUG -std=c99 -O0


all: q_expression

q_expression: q_expression.o list.o emalloc.o
	$(CC) q_expression.o list.o emalloc.o -o q_expression

q_expression.o: q_expression.c list.h emalloc.h
	$(CC) $(CFLAGS) q_expression.c

list.o: list.c list.h emalloc.h
	$(CC) $(CFLAGS) list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o q_expression

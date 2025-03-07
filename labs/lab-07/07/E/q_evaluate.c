#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

#define MAX_LINE_LEN 80

void inccounter(node_t *p, void *arg);
void print_node(node_t *p, void *arg);
void analysis(node_t *l);

int main(int argc, char *argv[]) {

/* 
 * Note that the expression in the example above is a postfix expression. 
 * 23 15 - 10 * is the same as (23-15)*10.
 * In part 2, you will use the linkedlist that you created, to evaluate the expression
 * and print the final result. 
 * You will need to use a linked list like a stack, in order to evaluate the expression.
 * If you do not know how to evaluate the expression using a stack, ask your lab instructor,
 * who can give you a demonstration. 
 * Try the following expressions
 *              '31 21 + 2 * 9 -'       : Answer should be 95
 *              '23 18 + 89 * 2 -'      : Answer should be 3647
 *              '100 10 20 3 * + + 5 /' : Answer should be 34 
 *
 * REMEMBER TO FREE DYNAMIC MEMORY WHERE APPROPRIATE.
 * You will need to modify the make file if you want to use it to compile this program.
 * You may use some of your code from q_expression.c 
 */

    if (argc != 2) {
        fprintf(stderr, "usage: %s <some string>\n", argv[0]);
        exit(1);
    }

    // COMPLETE IMPLEMENTATION

    exit(0); 
}

void inccounter(node_t *p, void *arg) {
    int *ip = (int *)arg;
    (*ip)++;
}


void print_node(node_t *p, void *arg) {
    char *fmt = (char *)arg;
    printf(fmt, p->op, p->val);
}


void analysis(node_t *l) {
    int len = 0;

    apply(l, inccounter, &len);    
    printf("Number of nodes: %d\n", len);

    apply(l, print_node, "%c:%d\n");
}

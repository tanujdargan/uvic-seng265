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
 * Program when run will take an expression from the command line 
 * and store it in a linked list. For example:
 *    ./q_expression '23 15 - 10 *' 
 * will store data into 5 nodes.  (Notice the use of strong quotes
 * for the argument provided to q_expression.)
 *
 *      Node 1: op:"v", val:23 (This is the head node; next is node 2)
 *      Node 2: op:"v", val:15 (next is node 3)
 *      Node 3: op:"-", val:0  (next is node 4)
 *      Node 4: op:"v", val:10 (next is node 5)
 *      Node 5: op:"*", val:0  (as this is the tail node, next is null)
 *
 * Note that when the item is a number, it is stored in val 
 * with the op as "v" and when the item is a mathematical operation 
 * (*, -, +, /), it is stores in op with the val as 0 .
 *
 * REMEMBER TO FREE DYNAMIC MEMORY WHERE APPROPRIATE.
 */

    if (argc != 2) {
        fprintf(stderr, "usage: %s <some string>\n", argv[0]);
        exit(1);
    }

    /* COMPLETE IMPLEMENTATION BELOW. */


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

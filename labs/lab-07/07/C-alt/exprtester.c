#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LEN 80

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


int main(int argc, char *argv[]) {
    node_t *list = NULL;

    list = add_front(list, new_node('v', 100));
    list = add_front(list, new_node('v', 50));
    list = add_front(list, new_node('+', 0));
    list = add_front(list, new_node('v', 2));
    list = add_front(list, new_node('*', 0));
 
    analysis(list);

    exit(0); 
}

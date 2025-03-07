#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LEN 80

void inccounter(node_t *p, void *arg) {
    int *ip = (int *)arg;
    (*ip)++;
}


void print_word(node_t *p, void *arg) {
    char *fmt = (char *)arg;
    printf(fmt, p->name, p->birth_year);
}


void analysis(node_t *l) {
    int len = 0;

    apply(l, inccounter, &len);    
    printf("Number of actors: %d\n", len);

    apply(l, print_word, "%s (born %d)\n");
}


int main(int argc, char *argv[]) {
    node_t *list = NULL;

    list = add_inorder(list, new_node("Bishop, John", 1966));
    list = add_inorder(list, new_node("Cusack, John", 1966));
    list = add_inorder(list, new_node("Rhys-Davies, John", 1944));
    list = add_inorder(list, new_node("Depp, Johnny", 1963));
    list = add_inorder(list, new_node("Wayne, John", 1907));
    list = add_inorder(list, new_node("Malkovich, John", 1953));
    list = add_inorder(list, new_node("Oliver, John", 1977));
    list = add_inorder(list, new_node("Higgins, John Michael", 1966));
    list = add_inorder(list, new_node("Glover, John", 1944));

 
    analysis(list);

    node_t  *temp_n = NULL;
    for ( ; list != NULL; list = temp_n ) {
        temp_n = list->next;
        free(list->name);
        free(list);
    } 
 
    exit(0); 
}

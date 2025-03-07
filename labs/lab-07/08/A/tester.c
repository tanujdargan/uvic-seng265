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
    printf(fmt, p->word);
}


void analysis(node_t *l) {
    int len = 0;

    apply(l, inccounter, &len);    
    printf("Number of words: %d\n", len);

    apply(l, print_word, "%s\n");
}


int main(int argc, char *argv[]) {
    char *line = NULL;
    char *t;
    int  num = 0;
    node_t *list = NULL;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <some string>\n", argv[0]);
        exit(1);
    }

    line = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
    if (line == NULL) {
        fprintf(stderr,
            "Argh. Something bad happened with malloc. :-(\n");
    }

    strcpy(line, argv[1]);

    t = strtok(line, " ");
    while (t) {
        num++;
        list = add_inorder(list, new_node(t)); 
        t = strtok(NULL, " ");
    }
 
    analysis(list);

    node_t  *temp_n = NULL;
    for ( ; list != NULL; list = temp_n ) {
        temp_n = list->next;
        free(list->word);
        free(list);
    } 

    free(line);
 
    exit(0); 
}

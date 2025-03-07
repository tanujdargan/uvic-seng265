#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"

#define MAX_WORDS 10

int comparator(const void *a, const void *b) {
    char *c_a = *(char **)a;
    char *c_b = *(char **)b;

    return (strcmp(c_a, c_b));
}

int main(int argc, char *argv[]) {
    char *line;
    char **words;
    char *t;
    int  num;
    int  i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <some string>\n", argv[0]);
        exit(1);
    }

    line = strdup(argv[1]);
    words = (char **)emalloc(sizeof(char *) * MAX_WORDS);

    num = 0; 
    t = strtok(line, " ");
    while (t && num < MAX_WORDS) {
        words[num] = strdup(t);
        t = strtok(NULL, " ");
        num++;
    }

    printf("BEFORE qsort:\n------------\n");
    for (i = 0; i < num; i++) {
        printf("%2d:%s\n", i, words[i]);
    }

    printf("\n");
    qsort(words, num, sizeof(char *), comparator);

    printf("AFTER qsort:\n------------\n");
    for (i = 0; i < num; i++) {
        printf("%2d:%s\n", i, words[i]);
    }

    for (i = 0; i < num; i++) {
        free(words[i]);
    }
    free(words);
    free(line);
 
    exit(0); 
}

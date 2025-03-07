#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20

int main(int argc, char *argv[]) {
    char *line = NULL;
    char *t;
    int  num = 0;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <some string>\n", argv[0]);
        exit(1);
    }

    line = (char *)malloc(sizeof(char) * MAX_LEN);
    if (line == NULL) {
        fprintf(stderr,
            "Argh. Something bad happened with malloc. :-(\n");
    }

    strcpy(line, argv[1]);

    t = strtok(line, " ");
    while (t) {
        num++;
        printf("Word: %s\n", t);
        t = strtok(NULL, " ");
    }
  
    printf("Number of words: %d\n", num);
 
    exit(0); 
}

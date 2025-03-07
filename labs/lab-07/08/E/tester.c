#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"

#define MAX_NUMS 1000
#define MAX_LINE_LEN 50


/* Recall: if item represented by `a` comes before the
 * item represented by `b`, then a negative value is returned;
 * if `a` comes after `b`, then a positive value is returned;
 * otherwise 0 is return. Also: 1 and -1 are suitable negative
 * and positive values.
 */
int compare_two_doubles(const void *a, const void *b) {
    double *da = (double *)a;
    double *db = (double *)b;
    
    if (*da < *db) {
        return -1;
    } else if (*da > *db) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    double *data;
    int     i;
    int     nums;
    double  temp;
    char    line[MAX_LINE_LEN];

    data = (double *)emalloc(MAX_NUMS * sizeof(double));

    nums = 0;
    while (fgets(line, MAX_LINE_LEN, stdin)) {
        temp = atof(line);
        data[nums] = temp;
        nums++;

        if (nums == MAX_NUMS) {
            break;
        }
    }

    printf("BEFORE qsort:\n------------\n");
    for (i = 0; i <nums; i++) {
        printf("%12.8f\n", data[i]);
    } 

    printf("\n");
    qsort(data, nums, sizeof(double), compare_two_doubles);

    printf("AFTER qsort:\n------------\n");
    for (i = 0; i < nums; i++) {
        printf("%12.8f\n", data[i]);
    }

    free(data);

    exit(0); 
}

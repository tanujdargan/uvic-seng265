#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMS 10

int comparator(const void *a, const void *b) {
    long l_a = *(long *)a;
    long l_b = *(long *)b;

    /* if l_a < l_b, then a negative integer is to be returned.
     * if l_a > l_b, then a positive integer is to be returned.
     * if l_a == l_b, then zero is to be returned.
     */
    return (l_a - l_b);  /* There *could* be a subtle bug here... */
}


int main(int argc, char *argv[]) {
    long numbers[MAX_NUMS];
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <some seed value>\n", argv[0]);
        exit(1);
    }

    srandom(atoi(argv[1]));

    printf("BEFORE qsort:\n------------\n");
    for (i = 0; i <MAX_NUMS; i++) {
        numbers[i] = random();
        printf("%12ld\n", numbers[i]);
    } 

    printf("\n");
    qsort(numbers, MAX_NUMS, sizeof(long), comparator);

    printf("AFTER qsort:\n------------\n");
    for (i = 0; i < MAX_NUMS; i++) {
        printf("%12ld\n", numbers[i]);
    }
    printf("\n");

    printf("Address of 'comparator' function: %lx\n",
        (unsigned long)comparator);
    printf("Address of 'numbers' array %lx\n",
        (unsigned long)numbers);
 
    exit(0); 
}

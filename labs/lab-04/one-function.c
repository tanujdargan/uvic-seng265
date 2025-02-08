/** @file one-function.c
 *  @brief A sample program for Lab 04.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main()
{
    int a;
    int b;
    int *pp;

    a = 10;
    b = 20;

    printf("%d %d\n", a, b);

    pp = &a;
    *pp = 333;

    printf("%d %d\n", a, b);

    pp = &b;
    a = 444;
    b = 555;

    printf("%d %d\n", a, b);
    printf("%d\n", *pp);
    printf("%p\n", (void *)pp);
}

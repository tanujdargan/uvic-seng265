/** @file danger.c
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
 * Function: rotate
 * --------------
 * @brief Rotates the numbers of different variables in the program.
 *
 * @param m The address of a program's variable.
 * @param n The address of a program's variable.
 * @param p The address of a program's variable.
 * @param q The address of a program's variable.
 *
 */
void rotate(int *m, int *n, int *p, int *q)
{
    int temp;
    temp = *m;

    *m = *n;
    *n = *p;
    *p = *q;
    *q = temp;
}

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
    int a = 111;
    int b = 222;
    int c = 333;
    int d = 444;

    printf("%d %d %d %d\n", a, b, c, d);

    rotate(&a, &b, &c, &d);
    printf("%d %d %d %d\n", a, b, c, d);

    rotate(&a, &b, &c, &d);
    printf("%d %d %d %d\n", a, b, c, d);
}

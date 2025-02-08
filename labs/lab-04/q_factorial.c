/** @file q_array_rotate.c
 *  @brief Submission program for Lab 04.
 *
 *  This program calculates the factorial of a number provided as a
 *  command line argument.
 *
 *  Usage example:
 *  ./q_array_rotate 5
 *
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Tanuj D.
 */

#include <stdio.h>
#include <stdlib.h>

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
int main(int argc, char *argv[])
{
    // variable to store the final answer
    double factorial = 1.0;
    int num = 0;
    
    // WRITE YOUR CODE TO DO COMMAND LINE INPUT CHECKING HERE (DONE)
    // Check if an argument was provided (argc must be at least 2)
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return 1;
    }

    // Takes the command line input and converts it into int.
    num = atoi(argv[1]);

    // If num is negative, factorial isn't defined in the usual sense.
    if (num < 0)
    {
        fprintf(stderr, "Error: Factorial of a negative number is undefined.\n");
        return 1;
    }

    // WRITE YOUR CODE TO DO THE FACTORIAL CALCULATIONS HERE (DONE)
    // Calculate factorial for num
    for (int i = 1; i <= num; i++)
    {
        factorial *= i;
    }

    printf("%.0f\n", factorial);
    return 0;
}

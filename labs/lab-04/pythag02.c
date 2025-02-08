/** @file pythag02.c
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
#include <math.h>
#include <stdio.h>

/**
 * Function: pythag
 * --------------
 * @brief Calculates the hypotenuse given two sides of a triangle.
 *
 * @param double a A side from the triangle.
 * @param double b A side from the triangle
 * @return int The hypotenuse given two sides of a triangle.
 *
 */
double pythag(double a, double b)
{
    return sqrt(a * a + b * b);
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
    printf("Right triangle with sides %.2f and %.2f has "
           "hypotenuse of length %.2f\n",
           10.0, 13.0, pythag(10, 13));

    printf("Right triangle with sides %.2f and %.2f has "
           "hypotenuse of length %.2f\n",
           21.9, 31.2, pythag(21.9, 31.2));

    printf("Right triangle with sides %.2f and %.2f has "
           "hypotenuse of length %.2f\n",
           719.21, 21.2, pythag(719.21, 21.2));
}

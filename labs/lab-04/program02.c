
/** @file program02.c
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
#include <stdlib.h>
#include <math.h>

/**
 * Function: expo
 * --------------
 * @brief Demonstrates the use of the pow() function.
 *
 * @param int a The first input number.
 * @param int b The second input number.
 * @return int Returns pow(a,b)
 *
 */
int expo(int a, int b)
{

        double c = pow(a, b);

        printf("Answer is %f\n", c);
        return c;
}

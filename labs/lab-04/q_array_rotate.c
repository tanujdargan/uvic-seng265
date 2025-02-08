/** @file q_array_rotate.c
 *  @brief Submission program for Lab 04.
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

#define MAX_SIZE 10

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

    int i = 0;
    char *sep = "";
    // declare and initialize an int array arr_1 of size MAX_SIZE and initialize it with random values
    // For example, declare and initialize arr_1 to {1,2,3,4,5,6,7,8,9,10}
    int arr_1[MAX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // This for statement prints the content of arr_1 to console
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");

    // call rotate() with num = 1

    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");
    // Outcome on console from the above for loop should be 2, 3, 4, 5, 6, 7, 8, 9, 10, 1

    // call rotate() with num = 2

    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%s%d", sep, arr_1[i]);
        sep = ", ";
    }
    printf("\n");
    // Outcome on console from the above for loop should be 4, 5, 6, 7, 8, 9, 10, 1, 2, 3
}

/*
 * Design a function rotate(int num, .........) that take a number as a parameter (int num) and any other parameters as required
 * When called, the function will modify arr_1 by moving each of its values to an index lowered by num. If the new index becomes negative, then MAX_SIZE is added to get the correct index
 * For example, if num = 2, then a number at index 4 is moved to index 2 (4 - num) and a number at index 1 is moved to index 9(1 - num + MAX_SIZE)
 * Another example, if at the start, arr_1 is {2,4,6,8,1,5},
 * calling arr_1 with num = 2 should change arr_1 to {6,8,1,5,2,4}
 */

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

#define MAX_NUMS 5

/**
 * Function: rogue
 * --------------
 * @brief This function goes crazy.
 *
 * @param numbers A pointer to the array of numbers.
 * @param num The size of the array.
 *
 */
void rogue(int *numbers, int num)
{
    int i;

    for (i = -2; i <= num; i++)
    {
        numbers[i] = 111 * i + 11;
    }
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
    int innocent = 123;
    int nums[MAX_NUMS] = {1, 2, 3, 4, 5};
    int really_innocent = 456;
    int i;

    printf("%d %d\n", innocent, really_innocent);
    for (i = 0; i < MAX_NUMS; i++)
    {
        printf("%d: %d\n", i, nums[i]);
    }

    rogue(nums, MAX_NUMS);

    printf("----------------\n");
    printf("%d %d\n", innocent, really_innocent);
    for (i = 0; i < MAX_NUMS; i++)
    {
        printf("%d: %d\n", i, nums[i]);
    }
}

#!/usr/bin/env python3

import datetime


def init():
    return [(datetime.datetime(2020, 1, 20), datetime.datetime(2020, 3, 7)),
        (datetime.datetime(2020, 4, 18), datetime.datetime(2020, 5, 16)),
        (datetime.datetime(2020, 1, 1), datetime.datetime(2020, 5, 28)),
        (datetime.datetime(2020, 1, 22), datetime.datetime(2020, 2, 7)),
        (datetime.datetime(2020, 2, 10), datetime.datetime(2020, 4, 18)),
        (datetime.datetime(2020, 2, 21), datetime.datetime(2020, 6, 12)),
        (datetime.datetime(2020, 4, 2), datetime.datetime(2020, 6, 7)),
        (datetime.datetime(2020, 5, 16), datetime.datetime(2020, 5, 26)),
        (datetime.datetime(2020, 3, 19), datetime.datetime(2020, 4, 21)),
        (datetime.datetime(2020, 6, 3), datetime.datetime(2020, 6, 12))]


"""
The following won't work immediately as you must as first add
parameters to the function definition.
"""

def within_deadline():
    """
    The first parameter is a datetime, the second paramter is a
    datetime, and the first is guaranteed to be before the second 
    in time. The third parameter is the number of days corresponding
    to a "deadline". If the second datetime is within the deadline (that
    is, the first datetime + number of days), then return True; otherwise
    return False.
    """

    return False


def main():
    data = init()
    white_space = ""
    for (d1, d2) in data:
        print(white_space, end="")

        print(d1)
        print(d2)
        if within_deadline(d1, d2, 14):
            print("Dates ARE within 14 days of each other")

            # Modify this line with a suitable call to
            # strftime().
            #
            # |||||||||||||||||||||||||||||||
            # VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
            print("The first date is a <???>")
        else:
            print("Dates are NOT within 14 days of each other")
        
        white_space = "\n"


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import datetime


def init():
    result = [datetime.datetime(1971, 12, 25),
        datetime.datetime(1980, 7, 26),
        datetime.datetime(1954, 7, 17),
        datetime.datetime(1953, 6, 15),
        datetime.datetime(1946, 6, 14),
        datetime.datetime(1964, 6, 19),
        datetime.datetime(1977, 12, 21),
        datetime.datetime(1952, 10, 7),
        datetime.datetime(1955, 3, 21),
        datetime.datetime(1985, 11, 16),
        datetime.datetime(1961, 2, 24),
        datetime.datetime(1962, 7, 21),
        datetime.datetime(1956, 8, 31),
        datetime.datetime(1954, 9, 21),
        datetime.datetime(1966, 4, 28),
        datetime.datetime(1954, 2, 12),
        datetime.datetime(1979, 1, 18),
        datetime.datetime(1964, 8, 8),
        datetime.datetime(1961, 3, 8),
        datetime.datetime(1977, 11, 19)
    ]

    return result    


"""
The following won't work immediately as you must as first add
parameters to the function definition.  
"""

def before():
    """
    Given a list of datetimes along with a year, month, and day
    as integers, return the list of all datetimes that are before
    that year/month/day.
    """
    return []


def main():
    birthdates = init()

    # All birthdates before March 1, 1960

    older = before(birthdates, 1960, 3, 1)

    for d in older:
        print(d)


if __name__ == "__main__":
    main()

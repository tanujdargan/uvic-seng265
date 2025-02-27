#!/usr/bin/env python3

import datetime

def main():
    """
    Create a datetime object for today's date
    """

    # COMPLETE IMPLEMENTATION
    todays_date = datetime.datetime.now().date()

    date_list = every_lab(todays_date)

    """
    variable date_list should contain datetime objects 
    for all the days when you have a lab
    print these dates in the format "Mon, 15 Jan 21"
    """

    # COMPLETE IMPLEMENTATION
    for lab_date in date_list:
        print(lab_date.strftime("%a, %d %b %y"))


def every_lab(todays_date):
    """
    Assume that you have a lab every week till the end of classes. 
    (Only your lab, in this instance.)

    This function will create datetimes objects for those labs, 
    add them to a list and then return this list
    """

    # COMPLETE IMPLEMENTATION
    lab_dates = []

    # Classes end on April 4th, 2025
    end_date = datetime.date(2025, 4, 4)

    # Labs are on Fridays (weekday 4, as Monday is 0)
    lab_weekday = 4

    # Find the next Friday from today's date
    days_until_friday = (lab_weekday - todays_date.weekday()) % 7

    # If today is Friday, include it
    if days_until_friday == 0:
        next_lab = todays_date
    else:
        next_lab = todays_date + datetime.timedelta(days=days_until_friday)

    # Add all lab dates until the end of classes
    current_date = next_lab
    while current_date <= end_date:
        lab_dates.append(current_date)
        current_date = current_date + datetime.timedelta(days=7)  # Next Friday

    return lab_dates


if __name__ == "__main__":
    main()

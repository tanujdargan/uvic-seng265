#!/usr/bin/env python3

import datetime

def main():
    """
    Florence is a nurse in a clinic. She is caring for 4 patients on
    different medication schedules

    * Mark needs medication every 5 hours
    * Susan needs medication every 3 hours
    * Chloe needs medication every 8 hours
    * Alexander needs medication every 10 hours

    Starting with your current day and time, make a care schedule
    for the next 14 days that Florence can use to schedule
    who needs medication at what time.

    HINT: Create datetime objects for all times. Convert to ical
    and then sort. Now convert back to datetime objects to print out
    the final schedule.

    Follow the steps provided.

    STEP 1: Use function patient_schedule to get a list of
    medication times for every patient
    medication times in the list are in ical format

    mark_schedule = <...........COMPLETE..................>
    susan_schedule = <...........COMPLETE..................>
    chloe_schedule = <...........COMPLETE..................>
    alexander_schedule = <...........COMPLETE..................>


    STEP 2: Combine all the lists and then form a master list of
    when medication is required by which patient.

    Print the medication schedule sorted by time in the format below:

      Friday, 25 03 2021, 09:24:27 Time to give medication to Alexander
      Friday, 25 03 2021, 10:24:27 Time to give medication to Chloe

    Refer to florence_sched.txt to see what the final output
    should look like. You are not required to write this information
    to a file. Simply output to console is enough.

    HINT: You will need to keep track of who needs medication when.
    One way of doing this is with a dictionary. You may choose to
    use other ways.
    """

    # COMPLETE YOUR IMPLEMENTATION


def patient_schedule(patient_name, med_interval):
    """
    This function will take a patient name and corresponding
    medication interval and return a list of times when the patient needs
    medication, in ical format.  The function should use datetime_to_ical
    function.
    """

    # COMPLETE YOUR IMPLEMENTATION



def datetime_to_ical(dtime):
    """
    This function will take a datetime object and convert it into
    ical format string and return it.

    HINT: try print(dtime.year)
    you can do the same thing for month, day, hour, minute and second
    """

    # COMPLETE IMPLEMENTATION



def ical_to_datetime(ical):
    """
    This function will take an ical string and convert it into
    a datetime object and return it.
    """

    # COMPLETE IMPLEMENTATION


if __name__ == "__main__":
    main()

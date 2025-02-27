#!/usr/bin/env python3

import datetime
import sys

def main():
    """florence_sched.txt contains a list of dates and times 
       when patients need medications

       * There are 3 nurse available on duty. 
       * Florence works from 8:00:00 hrs to 15:59:59 hrs
       * Dana works from 16:00:00 hrs to 23:59:59 hrs
       * Sam works from 00:00:00 hrs to 7:59:59 hrs

       15:59:59 hours is in format hour:minute:second

       Read the file florence_schedule by piping at the command line, 
       using the command:

       ./q_care_schedule.py < florence_sched.txt

       The output is a printout of the sorted care schedule for each nurse.

       See file care_sched_nurses.txt to see what the output should 
       look like.

       HINT: You may use the datetime.time to compare hours of work 
       with medication requirement timings. 
    """

    # COMPLETE IMPLEMENTATION

if __name__ == "__main__":
    main()




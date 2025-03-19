#!/usr/bin/env python3

import re
import datetime
import fileinput


template = """SUBSCRIPTION EXPIRY MESSAGE

==FIRST== ==LAST==
==TODAY==


Dear ==FIRST==:

Our records show that your subscription to "Unix Users Quarterly"
expired on ==EXPIRY==. 

If you would like to keep your subscription active, we request 
payment by ==SIX-WEEKS-FROM-TODAY==.

Yours sincerely,

Uriah Heep
"""

dirpath = "messages/"


def main():
    today = datetime.date.today()
    six_weeks_from_today = today + datetime.timedelta(weeks=6)

    today = today.strftime("%B %d %Y")
    six_weeks_from_today = six_weeks_from_today.strftime("%B %d %Y")

    for line in fileinput.input():
        line = line.rstrip()
        (last, first, date, code) = line.split(",")
        
        message = re.sub("==FIRST==", first, template)
        message = re.sub("==LAST==", last, message)
        message = re.sub("==TODAY==", today, message)
        message = re.sub("==SIX-WEEKS-FROM-TODAY==", 
            six_weeks_from_today, message)
        message = re.sub("==EXPIRY==", date, message)

        f = open(dirpath + code + ".txt", "w")
        f.write(message)
        f.write("\n")
        f.close()

if __name__ == "__main__":
    main()

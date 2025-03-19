#!/usr/bin/env python3
"""
Obtain and print the names of the packages without the cpu architecture (similar to A/installed4.py) that were installed within
the range of dates provided by the user (i.e., variables date_from and date_to). 

* Dates provided by the user should follow the format yyyy-mm-dd
* The output for each package belonging to the specified range should be:
yyyy-mm-dd: NAME_OF_PACKAGE
* An example of output from the program is described in range-2020-07-15-to-2020-07-16.txt

"""

import re
import sys
from datetime import datetime

def main():
    if len(sys.argv) < 3:
        sys.exit(0)
    date_from = sys.argv[1]
    date_to = sys.argv[2] 
    
    try:
        # Convert dates to datetime objects for comparison
        date_from_obj = datetime.strptime(date_from, "%Y-%m-%d")
        date_to_obj = datetime.strptime(date_to, "%Y-%m-%d")
    except ValueError:
        sys.exit(0)  # Exit silently if dates are invalid
    
    # Dictionary to track unique package events per date in order of appearance
    packages_seen = {}  # {(date, package): True}
    package_events = []
    
    try:
        with open('dpkg.log') as file:
            for line in file:
                # Extract date from log line
                date_match = re.match(r"(\d{4}-\d{2}-\d{2})", line.strip())
                if not date_match:
                    continue
                    
                date_str = date_match.group(1)
                log_date = datetime.strptime(date_str, "%Y-%m-%d")
                
                # Check if date is in range
                if date_from_obj <= log_date <= date_to_obj:
                    # Check for status installed
                    if "status installed" in line:
                        package_match = re.search(r"status installed ([^:]+):([^ ]+)", line)
                        if package_match:
                            package_name = package_match.group(1)
                            # Skip if we've seen this package for this date already
                            if (date_str, package_name) not in packages_seen:
                                packages_seen[(date_str, package_name)] = True
                                package_events.append((date_str, package_name))
                    
                    # Check for remove events
                    elif "remove " in line:
                        package_match = re.search(r"remove ([^:]+):([^ ]+)", line)
                        if package_match:
                            package_name = package_match.group(1)
                            # Skip if we've seen this package for this date already
                            if (date_str, package_name) not in packages_seen:
                                packages_seen[(date_str, package_name)] = True
                                package_events.append((date_str, package_name))
    except FileNotFoundError:
        sys.exit(0)  # Exit silently if dpkg.log is not found
    
    # Print all package events in the order they were first seen
    for date, package in package_events:
        print(f"{date}: {package}")

if __name__ == "__main__":
    main()
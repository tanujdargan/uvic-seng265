#!/usr/bin/env python
import re


def main():
    line_number: int = 0
    with open('logs.txt') as file:
        for line in file:
            line_number += 1
            m = re.search(r"installed (.+) .*", line.rstrip())
            if m:
                print("%d: %s" % (line_number, m.group(1)))


if __name__ == "__main__":
    main()

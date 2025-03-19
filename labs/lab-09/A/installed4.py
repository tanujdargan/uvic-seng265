#!/usr/bin/env python
import re


def main():
    line_number: int = 0

    # compiling the pattern first for best efficiency
    pattern = re.compile(r" installed ((.+):(.+)) .*")

    with open('logs.txt') as file:
        for line in file:
            line_number += 1
            m = pattern.search(line.rstrip())
            if m:
                print("%d: %s" % (line_number, m.group(2)))


if __name__ == "__main__":
    main()

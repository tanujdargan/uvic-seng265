#!/usr/bin/env python3

import re


def main():

    info = [("F", "Faraday Constant", 96485.332, "England"),
        ("c", "speed of light", 299792458, "Denmark"),
        ("h", "Planck Constant", 6.626e-34, "Germany"),
        ("m_e", "electron mass", 9.109e-31, "Great Britain")]

    text = """The ==NAME== (symbol '==SYMBOL==') has the magnitude ==VALUE==.
This was determined first in ==COUNTRY==.
"""

    for (symbol, name, number, place) in info:
        final = re.sub(r"==NAME==", name, text)
        final = re.sub(r"==SYMBOL==", symbol, final)
        final = re.sub(r"==COUNTRY==", place, final)
        final = re.sub(r"==VALUE==", "%.5E" % number, final)

        print(final)
        

if __name__ == "__main__":
    main()

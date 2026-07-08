#!/usr/bin/env python3
"""
prx_decompress.py

Minimal PRX decompressor: strips the 0x150-byte header and gzip-inflates
the rest back into a plain ELF file.
"""

import sys
import gzip
from io import BytesIO

HEADER_SIZE = 0x150


def prx_decompress(output, input):
    a = open(input, "rb")
    data = a.read()
    a.close()

    prx = data[HEADER_SIZE:]

    temp = BytesIO(prx)
    f = gzip.GzipFile(fileobj=temp, mode='rb')
    elf = f.read()
    f.close()

    a = open(output, "wb")
    a.write(elf)
    a.close()


def main():
    if len(sys.argv) < 3:
        print("Usage: %s outfile infile\n" % (sys.argv[0]))
        exit(-1)

    prx_decompress(sys.argv[1], sys.argv[2])


if __name__ == "__main__":
    main()


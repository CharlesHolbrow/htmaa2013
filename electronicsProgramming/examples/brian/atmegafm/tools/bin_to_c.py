#!/usr/bin/env python

import sys


def make_c_data(infile, outfile, array_name):
    bytesd = []
    while True:
        c = infile.read(1)
        if len(c) < 1:
            break
        bytesd.append(ord(c))

    #print """#include "song.h" """
    
    outfile.write("const PROGMEM uint8_t %s[%d] = {\n" % (array_name, len(bytesd)))
    outfile.write("    ")

    for i in range(len(bytesd)):
        sep = ""
        if i < len(bytesd) - 1:
            sep = ","
        outfile.write("% 4d%s" % (bytesd[i], sep))
        if i%8 == 7:
            outfile.write("\n    ")
    outfile.write("};\n\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "usage: %s <input.bin> > output.c" % sys.argv[0]
        sys.exit(1)

    infile = open(sys.argv[1], "rb")
    outfile = sys.stdout
    make_c_data(infile, outfile, "song_data")


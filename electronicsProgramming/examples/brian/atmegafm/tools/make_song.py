#!/usr/bin/env python

import sys
from bin_to_c import make_c_data

if len(sys.argv) < 3:
    print "Usage: %s c|h <files>" % sys.argv[0]
    sys.exit(1)

makec = False

mode = sys.argv[1]
if mode != 'c' and mode != 'h':
    print "error: first argument must be c or h"
    sys.exit(1)

if mode == 'c':
    makec = True

files = sys.argv[2:]
print "Generating song.%s for song files:" % (mode,),  files

songnames = []

if makec:
    outfile = open("song.c", "w")
    outfile.write("""#include "song.h"\n\n""")

    for songfile in files:
        name = songfile.replace(".bin", "")
        songnames.append(name)
        infile = open(songfile, "rb")
        make_c_data(infile, outfile, "song_%s" % name)
        infile.close()

    outfile.write("const uint8_t *songs[%d] = {\n" % len(songnames))
    for songname in songnames:
        outfile.write("    song_%s" % songname)
        if songname != songnames[-1]:
            outfile.write(",")
        outfile.write("\n")
    outfile.write("};\n\n")

    outfile.close()
    sys.exit(0)

# else, we're making the header

outfile = open("song.h", "w")
outfile.write("""
#ifndef __song_h_
#define __song_h_

#include <avr/pgmspace.h>
#include <stdint.h>

#define N_SONGS %d

extern const uint8_t *songs[N_SONGS];

#endif // __song_h_

""" % len(files))

outfile.close()



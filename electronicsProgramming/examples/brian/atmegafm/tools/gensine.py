#!/usr/bin/env python

from math import sin, pow, pi

tablebits = 6
tableres = 8
tablesize = int(pow(2,6))

h = open("sinetable.h", "w")
c = open("sinetable.c", "w")

h.write("""
#ifndef __sinetable_h_
#define __sinetable_h_

#include <avr/pgmspace.h>
#include <stdint.h>

#define SINETABLE_SIZE %d
#define SINETABLE_BITS %d
#define SINETABLE_RES %d
#define SINETABLE_MASK %d

extern const PROGMEM uint%d_t sinetable[%d];

#endif // __sinetable_h_

""" % (tablesize, tablebits, tableres, tablesize-1, tableres, tablesize))
h.close()

c.write("""
#include "sinetable.h"

const PROGMEM uint%d_t sinetable[%d] = {
""" % (tableres, tablesize))

maxval = int(pow(2, tableres) - 1)
mean = int((maxval + 1) / 2)

for i in xrange(tablesize):
    t = 2 * pi * (float(i)/float(tablesize))
    a = sin(t) * (mean-1) + mean
    if i < tablesize-1:
        c.write("    %d,\n" % int(a))
    else:
        c.write("    %d\n" % int(a))

c.write("};\n\n")
c.close()



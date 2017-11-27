#!/usr/bin/env python

import sys
from math import exp

length = 256

def output_table(table_name, table):
    print "const prog_uint8_t env_table_%s[%d] = {" % (table_name, length)
    print "   ",
    for i in range(length):
        sep = ""
        if i<len(table)-1:
            sep = "," 
        print ("% 4d%s" % (table[i], sep)),
        if i % 8 == 7:
            print "\n   ",
    print "};\n"

def make_adsr(params):
    a = int(params['attack'] * length)
    d = int(params['decay'] * length)
    s = int(params['sustain'] * length)
    r = int(params['release'] * length)

    level = params['sustain_level']

    table = []

    for x in range(a):
        val = int(float(x+1)/a * 255)
        table.append(val)

    for x in range(d):
        val = int(((-1.0 * (1.0 - level) / float(d)) * (float(x+1)) * 255) + 255)
        table.append(val)

    for x in range(s):
        val = int(level * 255)
        table.append(val)

    for x in range(r):
        val = int(((-1.0 * (level) / float(r)) * (float(x+1)) * 255) + (level * 255))
        table.append(val)

    while len(table) < length:
        table.append(0)

    output_table(params['name'], table)

def make_ar(params):
    a = int(params['attack'] * length)
    r = int(params['release'] * length)

    level = 1.0

    table = []

    for x in range(a):
        val = int(float(x+1)/a * 255)
        table.append(val)

    for x in range(r):
        val = int(((-1.0 * (level) / float(r)) * (float(x+1)) * 255) + (level * 255))
        table.append(val)

    while len(table) < length:
        table.append(0)

    output_table(params['name'], table)


def make_exp(params):
    table = []
    a = params['attack']
    for i in range(a):
        table.append ( int( float(i)/a * 255))
    for i in range(256-params['attack']):
        table.append( int(exp(-1.0*params['p1']*float(i)/256) * 255) )
    output_table(params['name'], table)


envelopes = [
    {
        "generator": make_adsr,
        "name": "adsr1",
        "attack": 0.1,
        "decay": 0.2,
        "sustain": 0.4,
        "release": 0.3,
        "sustain_level": 0.4,
        "speed": 32,
        "hold": int(256 * 0.7),
    },
    {
        "generator": make_exp,
        "name": "exp1",
        "attack": 6,
        "p1": 4.0,
        "speed": 32,
        "hold": 255,
    },
    {
        "generator": make_ar,
        "name": "ar1",
        "attack": 0.3,
        "release": 0.7,
        "speed": 32,
        "hold": 200,
    },
]

print """
#include <stdint.h>

#include "envelope.h"

"""

for envelope in envelopes:
    envelope['generator'](envelope)

    print "const envelope_t env_%s = {" % envelope['name']
    print "    .table = env_table_%s," % envelope['name']
    print "    .increment = %d," % envelope['speed']
    print "    .hold = %d" % envelope['hold']
    print "};\n"

print "const envelope_t const *envelopes[%d] = {" % len(envelopes)
for i in range(len(envelopes)):
    sep=""
    if i < len(envelopes) - 1:
        sep=","
    print "    &env_%s%s" % (envelopes[i]['name'], sep)
print "};\n"


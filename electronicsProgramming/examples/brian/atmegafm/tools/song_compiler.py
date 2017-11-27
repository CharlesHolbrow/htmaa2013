#!/usr/bin/env python

from struct import pack
import sys

if len(sys.argv) < 3:
    print "usage: %s <input.song> <output.bin>" % sys.argv[0]
    sys.exit(1)

infile = open(sys.argv[1], "r")
outfile = open(sys.argv[2], "wb")

nchannels = 4

print "Compiling %s to binary sequencer format..." % sys.argv[1]

def str_to_midi(note):
    if len(note) < 2:
        return 0
    midi = 0
    if   note[0] == "C": midi = 0
    elif note[0] == "D": midi = 2
    elif note[0] == "E": midi = 4
    elif note[0] == "F": midi = 5
    elif note[0] == "G": midi = 7
    elif note[0] == "A": midi = 9
    elif note[0] == "B": midi = 11

    pos = 1
    if note[pos] == "#": 
        midi += 1
        pos += 1
    elif note[pos] == "b":
        midi -= 1
        pos += 1

    octave = int(note[pos])
    midi += 24
    midi += (octave - 1 ) * 12
    return midi

def parse_command(line):
    global nchannels
    line = line[1:].strip().split()
    if len(line) < 1:
        return
    if line[0] == "channels":
        nchannels = int(line[1])
        print "set channels: %d" % nchannels
        outfile.write(chr(0x90 | nchannels))
    elif line[0] == "instrument":
        chan = int(line[1])
        instr = int(line[2])
        print "set instrument for channel %d: %d" % (chan, instr)
        outfile.write(chr(0xA0 | chan) + chr(instr))
    elif line[0] == "volume":
        chan = int(line[1])
        vol = int(line[2])
        print "set volume for channel %d: %d" % (chan, vol)
        outfile.write(chr(0xB0 | chan) + chr(vol))
    elif line[0] == "speed":
        speed = int(line[1])
        print "set sequencer speed: %d" % speed
        outfile.write(chr(0xC0) + chr(speed))

for line in infile:
    if len(line) > 0 and line[0] == '*':
        parse_command(line)
    else:
        channels = line.replace('\n', '').split("\t")
        div = [0] * nchannels

        for i in range(nchannels):
            if len(channels) > i:
                if channels[i] == 'OFF':
                    div[i] = 1
                else:
                    div[i] = str_to_midi(channels[i])
        if sum(div) == 0:
            outfile.write(chr(0x80))
        else:
            outfile.write(apply(pack, ["B" * len(div)] + div))

outfile.write(chr(255))

infile.close()
outfile.close()


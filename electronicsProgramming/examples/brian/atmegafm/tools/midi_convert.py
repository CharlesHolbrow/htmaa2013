import midi
import sys

if len(sys.argv) < 3:
    print "bad usage"
    sys.exit(1)

divs_per_beat = 4
ticks_per_div=1

def midi_to_str(note):
    if note < 24: return ""
    octave = 2
    note -= 24
    name = ""
    while note >= 12:
        note -= 12
        octave += 1
    if   note == 0: name = "C"
    elif note == 1: name = "C#"
    elif note == 2: name = "D"
    elif note == 3: name = "D#"
    elif note == 4: name = "E"
    elif note == 5: name = "F"
    elif note == 6: name = "F#"
    elif note == 7: name = "G"
    elif note == 8: name = "G#"
    elif note == 9: name = "A"
    elif note == 10: name = "A#"
    elif note == 11: name = "B"
    else: print "aah, wtf %d" % note

    return "%s%d" % (name, octave)

notelist = []
def register_note(t, c, p, v, t1, t2):
    notelist.append((t, c, midi_to_str(p), t1, t2))
midi.register_note = register_note

mf = midi.MidiFile()
mf.open(sys.argv[1])
mf.read()
mf.close()

ticks_per_div = mf.ticksPerQuarterNote/divs_per_beat
print "divs per quarter note: %d" % divs_per_beat
print "ticks per div: %d" % ticks_per_div

max_div = 0
active_channels = []
for t, c, p, t1, t2 in notelist:
    if active_channels.count(c) < 1:
        active_channels.append(c)
    t = t2 / ticks_per_div
    if t > max_div:
        max_div = t

active_channels.sort()

print "number of divs: %d" % max_div
print "active channels: ", active_channels

outfile = open(sys.argv[2], "w")

selected_channels = [2, 3, 4, 6]
datacycle_channels = [1, 1, 2, 1]
cdatas = []

for cg in range(len(selected_channels)):
    ci = selected_channels[cg]
    datacycle = datacycle_channels[cg]
    d = 0
    cdata = []

    for i in range(datacycle):
        de = [""] * (max_div + 1)
        cdata.append(de)

    for t, c, p, t1, t2 in notelist:
        if c != ci: continue
        start_div = t1/ticks_per_div
        end_div = t2/ticks_per_div
        if end_div == start_div:
            end_div = start_div+1
        #print(p, start_div, end_div)

        data = cdata[d]

        if data[start_div] != "" and data[start_div] != "OFF":
            print "Warning: smashing %s on track %d at div %d with %s" % (
                    data[start_div], c, start_div, p)
        data[start_div] = p

        for i in range(start_div+1, end_div):
            if data[i] != "" and data[i] != "OFF":
                print "Warning: smashing %s on track %d at div %d with ." % (
                        data[i], c, i)
            data[i] = "."

        if data[end_div] != "" and data[end_div] != "OFF":
            print "Warning: smashing %s on track %d at div %d with OFF" % (
                    data[start_div], c, start_div)
        data[end_div] = "OFF"

        d+= 1
        if d >= datacycle:
            d = 0
    cdatas.append(cdata)

outfile.write("*channels 5\n")
outfile.write("*speed 17\n")
outfile.write("*instrument 0 4\n")
outfile.write("*instrument 1 4\n")
outfile.write("*instrument 2 2\n")
outfile.write("*instrument 3 2\n")
outfile.write("*instrument 4 0\n")
outfile.write("*volume 0 40\n")
outfile.write("*volume 1 40\n")
outfile.write("*volume 2 100\n")
outfile.write("*volume 3 100\n")
outfile.write("*volume 4 110\n")


#outfile.write("*volume 0 0\n")
#outfile.write("*volume 1 0\n")
#outfile.write("*volume 2 0\n")
#outfile.write("*volume 3 0\n")
#outfile.write("*volume 4 0\n")

for cdata in cdatas:
    for j in range(len(cdata)):
        outfile.write("OFF\t")
outfile.write("\n")

for i in range(max_div):
    for cdata in cdatas:
        for j in range(len(cdata)):
            outfile.write(cdata[j][i] + "\t")
    outfile.write("\n")

outfile.close()
    

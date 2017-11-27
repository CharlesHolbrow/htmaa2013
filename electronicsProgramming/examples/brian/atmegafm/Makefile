CC = avr-gcc
OBJCOPY = avr-objcopy

OBJECTS = main.o sinetable.o audio.o mixer.o pitch.o envelope.o sequencer.o led.o song.o \
		  button.o instrument.o uart.o
GENERATED_SOURCES = sinetable.c sinetable.h envelope.c song.c song.h
SONGS = unstolen.bin yume_no_kishibe_ni.bin
APPLICATION = avrfm
MCU = atmega168
F_CPU = 20000000UL

CFLAGS=-mmcu=$(MCU) -Wall -DF_CPU=$(F_CPU) -I. -funsigned-char -funsigned-bitfields \
	   -fpack-struct -fshort-enums -Os
LDFLAGS=-mmcu=$(MCU)

all: $(GENERATED_SOURCES) $(APPLICATION).hex

clean:
	rm -f $(GENERATED_SOURCES) *.hex *.elf *.o *.bin tools/*.pyc

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

$(APPLICATION).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^
	avr-size -C --mcu=$(MCU) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	avrdude -p m168 -B 10 -c jtag2isp -P usb -e -U flash:w:$(APPLICATION).hex

%.bin: %.song
	python tools/song_compiler.py $< $@

song.c: $(SONGS)
	python tools/make_song.py c $^

song.h: $(SONGS)
	python tools/make_song.py h $^

sinetable.c: tools/gensine.py
	python tools/gensine.py c

sinetable.h: tools/gensine.py
	python tools/gensine.py h

envelope.c: tools/genenv.py
	python tools/genenv.py > envelope.c

.PHONY: all clean


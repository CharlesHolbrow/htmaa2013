# Networking

Why?

1. 1 thread per processor. Parallelism.
2. modularity.
3. Interference - separate high power electronics, from high frequency devices

# Serial

we have used RS-232 for host communication. Tx and RX for serial communication.

RS-422 and RS-485 are more complex for industrial use, AC for longer tie lines. 

On our Fab boards: The host always talks out on the TX line.


# I²C (i squared c) (aka USI, aka TWI)

i2c is a Communications protocol.

commonly used for chip to chip communication. 

two wires - clock wire, data wire both held 'high' with pullups 

Master sends a clock.

there is a master and multiple slaves hanging off the wire.

While the clock line is high, the master brings the data line low( I'm starting a message)...

- scl sda pins: the attiny has hardware that can be used to speak i2c


# SPI - Serial Peripheral Interface

SPI is another Communication Protocol, very similar to i2c (I.e. Master device sends a Clock signal)



# ISP

In System Programming. Don't confuse ISP the the SPI communication protocol.

This is a means of Programing a chip while the chip is in the board.

This uses the SPI communication Protocol to program the chip.


# USB

started as a wrapper for serial. now it's much more.

atmega has hardware usb built in. 

atmel has a library for usb support

# LUFA

(Software) this independent Library implements many common class compliant usb packages. 

Who's who?
Transport how you manage a session

IP routes 

udp and tcp manage traffic 

udp ports are like mailboxes in a building


# wireshark 

great tool for network debugging


# slip 

ip over serial

slattach is the unix command that can turn serial into an Internet connection

# Radio

ISM is a slightly less overused band. 

# Opto Isolator

Optically isolate a voltage with an led and photo resistor. 

This could be useful for midi for sending optical midi data. 

# Neil's Serial Example

Each pin on the attiny is a tri-state pin (aka z-state). 

1. Hi  (output mode via DDR)
2. Low (output mode via DDR)
3. floating (input mode via DDR)

In floating mode a pull-up resistor can be enabled or disabled

When a pin is configured as an input is is not connected to the hi or the low.

## How Neil's Serial Example works

The master transmit is connected to the receive of ALL the slaves. 
The slaves transmit pins are ALL connected to the 

By default all the transmit pins are floating. [CA: pull resistor should be on]

The master sends a message to the telling which chip may speak. That chip enables toggles it's transmit pin to output mode, and sends info back to the master.




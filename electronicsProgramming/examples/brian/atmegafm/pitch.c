#include "pitch.h"

uint16_t note_to_increment(uint8_t note) {
    switch(note) {
        case 36: return FREQ_TO_INCREMENT(65.406);
        case 37: return FREQ_TO_INCREMENT(69.296);
        case 38: return FREQ_TO_INCREMENT(73.416);
        case 39: return FREQ_TO_INCREMENT(77.782);
        case 40: return FREQ_TO_INCREMENT(82.406);
        case 41: return FREQ_TO_INCREMENT(87.307);
        case 42: return FREQ_TO_INCREMENT(92.499);
        case 43: return FREQ_TO_INCREMENT(97.999);
        case 44: return FREQ_TO_INCREMENT(103.826);
        case 45: return FREQ_TO_INCREMENT(110.000);
        case 46: return FREQ_TO_INCREMENT(116.541);
        case 47: return FREQ_TO_INCREMENT(123.470);

        case 48: return FREQ_TO_INCREMENT(130.813);
        case 49: return FREQ_TO_INCREMENT(138.591);
        case 50: return FREQ_TO_INCREMENT(146.832);
        case 51: return FREQ_TO_INCREMENT(155.563);
        case 52: return FREQ_TO_INCREMENT(164.814);
        case 53: return FREQ_TO_INCREMENT(174.614);
        case 54: return FREQ_TO_INCREMENT(184.997);
        case 55: return FREQ_TO_INCREMENT(195.998);
        case 56: return FREQ_TO_INCREMENT(207.652);
        case 57: return FREQ_TO_INCREMENT(220.000);
        case 58: return FREQ_TO_INCREMENT(233.082);
        case 59: return FREQ_TO_INCREMENT(246.942);

        case 60: return FREQ_TO_INCREMENT(261.626);
        case 61: return FREQ_TO_INCREMENT(277.183);
        case 62: return FREQ_TO_INCREMENT(293.665);
        case 63: return FREQ_TO_INCREMENT(311.127);
        case 64: return FREQ_TO_INCREMENT(329.628);
        case 65: return FREQ_TO_INCREMENT(349.228);
        case 66: return FREQ_TO_INCREMENT(369.994);
        case 67: return FREQ_TO_INCREMENT(391.995);
        case 68: return FREQ_TO_INCREMENT(415.305);
        case 69: return FREQ_TO_INCREMENT(440.000);
        case 70: return FREQ_TO_INCREMENT(466.164);
        case 71: return FREQ_TO_INCREMENT(493.883);

        case 72: return FREQ_TO_INCREMENT(523.251);
        case 73: return FREQ_TO_INCREMENT(554.365);
        case 74: return FREQ_TO_INCREMENT(587.329);
        case 75: return FREQ_TO_INCREMENT(622.254);
        case 76: return FREQ_TO_INCREMENT(659.255);
        case 77: return FREQ_TO_INCREMENT(698.456);
        case 78: return FREQ_TO_INCREMENT(739.989);
        case 79: return FREQ_TO_INCREMENT(783.991);
        case 80: return FREQ_TO_INCREMENT(830.609);
        case 81: return FREQ_TO_INCREMENT(880.000);
        case 82: return FREQ_TO_INCREMENT(932.327);
        case 83: return FREQ_TO_INCREMENT(987.767);

        case 84: return FREQ_TO_INCREMENT(1046.502);
        case 85: return FREQ_TO_INCREMENT(1108.735);
        case 86: return FREQ_TO_INCREMENT(1174.659);
        case 87: return FREQ_TO_INCREMENT(1244.508);
        case 88: return FREQ_TO_INCREMENT(1318.510);
        case 89: return FREQ_TO_INCREMENT(1396.913);
        case 90: return FREQ_TO_INCREMENT(1479.978);
        case 91: return FREQ_TO_INCREMENT(1567.982);
        case 92: return FREQ_TO_INCREMENT(1661.219);
        case 93: return FREQ_TO_INCREMENT(1760.000);
        case 94: return FREQ_TO_INCREMENT(1864.655);
        case 95: return FREQ_TO_INCREMENT(1975.533);
    }

    return 0;
}


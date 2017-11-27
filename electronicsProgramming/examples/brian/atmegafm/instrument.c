#include "instrument.h"

/* Instrument sounds are defined here.  These are basically the synthesizer
 * parameters, which can be tweaked for the desired timbre.  They are defined
 * as follows:
 *
 * envelope_index: the index of the amplitude envelope to be applied to the
 *  sound.
 *
 * env_increment: controls how quickly the envelope table is played.  The 
 *  units are how far to increment through the table for each sample, with
 *  7 fractional bits.
 *
 * modulation_index: controls how heavily the carrier is modulated.  The
 *  values are inputs to a right shift, so larger values result in less
 *  modulation.
 *
 * mod_ratio_numerator/mod_ratio_denominator: the FM ratio.
 */

static const instrument_t instrument_flute = {
    .envelope_index = 0,
    .env_increment = 16,
    .modulation_index = 8,
    .mod_ratio_numerator = 0,
    .mod_ratio_denominator = 1,
    .attenuation = 0
};

static const instrument_t instrument_music_box = {
    .envelope_index = 1,
    .env_increment = 16,
    .modulation_index = 4,
    .mod_ratio_numerator = 36,
    .mod_ratio_denominator = 5,
    .attenuation = 2
};

static const instrument_t instrument_marimba = {
    .envelope_index = 1,
    .env_increment = 16,
    .modulation_index = 4,
    .mod_ratio_numerator = 36,
    .mod_ratio_denominator = 21,
    .attenuation = 2
};

static const instrument_t instrument_synthbeep = {
    .envelope_index = 1,
    .env_increment = 16,
    .modulation_index = 4,
    .mod_ratio_numerator = 36,
    .mod_ratio_denominator = 18,
    .attenuation = 2
};

static const instrument_t instrument_ahh = {
    .envelope_index = 2,
    .env_increment = 8,
    .modulation_index = 6,
    .mod_ratio_numerator = 8,
    .mod_ratio_denominator = 3,
    .attenuation = 2
};

static const instrument_t instrument_piano = {
    .envelope_index = 0,
    .env_increment = 32,
    .modulation_index = 3,
    .mod_ratio_numerator = 16,
    .mod_ratio_denominator = 1,
    .attenuation = 0
};

const instrument_t const *instruments[] = {
    &instrument_flute,
    &instrument_music_box,
    &instrument_marimba,
    &instrument_synthbeep,
    &instrument_ahh,
    &instrument_piano
};


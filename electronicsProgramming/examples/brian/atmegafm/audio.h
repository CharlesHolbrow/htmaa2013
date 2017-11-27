#ifndef __audio_h_
#define __audio_h_

// Macro to output a sample value to the speaker
//#define audio_output(x) OCR1AL = x

// Initialize the low-level audio subsystem.
void audio_init(void);
void audio_output(uint8_t sample);


#endif // __audio_h_


#ifndef MIDIcontroller_h
#define MIDIcontroller_h

#include "Arduino.h"
#include "MIDIbutton.h"
#include "MIDIpot.h"
#include "MIDIenc.h"
#include "MIDIcapSens.h"
#include "MIDIdrum.h"
#include "MIDI.h"
#include "usb_desc.h"
#include "usb_dev.h"
#include "usb_midi.h"
#include "core_pins.h"
#include "HardwareSerial.h"

#if defined(TEENSYDUINO) && defined(__AVR__)
#define PROCESSOR_TEENSY_2_0	1
#elif defined(__MK20DX128__)
#define PROCESSOR_TEENSY_3_0	1
#elif defined(__MK20DX256__)
#define PROCESSOR_TEENSY_3_1	1
#define PROCESSOR_TEENSY_3_2	1
#elif defined(__MKL26Z64__)
#define PROCESSOR_TEENSY_LC	1
#elif defined(__MK64FX512__)
#define PROCESSOR_TEENSY_3_5	1
#elif defined(__MK66FX1M0__)
#define PROCESSOR_TEENSY_3_6	1
#else
#error "This Library is not tested on your processor! (It might work...)"
#endif

#define MIDI_PC_USB   0
#define MIDI_SERIAL   1
#define MIDI_HOST     2
#define MIDI_DEBUG    3

extern void MIDI_setup(void);
extern void MIDI_send(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable, byte interface);
extern void MIDI_loop(void);

#endif

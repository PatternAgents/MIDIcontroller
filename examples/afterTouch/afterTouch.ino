#include "MIDIcontroller.h"

const int FSRpin = 23;  // Change this to the ANALOG pin you want to use.

MIDIdrum myPad(FSRpin, 40);
MIDIpot aftertouch(FSRpin, 77);

void setup(){
   MIDI_setup();
}

void loop(){
  MIDI_loop();
  myPad.send();
  aftertouch.send();
}

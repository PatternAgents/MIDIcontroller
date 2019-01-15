#include "MIDIcontroller.h"

const int potPin = A14;  // Change this to the ANALOG pin you want to use i.e. A0

// Pot parameters are: pin, CC number, KILL switch enabled
// When KILL is enabled, separate CC messages (with a different number) will be sent
// when you turn the pot all the way down and when you start turning it up again.
// Simply omit the "KILL" argument if you don't want that.
MIDIpot myPot(potPin, 22);

// OPTIONAL: use outputRange() to limit the min/max MIDI output values
myPot.outputRange(60, 88);

void setup(){
  MIDI_setup();
}

void loop(){
  MIDI_loop();
  myPot.send();
}

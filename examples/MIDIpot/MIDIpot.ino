#include "MIDIpot.h"
#include "MIDIcontroller.h"

const int potPin = A14;  // Change this to the ANALOG pin you want to use i.e. A0
byte loRange = 60;
byte hiRange = 88;

// Pot parameters are: pin, CC number, KILL switch enabled
// When KILL is enabled, separate CC messages (with a different number) will be sent
// when you turn the pot all the way down and when you start turning it up again.
// Simply omit the "KILL" argument if you don't want that.
MIDIpot myPot(potPin, 22);

void setup(){
  MIDI_setup();
  // OPTIONAL: use outputRange() to limit the min/max MIDI output values
  myPot.outputRange(loRange,hiRange);
}

void loop(){
  MIDI_loop();
  myPot.send();
}

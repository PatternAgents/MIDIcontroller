#include "MIDIcontroller.h"

const int encPinA = 20;   // Change these numbers to
const int encPinB = 21;   // the two pins your encoder is on.
const int buttonPin = 19; // Many encoders feature a push switch.
const int ledPin = 13;    // Set an LED to show the state of the switch.

// Encoder parameters are: pin A, pin B, CC number
MIDIenc myEnc(encPinA, encPinB, 24);
MIDIbutton myButton(buttonPin, 25, LATCH); // CC #25 in latch mode

void setup(){
  pinMode(ledPin, OUTPUT);
  MIDI_setup();
}

void loop(){
  MIDI_loop();
  myEnc.send();
  myButton.send();
  digitalWrite(ledPin, myButton.state);
}

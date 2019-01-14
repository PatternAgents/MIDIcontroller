#include "MIDIcontroller.h"
/* MIDIButton example :
   Defaults :
   Message      : Control Change
   MIDI Output  : USB, Cable 0
   MIDI Channel : 10 (Drum)

*/
const int leftPin = 4;        // any digital pin
const int rightPin = 5;       // any digital pin
const int ledPin = 13;        // Set an LED to show the state of a latch button.

// MOMENTARY buttons are the default. LATCH or TRIGGER may also be set
MIDIbutton leftButton(leftPin,   21, LATCH);     // default to Control Change #21, USB, Cable 0, Channel 10
MIDIbutton rightButton(rightPin, 15, MOMENTARY); // default to Control Change #15, USB, Cable 0, Channel 10

void setup(){
  pinMode(ledPin, OUTPUT);
  MIDI_setup();
  rightButton.setChannel(1,0,0);           // change to channel 1
  leftButton.setChannel(1,0,0);            // change to channel 1
  leftButton.setOnMessage(0x90, 60, 127);  // change message to NoteOn, Key = 60, Velocity = fortissimo
  leftButton.setOffMessage(0x80, 60, 0);   // change message to NoteOff, Key = 60, Velocity = none
}
void loop(){
  MIDI_loop();
  digitalWrite(ledPin, leftButton.state);
  leftButton.send();
  rightButton.send();
}

/* MIDISerial test example :

tests the raw send functions to MIDI serial

*/
#include "MIDIcontroller.h"

const int Pin1 = 2;       // any digital pin
const int ledPin = 13;    // Set an LED to show the state of a latch button.

// MOMENTARY buttons are the default. LATCH or TRIGGER may also be set
MIDIbutton Button1(Pin1, 11, LATCH);     // default to Control Change #11, USB, Cable 0, Channel 10

void setup(){
  pinMode(ledPin, OUTPUT);
  MIDI_setup();
  Button1.setChannel(1,0,MIDI_SERIAL); // change to channel 1, Cable 0, MIDI_PC_USB
  Button1.setOnMessage(0x90, 60, 127); // change message to NoteOn, Key = 60, Velocity = fortissimo
  Button1.setOffMessage(0x80, 60, 0);  // change message to NoteOff, Key = 60, Velocity = none
}
void loop(){
  MIDI_loop();
  digitalWrite(ledPin, Button1.state);
  Button1.send();
 
  // play notes as a test
  MIDI_send(0x90, 66, 127, 1, NULL, 0, MIDI_SERIAL);
  delay (200);
  MIDI_send(0x80, 66, 0, 1, NULL, 0, MIDI_SERIAL);
  delay(200);
}

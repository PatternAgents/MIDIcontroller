#include "MIDIcontroller.h"
byte MIDIchannel = 10;
const int latchPin = 5; //any digital pin
const int triggerPin = 3; //any Capacitive Touch capable pin
const int ledPin = 13;   //Set an LED to show the state of a latch button.

// MOMENTARY buttons are the default. LATCH or TRIGGER may also be set
MIDIbutton latchButton(latchPin, 21, LATCH);       // Control Change #21
MIDIbutton triggerButton(triggerPin, 15, TRIGGER); // Control Change #15

void setup(){
  pinMode(ledPin, OUTPUT);
}
void loop(){
  latchButton.send();
  digitalWrite(ledPin, latchButton.state);
}

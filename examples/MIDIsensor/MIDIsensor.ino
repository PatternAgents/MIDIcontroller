#include "MIDIcontroller.h"

/*This is an example of how to use
  potentiometers and analog sensors.
  The use of a photocell will be
  demonstrated. I'ts wired like so:
 
  3.3v--(PHOTO CELL)---\
                        )---Analog Pin
  GND-------/\/\/------/
             10k
*/

const int sensPin = A9; // Change this to the ANALOG pin you want to use.

// parameters are: pin, CC number
MIDIpot mySensor(sensPin, 23);

void setup(){
  MIDI_setup();
  // Use the rangeFinder example to find the usable range of your sensor
  // and call inputRange() with the lowest and highest values.
  mySensor.inputRange(350, 950);
}

void loop(){
  MIDI_loop();
  mySensor.send();
}

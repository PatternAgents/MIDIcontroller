// midi_test - play a scale on MIDI OUT/Channel#1, and
//             print any incoming MIDI message on the serial monitor window
// 
// THIS SKETCH WILL NOT START UNTIL YOU OPEN THE SERIAL MONITOR WINDOW!
// THIS IS DONE TO AVOID MISSING ANY MESSAGES ON STARTUP...
//
// You can start the upload with the monitor window already open...
//

#define NOTEMIN 40
#define NOTEMAX 88

#include <MIDI.h>

// Change "Serial1" to your MIDI port if different (i.e. Serial4)
//
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);

void setup() {
    Serial.begin(115200);            // start USB (Serial Monitor)  
    while (!Serial) { }              // wait for PC to connect - comment this line to start automagically 
    MIDI1.begin(MIDI_CHANNEL_OMNI);  // start Serial MIDI
}


int delaytime = 250; // 250 milliSeconds
int delaycount = 0;  // we'll make "loop" be timed to approximately 1milliSecond per iteration 
int note = NOTEMIN;       // current note value
int note_state = 0;  // start with noteOff

void loop() {
     // check incoming MIDI every millisecond
     if (MIDI1.read()) {
      Serial.print("type:");
      Serial.print(MIDI1.getType(), HEX);
      Serial.print("  d1:");
      Serial.print(MIDI1.getData1(), HEX);
      Serial.print("  d2:");
      Serial.print(MIDI1.getData2(), HEX);
      Serial.println("");
    } 

    // now, delay for noteOn/NoteOff time
    // before changing the note_state
    if (delaycount++ >= delaytime){
      // timed out - change the note state
      delaycount = 0;
      // is a note playing?
      if (note_state == 0) {
        // no, play a note
        note_state = 1; 
        MIDI1.sendNoteOn(note, 127, 1);    // Send a Note (pitch , velo 127, channel 1)

      } else {
        // we were playing for delaytime - now send a note off
        note_state = 0;
        MIDI1.sendNoteOff(note, 0, 1);     // Stop the note
        note++;
        // clip the scale of notes
        if (note > NOTEMAX) note = NOTEMIN;       
      }
    } else {
      delay(1); // delay for one millisecond (approximately...)
    }
}

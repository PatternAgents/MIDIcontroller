# MIDIcontroller

A library for creating Teensy MIDI controllers

## LATEST FEATURES INCLUDE
  - Support for usbMIDI, usbMIDIx4, usbMIDIx16 (16 Cable Support)
  - Support for Serial MIDI (1 Cable on Serial1 by default)
  - per-instance selection of MIDI message, channel, cable and interface
  - Velocity sensitive FSR or Piezo inputs
  - momentary, latch or 'trigger' buttons
  - Stable analog to MIDI conversion for potentiometers and other sensors
  - Support for encoders and capacitive touch sensors
  - Min/Max output can be set (or inverted). 
    Min/Max input can also be set for analog input 
    (maintaining stability in conversion)

## TODO/UPDATE/NEW FEATURES PLANNED
  - rewrite to use hardware interrupts and timers (not polled)
  - Support for usbHOST MIDI on Teensy3.6 with an external USB Hub
  - add support for serial debug messages as an interface
  - replace KILL with a second user-selectable CC number
  - add an option to allow encoders to change 1 MIDI value per detent
  - MIDIdrum timer and waitTime  to use hardware interrupts and timers 
  - get velocity from Capacitive Touch by measuring the rate of change

## VERSION LOG
-  3.0.1 : Add Serial Debug support as Interface #3
-        : Fix Serial MIDI1.begin() omitted bug
-  3.0.0 : Add usbMIDI cable support for MIDI, MIDIx4, and MIDIx16 USB types
-        : Add Serial MIDI support on Serial1 as default
-	 : Add per-instance selection of MIDI channel, cable, and interface
-	 : Add usbMIDI.read(); in MIDI_loop to fix the eventual MIDI crash due to 
-	 : http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
-        : global "MIDIchannel" is obsolete and no longer used
-        : defaults are now CC Message, Channel 10, Cable 0 , USB device Interface
-        : use the .SetChannel() and .setOnMessage/.setOffMessage API's to change the defaults
-
-  2.2.5 : Bugfixed jitter that occurred when using inputRange() with input maxed
-        : Arguments for specific velocities can now be passed to velocity inputs
-        : Added literals to highlight MOMENTARY, LATCH, TRIGGER and KILL modes
-        : Long overdue completion of the "Flicker" library (for Cap Touch input)
-        : Made separate examples for 'pot' and 'sensor' (to avoid confusion)
-        
-  2.2.0 : Added support for Piezos (Must be wired properly. See example)
-        : "MIDInote" class changed to "MIDIdrum" and optimized for FSR and Piezo
-        : Removed redundant 'velocity' variable. Just call outputRange(127, 127)
-        : Added support for using a Capacitive Touch input as a MIDIbutton
-        : Included 'Flicker' library (required for Capacitive Touch buttons)
-  2.1.5 : got rid of useless '*MC' pointer. renamed 'kill' to 'mode'
-  2.1.3 : included an example of how to implement aftertouch
-  2.1.2 : many variables changed to 'byte' or 'uint16_t' for easy storage
-        : public and private variables are better sorted
-  2.1.0 : Split read() and send() functions. MIDI channel is now user selectable
-  2.0.6 : Fixed a bug preventing poly CC to return to zero after note off.
-  2.0.5 : Added a condition to prevent many double note triggers.
-  2.0.4 : Added support for capacitive sensors (and started this version log)

  
## REQUIREMENTS

MIDIcontroller requires the following libraries to be installed :

- MIDI
- BOUNCE
- ENCODER


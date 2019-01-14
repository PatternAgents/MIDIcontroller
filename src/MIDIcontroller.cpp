#include "MIDIcontroller.h"


MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);

void MIDI_send(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable, uint8_t interface) {

  // process outgoing messages
  switch (interface)
  {
  case 0 :
	// usbMIDI usbMIDIx4 usbMIDIx16
  	if (type != midi::SystemExclusive) {
		usbMIDI.send(type, data1, data2, channel, cable);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		usbMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
	}
  case 1 :
	// serial MIDI
  	if (type != midi::SystemExclusive) {
	    // Normal messages, first we must convert usbMIDI's type (an ordinary
        // byte) to the MIDI library's special MidiType.
        midi::MidiType mtype = (midi::MidiType)type;
		MIDI1.send(mtype, data1, data2, channel);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		MIDI1.sendSysEx(SysExLength, sysexarray, true);
	}
	  break;
  case 2 :
      // USBhost MIDI
  	if (type != midi::SystemExclusive) {
		//hostMIDI.send(type, data1, data2, channel, cable);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		//hostMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
	}
      break;
  default :
	  break;
  
  }
}

void MIDI_loop(void){
	// MIDI Controllers should discard incoming MIDI messages.
    // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
    while (usbMIDI.read()) { }   
    while (MIDI1.read()) { }
	// Note : if you wanted to do any forwarding of incoming MIDI messages, add that here...
}

void MIDI_setup(void){
}
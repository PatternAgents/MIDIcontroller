#include "MIDIcontroller.h"

#if !defined(MIDISERIALNONE)
  MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
#endif

void MIDI_send(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable, uint8_t interface) {

  // process outgoing messages
  switch (interface)
  {
  case MIDI_PC_USB :
	// assume usbMIDI is available...
    if (cable >= MIDI_NUM_CABLES) return;
  	if (type != midi::SystemExclusive) {
		usbMIDI.send(type, data1, data2, channel, cable);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		usbMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
	}
	break;
  case MIDI_SERIAL :
	#if !defined(MIDISERIALNONE)
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
    #endif
	break;
  case MIDI_HOST :
	#ifdef PROCESSOR_TEENSY_3_6
    // USBhost MIDI 
  	if (type != midi::SystemExclusive) {
		//hostMIDI.send(type, data1, data2, channel, cable);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		//hostMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
	}
	#endif
    break;
  case MIDI_DEBUG : 
	  // assume Serial is available...
	  // Host USB Virtual Serial Port (Debug)
        Serial.print("MIDI Message type=");
		Serial.print(type, HEX);
		Serial.print(", Data1=");
		Serial.print(data1, HEX);
		Serial.print(", Data2=");
		Serial.print(data2, HEX);
		Serial.print(", Channel=");
		Serial.print(channel, HEX);
		Serial.print(", Cable=");
		Serial.print(cable, HEX);
		Serial.print(", I/F=");
		Serial.println(interface, HEX);
	  break;
  default :
	  break;
  }
}

void MIDI_loop(void){
	// MIDI Controllers should discard incoming MIDI messages.
    // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
    while (usbMIDI.read()) { }   
	#if !defined(MIDISERIALNONE)
      while (MIDI1.read()) { 
		// Note : if you wanted to do any forwarding of incoming MIDI messages, add that here...
	  }
	#endif
	
}

void MIDI_setup(void){
    
	Serial.begin(115200);
	#if !defined(MIDISERIALNONE)
	  MIDI1.begin(MIDI_CHANNEL_OMNI);
	  MIDI1.turnThruOff();				/* this was causing HAVOC/crash on Loopback (LOL) */
    #endif
}
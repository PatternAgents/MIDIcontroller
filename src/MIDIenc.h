#ifndef MIDIenc_h
#define MIDIenc_h

#include "Arduino.h"
#include "Bounce.h"
#include "Encoder.h"

class MIDIenc{
  public:
    // default constructor
    MIDIenc();
    
    // constructor when only pins and control number are given
    MIDIenc(int a, int b, byte num);
    
    // " when pins, control number, minimum and maximum outgoing MIDI values set
    MIDIenc(int a, int b, byte num, byte min, byte max);
    
    // destructor
    ~MIDIenc();

    int read(); // read input and return a MIDI value (or -1 if none)
    int send(); // calls read(), sends and returns a MIDI value (or -1 if none)
    void setControlNumber(byte num);
    void outputRange(byte min, byte max);
	void setChannel(byte channel, byte cable, byte face);
	void setOnMessage(byte OnMessage, byte num, byte velocity);
	void setOffMessage(byte OffMessage, byte num, byte velocity);
    Encoder *myKnob;
  private:
    byte number;
    byte value;
    byte outLo, outHi;
	byte _MIDIOnMessage = 0xB0;  // control change
	byte _MIDIOffMessage = 0xB0; // control change
	byte _MIDIOnVelocity = 127;
	byte _MIDIOffVelocity = 0;
	byte _MIDIchannel = 10;
    byte _MIDIcable = 0;
    byte _MIDIface = 0;
};

#endif
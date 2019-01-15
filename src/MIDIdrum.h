#ifndef MIDIdrum_h
#define MIDIdrum_h

#include "Arduino.h"

class MIDIdrum{
    int pin;
    int newValue;
    int peak;
    int state;  // 0 = idle, 1 = looking for peak, 2 = ignoring aftershock
    unsigned int waitTime;
    elapsedMillis timer;
    
  public:
    // default constructor
    MIDIdrum();
    
    // constructor when pin and note number are given
    MIDIdrum(int p, byte num);

    // destructor
   	~MIDIdrum();

    int read();
    int send();
    int send(int vel);
    void setNoteNumber(byte num);
    void outputRange(byte min, byte max);
    void setThreshold(int thresh);
	void setChannel(byte channel, byte cable, byte face);
	void setOnMessage(byte OnMessage, byte num, byte velocity);
	void setOffMessage(byte OffMessage, byte num, byte velocity);

private:
	byte number;
    byte outLo, outHi;
    int threshold;
	byte _MIDIOnMessage = 0x80;  // noteOn
	byte _MIDIOffMessage = 0x90; // noteOff
	byte _MIDIOnVelocity = 127;
	byte _MIDIOffVelocity = 0;
	byte _MIDIchannel = 10;
    byte _MIDIcable = 0;
    byte _MIDIface = 0;
};

#endif


#ifndef MIDIpot_h
#define MIDIpot_h

#include "Arduino.h"
#define KILL 1

class MIDIpot{
    int divider; // for converting from analog to MIDI resolution
    
  public:
    // default constructor
    MIDIpot();
    
    // constructor when only pin & control number are given
    MIDIpot(int p, byte num);
    
    // " when pin, control number are given and kill switch is enabled
    MIDIpot(int p, byte num, bool m);
    
    // " pin, control number, minimum & maximum outgoing MIDI values are set
    MIDIpot(int p, byte num, byte min, byte max);
    
    // " pin, control number, min/max values are given and kill switch is enabled
    MIDIpot(int p, byte num, bool m, byte min, byte max);
    
    // destructor
   	~MIDIpot();

    int read(); // read input and return a MIDI value (or -1 if none)
    int send(); // calls read(), sends and returns a MIDI value (or -1 if none)
    void setControlNumber(byte num);
    void inputRange(uint16_t min, uint16_t max);
    void outputRange(byte min, byte max);
	void setChannel(byte channel, byte cable, byte face);
	void setOnMessage(byte OnMessage, byte num, byte velocity);
	void setOffMessage(byte OffMessage, byte num, byte velocity);

  private:
    int pin;
    bool invert;
    byte value;
	byte number;
    uint16_t inLo, inHi;
    byte outLo = 0;
    byte outHi = 127;
    bool mode;  // in case you need to kill an effect entirely
	byte _MIDIOnMessage = 0xB0;  // control change
	byte _MIDIOffMessage = 0xB0; // control change
	byte _MIDIOnVelocity = 127;
	byte _MIDIOffVelocity = 0;
	byte _MIDIchannel = 10;
    byte _MIDIcable = 0;
    byte _MIDIface = 0;
};

#endif
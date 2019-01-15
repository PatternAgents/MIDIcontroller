#ifndef MIDIcapSens_h
#define MIDIcapSens_h

#include "Arduino.h"

class MIDIcapSens{
    int pin;
    bool waiting;
    unsigned int waitTime;
    unsigned long int timer;
    bool hovered;
    bool touched;
    
  public:
    MIDIcapSens();
    MIDIcapSens(int p, byte num);
    MIDIcapSens(int p, byte num, byte min, byte max);
   	~MIDIcapSens();

    int read(); // returns 2:risingEdge, 1:fallingEdge, 0:outOfRange, -1:none
    int send(); // calls read(), sends a MIDI value & returns the value
    void setNoteNumber(byte num);
    void outputRange(byte min, byte max);
    void setThresholds(int offT, int onT);
    void setThresholds(int offT, int onT, int upL);
	void setChannel(byte channel, byte cable, byte face);
	void setOnMessage(byte OnMessage, byte num, byte velocity);
	void setOffMessage(byte OffMessage, byte num, byte velocity);
  private:
    int value;
    int number;
    byte outLo, outHi;
    int upperLimit, onThreshold, offThreshold;
    bool afterRelease;
    bool state;
	byte _MIDIOnMessage = 0x80;  // NoteOn
	byte _MIDIOffMessage = 0x90; // NoteOff
	byte _MIDIOnVelocity = 127;
	byte _MIDIOffVelocity = 0;
	byte _MIDIchannel = 10;
    byte _MIDIcable = 0;
    byte _MIDIface = 0;
};

#endif


/*FIXME after the value bottoms out alternating MIDI messages (0 1 0 1 0...)
  will occasionally continue to be sent.
*/

#include "MIDIenc.h"
#include "MIDIcontroller.h"

// constructors
MIDIenc::MIDIenc(){};

MIDIenc::MIDIenc(int a, int b, byte num){
  myKnob = new Encoder(a, b);
	number = num;
  value = 0;
  outLo = 0;
  outHi = 127;
};

MIDIenc::MIDIenc(int a, int b, byte num, byte min, byte max){
  myKnob = new Encoder(a, b);
	number = num;
  value = 0;
  outLo = min;
  outHi = max;
};

// destructor
MIDIenc::~MIDIenc(){
  delete myKnob;
};


int MIDIenc::read(){
  int newValue = -1;
  int incdec = myKnob->read();
  if(incdec >= 1 && value < outHi){       // If turned up but not already maxed
    newValue = value + 1;
  }
  else if (incdec <= -1 && value > outLo){// If turned down but not bottomed out
    newValue = value - 1;
  }
  else{newValue = -1;}
  myKnob->write(0);
  return newValue;
};

int MIDIenc::send(){
  int newValue = read();
  if (newValue >= 0){
    //usbMIDI.sendControlChange(number, newValue, MIDIchannel);
	MIDI_send(_MIDIOnMessage, number, newValue, _MIDIchannel, NULL, _MIDIcable, _MIDIface);
    value = newValue;
  }
  return newValue;
}

// Set the CC number.
void MIDIenc::setControlNumber(byte num){
  number = num;
};

// Set upper and lower limits for outgoing MIDI messages.
void MIDIenc::outputRange(byte min, byte max){
  outLo = min;
  outHi = max;
};

// Set the button channel, cable, interface
void MIDIenc::setChannel(byte channel, byte cable, byte face){
   MIDIenc::_MIDIchannel = channel;
   MIDIenc::_MIDIcable   = cable;
   MIDIenc::_MIDIface    = face;
};

// Set the OnMessage
void MIDIenc::setOnMessage(byte OnMessage, byte num, byte velocity){
  MIDIenc::_MIDIOnMessage = OnMessage;  // default is control change
  MIDIenc::number = num;
  MIDIenc::_MIDIOnVelocity = velocity;

}

// Set the OffMessage
void MIDIenc::setOffMessage(byte OffMessage, byte num, byte velocity){
  MIDIenc::_MIDIOffMessage = OffMessage;  // default is control change
  MIDIenc::number = num;
  MIDIenc::_MIDIOffVelocity = velocity;
}

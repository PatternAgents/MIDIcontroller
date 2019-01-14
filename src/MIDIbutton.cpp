#include "MIDIbutton.h"
#include "MIDIcontroller.h"

// constructors
MIDIbutton::MIDIbutton() : Bounce(0, 0), Flicker(0, 0){};

MIDIbutton::MIDIbutton(int p, byte num, byte mod) : Bounce(p, 10), Flicker(0, 0){
  pinMode(p, INPUT_PULLUP);
  inputType = 0; //button
  number = num;
  mode = mod; 
  state = false;
};

MIDIbutton::MIDIbutton(int p, byte num, byte mod, int thresh) : Bounce(0, 0), Flicker(p, thresh){
  inputType = 1; //capacitive touch
  number = num;
  mode = mod; 
  state = false;
};

// destructor
MIDIbutton::~MIDIbutton(){};


int MIDIbutton::read(){
  int newValue = -1;
  if (inputType == 0){
    Bounce::update();              // Force a status report of the Bounce object.
    inputState = Bounce::state;
    if (Bounce::fallingEdge()){    // If the button's been pressed,
      newValue = outHi;            // return the high CC value.
    }
    else if (Bounce::risingEdge()){// If the button has been released,
      newValue = outLo;            // return the low CC value.
    }
    else{newValue = -1;}
  }
  else if (inputType == 1){
    Flicker::update();
    inputState = Flicker::state;
    if (Flicker::risingEdge()){
      newValue = outHi;
    }
    else if (Flicker::fallingEdge()){
      newValue = outLo;
    }
    else{newValue = -1;}
  }
  return newValue;
};


/* This function will send the appropriate Control Change messages for the press
and/or release of any MIDI button whether it's set to 'MOMENTARY' 'LATCH' or
'TRIGGER' mode.*/
int MIDIbutton::send(){
  int newValue = read();
  if (newValue == outHi){       // If the button's been pressed,
    if (state == false){        // and if it was latched OFF,
      // usbMIDI.sendControlChange(number,outHi,MIDIchannel); // send CC outHi,
	  MIDI_send(_MIDIOnMessage, number, _MIDIOnVelocity, _MIDIchannel, NULL, _MIDIcable, _MIDIface);
      newValue = number;
      state = true;             // Remember the button is now on.
    }
    else{                       // If the button was latched ON,
      if (mode == 2){           // and the button's in TRIGGER mode(2),
        // usbMIDI.sendControlChange(number,outHi,MIDIchannel); // send CC outHi again 
		MIDI_send(_MIDIOnMessage, number, _MIDIOnVelocity, _MIDIchannel, NULL, _MIDIcable, _MIDIface);
        newValue = number;
      }
      else {
		  // else send outLo
		  //usbMIDI.sendControlChange(number,outLo,MIDIchannel);
		  MIDI_send(_MIDIOffMessage, number, _MIDIOffVelocity, _MIDIchannel, NULL, _MIDIcable, _MIDIface);
	  }
      state = false;            // Remember the button is now off.
      newValue = outLo;
    }
  }
  else if (newValue == outLo && mode == 0){// Button in MOMENTARY mode released?
    //usbMIDI.sendControlChange(number,outLo,MIDIchannel); // send CC outLo,
     MIDI_send(_MIDIOffMessage, number, _MIDIOffVelocity, _MIDIchannel, NULL, _MIDIcable, _MIDIface);
    state = false;                         // Remember the button is now off
  }
  else {newValue = -1;}
  return newValue;
};


// Set the CC number.
void MIDIbutton::setControlNumber(byte num){
  number = num;
};


// Set specific min and max values.
void MIDIbutton::outputRange(byte min, byte max){
	outLo = min;
	outHi = max;
};


// Set the button mode.
void MIDIbutton::setMode(byte mod){
  mode = mod;
};

// Set the button channel, cable, interface
void MIDIbutton::setChannel(byte channel, byte cable, byte face){
  MIDIbutton::_MIDIchannel = channel;
  MIDIbutton::_MIDIcable   = cable;
  MIDIbutton::_MIDIface    = face;
};

// Set the OnMessage
void MIDIbutton::setOnMessage(byte OnMessage, byte num, byte velocity){
	MIDIbutton::_MIDIOnMessage = OnMessage;  // default is control change
	MIDIbutton::number = num;
	MIDIbutton::_MIDIOnVelocity = velocity;

}

// Set the OffMessage
void MIDIbutton::setOffMessage(byte OffMessage, byte num, byte velocity){
	MIDIbutton::_MIDIOffMessage = OffMessage;  // default is control change
	MIDIbutton::number = num;
    MIDIbutton::_MIDIOffVelocity = velocity;
}

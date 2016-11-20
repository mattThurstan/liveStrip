/*----------------------------knobs----------------------------*/

/*-----------knobs - setup------------*/
void setupKnob() {
  //called from setup
  for (int i = 0; i < _knobTotal; i++) {
    //call doSetup for each knob and pass it pins A&B
    _knob[i].doSetup(_knobPinA[i], _knobPinB[i], _knobSpeed[0][i]);
  }
  setupKnobInterrupts();
}

//attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
//attachInterrupt(interruptPin, blink, CHANGE);

void setupKnobInterrupts() {
  attachInterrupt(_knobPinA[0], interruptA0, CHANGE);  //FALLING, RISING, CHANGE
  attachInterrupt(_knobPinB[0], interruptB0, CHANGE);
  attachInterrupt(_knobPinA[1], interruptA1, CHANGE);
  attachInterrupt(_knobPinB[1], interruptB1, CHANGE);
  attachInterrupt(_knobPinA[2], interruptA2, CHANGE);
  attachInterrupt(_knobPinB[2], interruptB2, CHANGE);
  attachInterrupt(_knobPinA[3], interruptA3, CHANGE);
  attachInterrupt(_knobPinB[3], interruptB3, CHANGE);
  attachInterrupt(_knobPinA[4], interruptA4, CHANGE);
  attachInterrupt(_knobPinB[4], interruptB4, CHANGE);
  attachInterrupt(_knobPinA[5], interruptA5, CHANGE);
  attachInterrupt(_knobPinB[5], interruptB5, CHANGE);
  attachInterrupt(_knobPinA[6], interruptA6, CHANGE);
  attachInterrupt(_knobPinB[6], interruptB6, CHANGE);
  attachInterrupt(_knobPinA[7], interruptA7, CHANGE);
  attachInterrupt(_knobPinB[7], interruptB7, CHANGE);
}

void interruptA0() { _knob[0].doUpdate(); }
void interruptB0() { _knob[0].doUpdate(); }
void interruptA1() { _knob[1].doUpdate(); }
void interruptB1() { _knob[1].doUpdate(); }
void interruptA2() { _knob[2].doUpdate(); }
void interruptB2() { _knob[2].doUpdate(); }
void interruptA3() { _knob[3].doUpdate(); }
void interruptB3() { _knob[3].doUpdate(); }
void interruptA4() { _knob[4].doUpdate(); }
void interruptB4() { _knob[4].doUpdate(); }
void interruptA5() { _knob[5].doUpdate(); }
void interruptB5() { _knob[5].doUpdate(); }
void interruptA6() { _knob[6].doUpdate(); }
void interruptB6() { _knob[6].doUpdate(); }
void interruptA7() { _knob[7].doUpdate(); }
void interruptB7() { _knob[7].doUpdate(); }

/*-----------knobs - get------------*/
void knobGet() {
  //called from main loop
  if (_knobGetTimeElapsed >= _knobGetInterval) {
    //do get for each knob
    for (int i = 0; i < _knobTotal; i++) {
      //how to handle time?
      //compare old and new
      long cur = _knob[i].getCurPosition();
      //long pre = _knob[i].getPrevPosition();  //hmm.. this will always be different cos it only gets changed when something happens and interrupt fires update
      boolean hasChanged = _knob[i].getHasChanged();

      //if changed..
      //map cur pos to
      if (hasChanged) {
      
        if (_knobBehaviour[i] == 0) {                               
          //0=fixed rotary
          
          int _knobClicksPerRev = 2048; //??????  ..*1000
          int r = _knobClicksPerRev * 1000; //to put it into the same range that we are getting from lsRotaryEncoder
          
          int c = constrain(cur, r * _knobLimit[0][i], r * _knobLimit[1][i]);
          
          int m = map(c, 0, r, 0, 127);  //puts it into MIDI CC range - 8 bit
          
          int mmm = constrain(m, (127 * _knobRange[0][i]), (127 * _knobRange[1][i]));
          
          //send MIDI message
          usbMIDI.sendControlChange(_knobMidiCC[i], mmm, _midiChannel);  //control, value, channel
          //usbMIDI.send_now();

          _knobCurMidiCCSend[i] = mmm;
          
        } else if (_knobBehaviour[i] == 1) {
          //endless rotary(bit useless)
        } else if (_knobBehaviour[i] == 2) {
          //pan, etc.

          int _knobClicksPerRev = 2048; //??????  ..*1000
          int r = _knobClicksPerRev * 1000; //to put it into the same range that we are getting from lsRotaryEncoder
          
          int c = constrain(cur, -((r * _knobLimit[0][i])/2), ((r * _knobLimit[1][i])/2) ); //shifts it (in this example half to the left. 0 moves to -1024, 2048 to 1024
          
          int m = map(c, -(r/2), (r/2), 0, 127);  //puts it into MIDI CC range - 8 bit
          
          int mmm = constrain(m, (127 * _knobRange[0][i]), (127 * _knobRange[1][i]));
          
          //send MIDI message
          usbMIDI.sendControlChange(_knobMidiCC[i], mmm, _midiChannel);  //control, value, channel
          //usbMIDI.send_now();

          _knobCurMidiCCSend[i] = mmm;
          
        }

    } //END if hasChanged
      
    } //END _knobTotal for loop
    
    _knobGetTimeElapsed = 0;
  }
}
////sent MIDI value gets restricted between  and 127 depending on the following
//int _knobBehaviour[_knobTotal] = { 0 };                               //0=fixed rotary, 1=endless rotary(bit useless), 2=pan, etc.
//volatile float _knobLimit[2][_knobTotal] = { {0.2}, {0.8} };          //0-1 Start and end of simulated rotary limits. eg. like a real desk pot - used by type 0 - this should prob be under display
//volatile float _knobRange[2][_knobTotal] = { {0.0}, {1.0} };          //0-1 Start and end of restricted range within limits. eg. like MIDI mapping in a DAW - used by type 0, 1, 2
//volatile float _knobCenter[_knobTotal] = { 0.5 };                     //we can move the center point.. hmm.. this lets us do velocity curves.. have to make sure it stays inside knob range
//boolean _knobSpeedAltInUse[_knobTotal] = { false };                   //whether the knob is currently using this speed multiplier. eg. switch between slow/fast by clicking button.
//volatile float _knobSpeed[2][_knobTotal] = { {1.0}, {0.25} };         //normal speed multiplier and alternate speed multiplier


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

void interruptA0() {
    //boolean u = _knob[0].getUpdateLock();
    //if (!u) { _knob[0].doUpdate(); }
    if (!TEMPknobUpdateLock) {
      TEMPknobUpdateLock = true;  //lock it, do stuff, then unlock it
      _knob[0].doUpdate();
      TEMPknobUpdateLock = false;
    }
  }
void interruptB0() {
    //boolean u = _knob[0].getUpdateLock();
    //if (!u) { _knob[0].doUpdate(); }
    if (!TEMPknobUpdateLock) {
      TEMPknobUpdateLock = true;  //lock it, do stuff, then unlock it
      _knob[0].doUpdate();
      TEMPknobUpdateLock = false;
    }
  }
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

      if (hasChanged) {
        
        int _knobClicksPerRev = 20; //2048 ??????  ..*1000
        int r = _knobClicksPerRev * 1000; //to put it into the same range that we are getting from lsRotaryEncoder
        int c = 0;
        int m = 0;
        
        if (_knobBehaviour[i] == 0) {                               
          //0=fixed rotary
          c = constrain(cur, r * _knobLimit[0][i], r * _knobLimit[1][i]);
          m = map(c, 0, r, 0, 127);  //puts it into MIDI CC range - 8 bit
        } else if (_knobBehaviour[i] == 1) {
          //endless rotary(bit useless)
        } else if (_knobBehaviour[i] == 2) {
          //pan, etc.
          c = constrain(cur, -((r * _knobLimit[0][i])/2), ((r * _knobLimit[1][i])/2) ); //shifts it (in this example half to the left. 0 moves to -1024, 2048 to 1024
          m = map(c, -(r/2), (r/2), 0, 127);  //puts it into MIDI CC range - 8 bit
        }
        
        int mmm = 0;
        mmm = constrain(m, (127 * _knobRange[0][i]), (127 * _knobRange[1][i]));
        _knobCurMidiCCSend[i] = mmm;
        
        //send MIDI message
        usbMIDI.sendControlChange(_knobMidiCC[i], cur, _midiChannel);  //control, value, channel
        //usbMIDI.sendControlChange(_knobMidiCC[i], mmm, _midiChannel);  //control, value, channel
        usbMIDI.send_now();
          
      } //END if hasChanged
      
    } //END _knobTotal for loop
    
    _knobGetTimeElapsed = 0;
  }
}


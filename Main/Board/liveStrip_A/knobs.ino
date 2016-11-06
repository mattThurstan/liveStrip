/*----------------------------knobs----------------------------*/

void setupKnob() {
  //called from setup
  for (int i = 0; i < _knobTotal; i++) {
    //call doSetup for each knob and pass it pins A&B
    _knob[i].doSetup(_knobPinA[i], _knobPinB[i]);
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

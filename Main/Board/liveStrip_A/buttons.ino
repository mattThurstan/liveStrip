/*----------------------------buttons----------------------------*/

void setupButton() {
  //called from setup
  
  //..do setup for each button
  
  setupEndButtonInterrupts();
}

//attachInterrupt(interruptPin, function, CHANGE);
void setupEndButtonInterrupts() {
  attachInterrupt(_endButtonPin[0], interruptEB0, CHANGE);  //FALLING, RISING, CHANGE
  attachInterrupt(_endButtonPin[1], interruptEB1, CHANGE);
  attachInterrupt(_endButtonPin[2], interruptEB2, CHANGE);
  attachInterrupt(_endButtonPin[3], interruptEB3, CHANGE);
  attachInterrupt(_endButtonPin[4], interruptEB4, CHANGE);
}

void interruptEB0() {  }
void interruptEB1() {  }
void interruptEB2() {  }
void interruptEB3() {  }
void interruptEB4() {  }

/*----------------------------displays----------------------------*/

void setupDisplay() {
  //called from setup

  Tlc.init();           //TLC5940NT
  
}

/*-----------displays - set------------*/
void displaySet() {

  Tlc.clear();                                        //sets all the grayscale values to zero, but does not send them to the TLCs
  
  for (int i = 0; i < _knobTotal; i++) {
    
    int knobVal = map(_knobCurMidiCCSend[i], 0, 127, 0, 7);
    //map(_knobCurMidiCCSend[i], 0, 127, (0 + _knobLEDRingATotal), (7 + _knobLEDRingATotal))
    
    //loop to set range
    for (int j = 0; j < _knobLEDRingATotal; j++) {
      int val2;
      if (j == knobVal) {
        val2 = 4095;
      } else {
        val2 = 0;
      }
      Tlc.set(j, val2);
    }
    
    //loop to set indicator
    for (int k = 0; k < _knobLEDRingBTotal; k++) {
      int val4;
      int a = 127 * _knobRange[0][i];
      int b = 127 * _knobRange[1][i];
      
      if (k >= a || k <= b) {
        val4 = 4095;
      } else {
        val4 = 0;
      }
      Tlc.set(k + _knobLEDRingATotal, val4);
      //Tlc.set(k + _knobLEDRingATotal, 4095);          // (_knobLEDRingATotal - 1)  ?
    }

  }
  
  Tlc.update();                                       //sends the data to the TLCs
  
}


/*-----------displays - status------------*/
void blinkStatusLED() {
  //this delays the whole script. use sparingly
  digitalWrite(TEMPstatusLED, HIGH);
  delay(250);
  digitalWrite(TEMPstatusLED, LOW);
  delay(250);
  digitalWrite(TEMPstatusLED, HIGH);
  delay(250);
  digitalWrite(TEMPstatusLED, LOW);
  delay(250);
  digitalWrite(TEMPstatusLED, HIGH);
  delay(250);
  digitalWrite(TEMPstatusLED, LOW);
}

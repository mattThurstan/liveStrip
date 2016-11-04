/*
   liveStrip A 
   by M.Standish (Thurstan/mattKsp)
   
   1x rotary encoder
   1x LED matrix (2x 8x8)
  
   ..eventually..
   8x rotary encoders, ringed by 16 leds' (mono colour to start with)
   1x small screen (for channel numbers, VU meter, metronome, etc). currently 2x 8x8 LED matrix
   
	--- https://www.pjrc.com/teensy/td_libs_Encoder.html --- don't think i will use this as seems overkill, 
	need these kind of optimisations for when reading a wheel turning or engines, fast stuff. also have to 
	consider processing power availability
*/

#include <Tlc5940.h>
//#include <lsRotaryEncoder.h>
//lsRotaryEncoder knob0(0,1);

String progName = "liveStrip_A test";
String progVers = "0.02";   //don't need this ???
//String initMsg;

boolean debug = true;
int mainLoopDelay = 1;
const int numberOfKnobs = 1;   // 8
const int numberOfLEDs = 16;   // 16 LEDs per knob

int knobPinA[numberOfKnobs] = {2 };
int knobPinB[numberOfKnobs] = {4 };
int knobBt[numberOfKnobs] = {5 };

//int knobType = 0;  // 0 = normal, 1 = pan
//int knobSpeed[numberOfKnobs]; // speed multiplier. default = 1  ( stepIncrement )
int knobStepIncrement[numberOfKnobs]; 
int knobMin[numberOfKnobs];
int knobMax[numberOfKnobs];
int knobState[numberOfKnobs];  // can't do paired ints'...    ..ooh, erm, structs ???
int knobCur[numberOfKnobs];  // current reading  ( val )
//int knobPrev[numberOfKnobs];
int knobBtState[numberOfKnobs];
int LEDstart[numberOfKnobs];
int LEDend[numberOfKnobs];
boolean LEDindicator[numberOfKnobs];  // LED at bottom can be used for indicator of some sorts, or just constant marker

int LEDmax = 1023; //511  2047  4095;  // ..global for the moment
//int LEDbrightness = 4;  // 0-7 .. (4096 / 8) = 512 .. 4 x 512 = 2048 - 1 .. = 2047 .. halfway point


void setup() {
  if (debug) {
    Serial.begin(9600);
    Serial.println(".");
    Serial.print(progName);
    Serial.print(" ");
    Serial.println(progVers);
  }
  
  //Tlc.init(0);  // initialise all LEDs' at 0
  
  // init vars
  for(int i = 0; i < numberOfKnobs; i++){
    pinMode(knobPinA[i], INPUT);
    pinMode(knobPinB[i], INPUT);
    pinMode(knobBt[i], INPUT);
    //knobSpeed[i] = 5;  // speed multiplier. default = 1  ( stepIncrement )
    knobStepIncrement[i] = 5;
    knobMin[i] = 0;
    knobMax[i] = 127;
    knobState[i] = 0;
    knobCur[i] = 0;  // current value   ( val )
    //knobPrev[i] = 0; // previous value
    knobBtState[i] = 0;
    LEDstart[i] = 2;  
    LEDend[i] = 14;
    LEDindicator[i] = true; //false; 
  }
}

void loop() {
  
  for(int i = 0; i < numberOfKnobs; i++){

    knobRead(i);
    knobBtRead(i);
    
    if(knobBtState[i] == 1) {
      // do something with the button, then reset
      knobCur[i] = 0;
      knobBtState[i] = 0;
    }
    
    int knobLEDpos = map(knobCur[i], knobMin[i], knobMax[i], LEDstart[i], LEDend[i]);
    if(debug) { 
      Serial.print(" | LED pos: "); 
      Serial.println(knobLEDpos);     
    }

    //Tlc.clear();       //clear values before next setup round..
    //Tlc.set(knobLEDpos, LEDmax);  //channel, value

    if (LEDindicator[i] == true) {
      //Tlc.set(0, LEDmax );
    }
    //Tlc.update();      //..now go and do everything for LEDs'
  }

  delay(mainLoopDelay);
}

void knobRead(int i) {
  boolean a = digitalRead(knobPinA[i]);
  boolean b = digitalRead(knobPinB[i]);
   
  if(a == LOW && b == LOW){
    //Set value
    if(knobState[i] == 1){
      if(knobCur[i] > knobMin[i]){
        knobCur[i] -= knobStepIncrement[i]; //knobSpeed[i];
      }
    }
    if(knobState[i] == 2){
      if(knobCur[i] < knobMax[i]){
        knobCur[i] += knobStepIncrement[i]; //knobSpeed[i];
      }
    }
    knobState[i] = 4;
  }
  else if(a == LOW && b == HIGH){
    if(knobState[i] != 4)
      knobState[i] = 1;
  }
  else if(a == HIGH && b == LOW){
    if(knobState[i] != 4)
      knobState[i] = 2;
  }
  else if(a == HIGH && b == HIGH){
     knobState[i] = 0;
  }
  
  if(knobCur[i] < knobMin[i]){ knobCur[i] = knobMin[i]; }
  if(knobCur[i] > knobMax[i]){ knobCur[i] = knobMax[i]; }
  if(debug) { 
    Serial.print("Knob cur: "); 
    Serial.print(knobCur[i], DEC); 
  }
}

void knobBtRead(int i) {
  knobBtState[i] = digitalRead(knobBt[i]);
}

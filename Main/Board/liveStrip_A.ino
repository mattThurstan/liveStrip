// live strip test
//
// 1x rotary encoder
// 1x LED matrix (2x 8x8)
//
// ..eventually..
// 8x rotary encoders, ringed by 16 leds' (mono colour to start with)
// 1x small screen (for channel numbers, VU meter, metronome, etc). currently 2x 8x8 LED matrix
//

#include <Encoder.h>
#include <Tlc5940.h>

String progName = "liveStrip test";
String progVers = "0.01";   //don't need this ???
//String initMsg;

boolean debug = true;
int mainLoopDelay = 75;
const int numberOfKnobs = 1;   // 8
const int numberOfLEDs = 16;   // 16 LEDs per knob

// knob1-16 - leave 0 for system..
Encoder knob1(2, 4);          // 2, 3 - INTERRUPTS !!! ..can't get round this. can't spread.. have to do case switch..
//Encoder knob2(6, 7);         // etc..
//int knobSave[8];             // save current state (8 slots to start with) ..or get latest from computer ???

//int knobType = 0;  // 0 = normal, 1 = pan
int knobSpeed[numberOfKnobs]; // speed multiplier. default = 1
int knobMin[numberOfKnobs];
int knobMax[numberOfKnobs];
int knobCur[numberOfKnobs];  // current reading
int knobPrev[numberOfKnobs];
//long knobCur[numberOfKnobs];
//long knobPrev[numberOfKnobs];
int LEDstart[numberOfKnobs];
int LEDend[numberOfKnobs];
boolean LEDindicator[numberOfKnobs];  // LED at bottom can be used for indicator of some sorts, or just constant marker

int LEDmax = 1023; //511  2047  4095;  // ..global for the moment
//int LEDbrightness = 4;  // 0-7 .. (4096 / 8) = 512 .. 4 x 512 = 2048 - 1 .. = 2047 .. halfway point


void setup() {
  Serial.begin(9600);
  Serial.println(".");
  Serial.print(progName);
  Serial.print(" ");
  Serial.println(progVers);
  
  Tlc.init(0);  // initialise all LEDs' at 0
  
  // init vars
  for(int i = 0; i < numberOfKnobs; i++){
    knobSpeed[i] = 2;
    knobMin[i] = 0;
    knobMax[i] = 127;
    knobCur[i] = 0;  // current value
    knobPrev[i] = 0; // previous value
    LEDstart[i] = 2;  
    LEDend[i] = 14;
    LEDindicator[i] = true; //false; 
  }
}

void loop() {
  
  for(int i = 0; i < numberOfKnobs; i++){
    
    if(i == 0){
      //knobCur[i] = knob1.read() * knobSpeed[i];
      knobCur[i] = knob1.read();
        Serial.print(knobCur[i]);
        Serial.print(" ");
      knobCur[i] = knobCur[i] * knobSpeed[i];
        Serial.print(knobCur[i]);
        Serial.print(" ");
      if(knobCur[i] < knobMin[i]){ 
        knob1.write(knobMin[i] / knobSpeed[i]); 
        knobCur[i] = knobMin[i];
      } 
      else if(knobCur[i] > knobMax[i]){ 
        knob1.write( (knobMax[i] + 1 ) / knobSpeed[i]); 
        knobCur[i] = knobMax[i];
      }
    } 
/*  else if(i == 1){ .. }
    else if(i == 2){ .. }  */
    //etc..  

        Serial.print(knobCur[i]);
        Serial.print(" ");
    //if(knobCur[i] != knobPrev[i]){ knobPrev[i] = knobCur[i]; }
    
/*  knobCur[i] = knobCur[i] * knobSpeed[i];
    knobCur[i] = constrain(knobCur[i], knobMin[i], knobMax[i]);
      Serial.print(knobCur[i]);
      Serial.print(" "); */
  
    int knobLEDpos = map(knobCur[i], knobMin[i], knobMax[i], LEDstart[i], LEDend[i]);
      Serial.println(knobLEDpos);
    //knob1.write(0);  // virtual reset/change/.. when switching between synths
  
    Tlc.clear();       //clear values before next setup round..
    
    Tlc.set(knobLEDpos, LEDmax);  //channel, value
    
    /*if(knobLEDpos != LEDstart[i]){
      Tlc.set(knobLEDpos - 1, LEDmax / 4);
    }
    if(knobLEDpos != LEDend[i]){
      Tlc.set(knobLEDpos + 1, LEDmax / 4);
    }*/
    
    if (LEDindicator[i] == true) {
      Tlc.set(0, LEDmax );
    }
    
    Tlc.update();      //..now go and do everything for LEDs'
  }

  delay(mainLoopDelay);
}

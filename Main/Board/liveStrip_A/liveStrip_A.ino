
/*
    'liveStrip A' by Thurstan. MIDI controller for use (primarily) with Ableton Live devices.
    Copyright (C) 2016  MTS Standish (Thurstan|mattKsp)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    https://github.com/mattKsp/
*/

/*
 * 8x rotary encoders, ringed by 8x and 16 LED (mono colour to start with)
 * 1x small screen (for channel numbers, VU meter, metronome, etc). - currently 2x 8x8 LED matrix
 */
 
/*----------------------------|----------------------------*/

#include<EEPROM.h>            //for saving and loading from the EEPROM on the board
#include <lsRotaryEncoder.h>  //continous rotary encoder functions for liveStrip wrapped up in a library because..

/*----------------------------system----------------------------*/
const String _progName = "liveStrip_A";
const String _progVers = "0.03";
boolean _debug = true;
const int _mainLoopDelay = 0;   //just in case
int _orientation = 0;           //default orientation. 0-99 is same as 0-359  //normally only use 0 and 50 (0deg and 180deg), but can rotate faders to any angle.

/*----------------------------knob----------------------------*/
const int _knobTotal = 8;                                             //total knobs on device (default=8)
const int _knobPinA[_knobTotal] = { 0, 2, 4, 6, 8, 10, 12, 15 };      //Teensy 3.2 pin assignments
const int _knobPinB[_knobTotal] = { 1, 3, 5, 7, 9, 11, 14, 16 };      //miss out pin 13
volatile int _knobSpeed = 100;        //divide by 100 for float       //speed multiplier

int _knobType = 0;                                                    //0=fixed rotary, 1=endless rotary, 2=pan, etc.
int _knobLimit[_knobTotal][2] = { {20}, {80} };       //divide by 100 for float       //start and end of simulated rotary limits. eg. like a real desk pot - used by type 0
volatile int _knobRange[_knobTotal][2] = { {20}, {80} };       //divide by 100 for float       //start and end of restricted range within limits. eg. like MIDI mapping in a DAW - used by type 0, 1, 2


//have to set these up here cos library isn't set up for intitialising with empty arrays etc.
//lsRotaryEncoder knob[_knobTotal] {
//  lsRotaryEncoder(_knobPinA[0], _knobPinB[0]),
//  lsRotaryEncoder(_knobPinA[1], _knobPinB[1]),
//  lsRotaryEncoder(_knobPinA[2], _knobPinB[2]),
//  lsRotaryEncoder(_knobPinA[3], _knobPinB[3]),
//  lsRotaryEncoder(_knobPinA[4], _knobPinB[4]),
//  lsRotaryEncoder(_knobPinA[5], _knobPinB[5]),
//  lsRotaryEncoder(_knobPinA[6], _knobPinB[6]),
//  lsRotaryEncoder(_knobPinA[7], _knobPinB[7])
//  };
//yes i can.. erm, i think
lsRotaryEncoder _knob[_knobTotal];   //call blank constructors for init

/*----------------------------button----------------------------*/
const int _endButtonTotal = 3;                                //somewhere between 3 and 5 buttons at the end
const int _endButtonPin[_endButtonTotal] = { 17, 18, 19 };
//const int _knobButtonPin[_knobTotal] = { 22, 23, 24, 25, 26, 27, 28, 29 };       //if used knob buttons will be push switches integrated into the shaft of the encoder
//const int _otherButtonPin[1] = { 30 };                        //extras, not worth running a total for

/*----------------------------display----------------------------*/
int _displayBrightnessGlobal = 100; //divide by 100 for float //global brightness for displays/LEDs
/*-----------display - screen------------*/

/*-----------display - led------------*/
const int _knobLEDRingATotal = 8;                             //16
const int _knobLEDRingBTotal = 16;                            //32

/*----------------------------communication----------------------------*/
/*-----------communication - MIDI------------*/
int _defaultMIDIChannel = 1;           //the default MIDI channel


/*----------------------------MAIN----------------------------*/
void setup() {
  initEepromLoad();     //load any settings from eeprom for starters
  if (_debug) { }        //are we allowed to dissect our main course?
  //if flag true, play intro display sequence (then if first time run, set flag false)(can be re-enabled at startup from the editor)
  setupKnob();
  setupButton();
  setupDisplay();
  setupCommunication();
  //display somemething quick to indicate setup successfull.
}

void loop() {
  //
  delay(_mainLoopDelay);
}

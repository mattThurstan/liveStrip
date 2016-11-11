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
 * 
 * numbers consideration 
 * - floats take up way more space than an int, but then you have to divide the int and convert to a float.
 * calculation is minimal, but also with what we are doing here, we do not need to penny-pinch on memory space.
 * therefore just gonna use floats for this one and take the hit. the board can cope.
 */
 
/*----------------------------|----------------------------*/

#include<EEPROM.h>            //for saving and loading from the EEPROM on the board
#include <lsRotaryEncoder.h>  //continous rotary encoder functions for liveStrip wrapped up in a library because..
#include <Bounce2.h>          //buttons with de-bounce
//MIDI  - as board type is set to 'Teensy MIDI' we can use its MIDI library (usbMidi.) without declaring it

/*----------------------------system----------------------------*/
const String _progName = "liveStrip_A";
const String _progVers = "0.03";
boolean _debug = true;
const int _mainLoopDelay = 0;   //just in case
int _orientation = 0;           //current orientation. 0-359  Can rotate faders to any angle.
boolean _menuMode = false;      //flag for when we switch into menu mode

/*----------------------------knob----------------------------*/
const int _knobTotal = 8;                                             //total knobs on device (default=8)
lsRotaryEncoder _knob[_knobTotal];                                    //call blank constructors for init registration of knobs
const int _knobPinA[_knobTotal] = { 0, 2, 4, 6, 8, 10, 12, 15 };      //Teensy 3.2 pin assignments (encoders need 2 pins each). interrupt pins
const int _knobPinB[_knobTotal] = { 1, 3, 5, 7, 9, 11, 14, 16 };      //miss out pin 13
int _knobMidiCC[_knobTotal] = { 22, 23, 24, 25, 26, 27, 28, 29 };     //MIDI CC values
int _knobBehaviour[_knobTotal] = { 0 };                               //0=fixed rotary, 1=endless rotary, 2=pan, etc.
float _knobLimit[2][_knobTotal] = { {2.0}, {8.0} };                   //0-1 Start and end of simulated rotary limits. eg. like a real desk pot - used by type 0
volatile float _knobRange[2][_knobTotal] = { {0.0}, {1.0} };          //0-1 Start and end of restricted range within limits. eg. like MIDI mapping in a DAW - used by type 0, 1, 2
volatile float _knobCenter[_knobTotal] = { 0.5 };                     //we can move the center point.. hmm.. have to make sure it stays inside knob range
boolean _knobSpeedAltInUse[_knobTotal] = { false };                   //whether the knob is currently using this speed multiplier. eg. switch between slow/fast by clicking button.
volatile float _knobSpeed[2][_knobTotal] = { {1.0}, {0.25} };         //normal speed multiplier and alternate speed multiplier

/*----------------------------button----------------------------*/
const int _endButtonTotal = 5;                                        //somewhere between 3 and 5 buttons at the end
Bounce _endButton[_endButtonTotal];                                   //de-bounced buttons
Bounce _knobButton[_knobTotal];                                       //knob buttons
Bounce _otherButton;                                                  //extra button for system stuff
const int _endButtonPin[_endButtonTotal] = { 17, 18, 19, 20, 21 };          //Teensy 3.2 pin assignments. interrupt pins
const int _knobButtonPin[_knobTotal] = { 22, 23, 24, 25, 26, 27, 28, 29 };  //if used knob buttons will be push switches integrated into the shaft of the encoder. this may be changed to capacitive touch
const int _otherButtonPin = 30;                                             //extra, only need one to start with.. accessible when in menu mode (used for system, does not send MIDI)
int _endButtonMidiNote[_endButtonTotal] = { 0, 1, 2, 3, 4 };                //MIDI note values for end buttons
int _knobButtonMidiNote[_knobTotal] = {10, 11, 12, 13, 14, 15, 16, 17 };    //MIDI note values for knob buttons (if used)
//int _endButtonTriggerStyle[_knobTotal] = { 2 };                             //when sending MIDI messages, send on.. a)rose, b)fell, or c)change (.read)
int _endButtonMidiCC[_knobTotal] = { 85, 86, 87, 88, 89 };            //MIDI CC values for end buttons (90 is also available in this range set)
int _endButtonType[_knobTotal] = { 0 };                               //0=MIDI note 1=MIDI CC
int _endButtonBehaviour[_knobTotal] = { 0 };                          //0=momentary 1=toggle
boolean _endButtonToggleState[_knobTotal] = { false };                //toggle state - false=off true=on    //this can also be adjusted dependant on metering source
int _endButtonMidiOnValue[_knobTotal] = { 127 };                      //0-127 - value to send out in MIDI message
int _endButtonMidiOffValue[_knobTotal] = { 0 };                       //0-127 - ..

/*----------------------------display----------------------------*/
int _knobMeteringSource = 2;                                          //value source for metering
/* when displaying knob values, do we..
 * a) take the value straight from the knob, 
 * b) wait for the bounce-back from the sequencer, or 
 * c) compare and use both. 
 * (this could be usefull)
 * ..similar to local control on a synth
*/
int _endButtonMeteringSource = 2;                                     //..same for end buttons
float _displayBrightnessGlobal = 1.0;                                 //global brightness for displays/LEDs
/*-----------display - screen------------*/

/*-----------display - led------------*/
const int _knobLEDRingATotal = 8;                                     //16
const int _knobLEDRingBTotal = 16;                                    //32

/*----------------------------communication----------------------------*/
/*-----------communication - MIDI------------*/
const int _midiChannel = 1;                                          //the default MIDI channel - 0=global


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

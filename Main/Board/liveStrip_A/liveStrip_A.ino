
/*
    'liveStrip A' by Thurstan. MIDI controller for use (primarily) with Ableton Live devices.
    Copyright (C) {2016}  {MTS Standish (Thurstan|mattKsp)}

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

/*----------------------------system----------------------------*/
const String progName = "liveStrip_A";
const String progVers = "0.03";
boolean debug = true;
const int mainLoopDelay = 0;  //just in case

/*----------------------------MAIN----------------------------*/
void setup() {
  if (debug) { }
  //
  load any settings from eeprom
  if flag true, play intro display sequence (then if first time run, set flag false)(can be re-enabled at startup from the editor)
  setup knobs - gets done up with vars cos it's special like that
  setup buttons
  setup displays
  setup interrupts
  setup communication
  
}

void loop() {
  //
  delay(mainLoopDelay);
}

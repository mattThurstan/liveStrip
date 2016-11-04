# liveStrip
MIDI controller for use (primarily) with Ableton Live devices

Repository is an Arduino project using Teensy MIDI<br>
Transmits and receives MIDI Notes, CC & Sysex messages over USB

### Equipment
#### Hardware
- Teensy 3.2 board
- 8x endless smooth rotary encoders (with either integrated push buttons, or capacitive touch-sensing)
- 2 rings of LEDs per encoder
  * 8x blue (to indicate dial range)
  * 16x red (or green)
  * ..will try different colour combinations. power consumption is main issue here (usb limit of 500mA)
- 1x small screen (for channel numbers, VU meter, metronome, button configs, etc)
  * currently 2x 8x8 LED matrix (pins CS 10, DOUT 11, CLK 13)
- 2-5 buttons (for lock to device, menu, midi map, etc.) 

#### Software
- Arduino 
- Teensyduino plugin (for Arduino) - https://www.pjrc.com/teensy/td_download.html
  * Make sure Arduino software is set to 'MIDI'
  * You must select MIDI from the "Tools > USB Type" menu
- Parola display library for temporary 8x8 LED matrix scren - https://parola.codeplex.com/
- Encoder library
- Bounce library
- EEPROM libary
- usbMIDI library (teensy)

### Licence
- Written by M.Standish (Thurstan/mattKsp)
- Released under GNU GPLv3 (see LICENCE file)

This software is provided on an "AS-IS-BASIS".

### Reference
https://www.pjrc.com/teensy/td_midi.html<br>
https://www.pjrc.com/teensy/td_libs_Encoder.html - don't think i will use this as it seems overkill, 
	only need these kind of optimisations for when reading a wheel turning or engines, fast stuff. also have to 
	consider processing power availability<br>
 

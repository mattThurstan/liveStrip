/*----------------------------memory----------------------------*/

/*-----------loading------------*/
void initEepromLoad() {
  //called first from setup
  //eeprom is wiped everytime a new sketch is uploaded, but will be persistant thru normal use.
  loadSystemSettings();
  loadKnobSettings();
  loadButtonSettings();
  loadDisplaySettings();
  loadCommunicationSettings();
}
/*-----------loading - system------------*/
void loadSystemSettings() {

}
/*-----------loading - knob------------*/
void loadKnobSettings() {
  
}
/*-----------loading - button------------*/
void loadButtonSettings() {
  loadEndButtonSettings();           //these buttons may or may not have LEDs
  loadKnobButtonSettings();          //not enough pins - not used yet
  loadOtherButtonSettings();         //side bts, underneath bts, etc. - not used yet
}
void loadEndButtonSettings() {
  //..the buttons on the top, at one end, next the the main display screen. 3-5 buttons probably
}
void loadKnobButtonSettings() { }
void loadOtherButtonSettings() { }

/*-----------loading - display------------*/
void loadDisplaySettings() {
  loadDisplaySettingsGlobal();
  loadMainScreenSettings();
  loadEndButtonLEDSettings();           //not all buttons will have LEDs - not used yet
  loadKnobLEDSettingsA();               //load settings for knob LED ring A
  loadKnobLEDSettingsB();               //load settings for knob LED ring B
  loadOtherLEDSettings();               //status LED, LEDs for 'other' buttons, etc. - not used yet
}
void loadDisplaySettingsGlobal() { }
void loadMainScreenSettings() { }
void loadEndButtonLEDSettings() { }
void loadKnobLEDSettingsA() { }
void loadKnobLEDSettingsB() { }
void loadOtherLEDSettings() { }

/*-----------loading - communication------------*/
void loadCommunicationSettings() {
  
}

/*-----------saving------------*/
/*-----------saving - system------------*/
void saveSystemSettings(byte *sysExBytes) {
  //displayBrightness = sysExBytes[0];   //brightness of any displays/LEDs
  //defaultMidiChannel = sysExBytes[4];
  //EEPROM.write(7, 1); //write a 1 to pos 7 to indicate that system data has been saved and is available for use.
  loadSystemSettings(); //reload/update vars again from eeprom cos we just saved and changed them..
}
/*-----------saving - knob------------*/
void saveKnobSettings() { }
/*-----------saving - button------------*/
void saveButtonSettings() { 
  saveEndButtonSettings();
  saveKnobButtonSettings();
  saveOtherButtonSettings();
}

void saveEndButtonSettings() { }
void saveKnobButtonSettings() { }
void saveOtherButtonSettings() { }

/*-----------saving - display------------*/
void saveDisplaySettings() {
  saveDisplaySettingsGlobal();
  saveMainScreenSettings();
  saveEndButtonLEDSettings();
  saveKnobLEDSettingsA();
  saveKnobLEDSettingsB();
  saveOtherLEDSettings();
}
void saveDisplaySettingsGlobal() { }
void saveMainScreenSettings() { }
void saveEndButtonLEDSettings() { }
void saveKnobLEDSettingsA() { }
void saveKnobLEDSettingsB() { }
void saveOtherLEDSettings() { }

/*-----------saving - communication------------*/
void saveCommunicationSettings() { }


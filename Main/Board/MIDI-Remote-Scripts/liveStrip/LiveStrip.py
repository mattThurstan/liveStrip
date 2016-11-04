# -*- coding: utf-8 -*-
#LiveStrip.py

from __future__ import with_statement
import Live 
import time
from _Framework.ControlSurface import ControlSurface
from _Framework.TransportComponent import TransportComponent # Class encapsulating all functions in Live's transport section
from _Framework.SessionComponent import SessionComponent
from _Framework.DeviceComponent import DeviceComponent
from _Framework.ButtonElement import ButtonElement #ButtonElement(is_momentary, msg_type, channel, identifier)

import settings
from consts import *

#global variables
#CHANNEL = 8  #channels are numbered 0 - 15 - try consts.MIDI_CHANNEL
#is_momentary = True	#used for buttons
do_nothing = False		#used to stop script compiler stalling. false or true doesn't matter.

class LiveStrip(ControlSurface):
  #Control Surface is central base class. acts as container.
  __module__ = __name__
  __doc__ = "Ableton Live control surface script for LiveStrip"

  def __init__(self, c_instance):
    ControlSurface.__init__(self, c_instance)
    with self.component_guard():
      #self._suppress_send_midi = True
      self._suppress_session_highlight = True
	  #non-throw-away variables ???
	  #self._suggested_input_port = 'LiveStrip'		#???
      #self._suggested_output_port = 'LiveStrip'	#???
      #self._control_is_with_automap = False #for buttons ??? mabye for user-defined mappings 
      self._transport = None #setup a blank transport 
      self._session = None #setup a blank session
      self._device = None #setup a blank device
	  #self._is_locked = False #for device or track
      self.setup_button_control()	#buttons first - important
      #self.setup_rotary_control()   #then rotary encoders - important
      self.setup_transport_control() #then transport..
      self.setup_session_control()	#..then the rest
      self.setup_device_control()
      self.assign_button_control()	#after everything is set up we can then assign the buttons to things. ref this for updating aswell ???
      self._end_buttons[0].add_value_listener(self._bt0_value)
      self._end_buttons[1].add_value_listener(self._bt1_value)
      self._end_buttons[2].add_value_listener(self._bt2_value)
      self._end_buttons[3].add_value_listener(self._bt3_value)
      self.set_highlighting_session_component(self._session)
      self._suppress_session_highlight = False
    self.log_message("LiveStrip loaded")

  #def refresh_state(self):
    #nothing
	
  def disconnect(self):
	#self._suppress_send_midi = True
    #clean up things
	self._end_buttons[0].remove_value_listener(self._bt0_value)
    self._end_buttons[1].remove_value_listener(self._bt1_value)
    self._end_buttons[2].remove_value_listener(self._bt2_value)
    self._end_buttons[3].remove_value_listener(self._bt3_value)
    #create entry in log file then do final control surface disconnect
    self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " - LiveStrip disconnected")    
    ControlSurface.disconnect(self)
    return None
		
  def setup_button_control(self):
    #setup the buttons on the end of the LiveStrip
	#but does not assign them
	#prob do something like enter menu mode by selecting 1 & 2 together, ..blink, confirm, ..then use buttons and knobs for selection.
	is_momentary = True #button setting (throw-away variable)
	#self._end_buttons = [ButtonElement(is_momentary, 0, settings.MIDI_CHANNEL, settings.END_NOTES[index]) for index in range(4)]
	#self._end_buttons[0].name = Settings.BUTTONS_MAP_LIST[Settings.END_BUTTONS_CURRENT[0]]
	#self._end_buttons[1].name = Settings.BUTTONS_MAP_LIST[Settings.END_BUTTONS_CURRENT[1]]
	#self._end_buttons[2].name = Settings.BUTTONS_MAP_LIST[Settings.END_BUTTONS_CURRENT[2]]
	#self._end_buttons[3].name = Settings.BUTTONS_MAP_LIST[Settings.END_BUTTONS_CURRENT[3]]
	for index in range(4):
      self._end_buttons[index] = ButtonElement(is_momentary, 0, settings.MIDI_CHANNEL, settings.END_NOTES[index])
      self._end_buttons[index].name = settings.BUTTONS_MAP_LIST[settings.END_BUTTONS_CURRENT[index]]
	#i think might need to set & unset listeners if swapping the button assignments for different modes
	#for index in range(len(self._end_buttons)):
	#  self._end_buttons[index].add_value_listener(self._bt_value)
    #self._end_buttons[0].add_value_listener(self._bt0_value)
    #self._end_buttons[1].add_value_listener(self._bt1_value)
    #self._end_buttons[2].add_value_listener(self._bt2_value)
    #self._end_buttons[3].add_value_listener(self._bt3_value)
  
  #def setup_rotary_control(self):
  #setup the rotary encoders
  
  def setup_transport_control(self):
    #is_momentary = True #button setting (throw-away variable)
    self._transport = TransportComponent() #Instantiate a Transport Component
    #for index in range(4):
      #if settings.END_BUTTONS_CURRENT[index] == 4: #BUTTONS_MAP_LIST - play
        #self._transport.set_play_button(self._end_buttons[index]) #ButtonElement(is_momentary, msg_type, channel, identifier)
    #for index in range(4):
      #if settings.END_BUTTONS_CURRENT[index] == 5: #BUTTONS_MAP_LIST - stop
        #self._transport.set_stop_button(self._end_buttons[index])
  
  def setup_session_control(self):
    #do i actually need session control ??? ...erm..  ...no, i don't think i do
    #num_tracks = 1 #8 columns (tracks) - see consts
    #num_scenes = 8 #8 rows (scenes) - see consts
    #(num_tracks, num_scenes) a session highlight ("red box") 
    #self.session = SessionComponent(num_tracks,num_scenes)
    self._session = SessionComponent(settings.NUM_TRACKS, settings.NUM_SCENES)
    self._session.set_offsets(0,0)
	
  def setup_device_control(self):
    #is_momentary = True
    self._device = DeviceComponent()
    self._device.name = 'Device_Component'
    device_param_controls = []
    #for index in range(8):
    #  device_param_controls.append(self._ctrl_map[PARAMCONTROL[index]])
    #if None not in device_param_controls:
    #  self._device.set_parameter_controls(tuple(device_param_controls))
    #self._device.set_on_off_button(self._note_map[DEVICEONOFF])	#have to hand this a button
    #for index in range(4):
      #if settings.END_BUTTONS_CURRENT[index] == 1:	#BUTTONS_MAP_LIST - device lock
        #self._device.set_lock_button(self._end_buttons[index])	#watch out, this way could set several to be the same
    #for index in range(4):
      #if settings.END_BUTTONS_CURRENT[index] == 2:	#BUTTONS_MAP_LIST - device onOff
        #self._device.set_on_off_button(self._end_buttons[index])	#watch out, this way could set several to be the same
    
    self.set_device_component(self._device)

  def assign_button_control(self):
    for index in range(4):
      self.assign_individual_button_control(index)

  def assign_individual_button_control(self, index):
    #for index in range(4):
    assert isinstance(play, (ButtonElement, type(None)))
		#if (self._play_button != None):
		#	self._play_button.remove_value_listener(self._play_value)
		#self._play_button = play
		#if (self._play_button != None):
		#	self._play_button.add_value_listener(self._play_value)
		#	self._play_button.turn_off()
      
      if settings.END_BUTTONS_CURRENT[index] == 0:	#BUTTONS_MAP_LIST - NONE, or internal to LiveStrip unit.
        #self._device.set_lock_button(self._end_buttons[index])	#watch out, this way could set several to be the same
        do_nothing = True;
      elif settings.END_BUTTONS_CURRENT[index] == 1: #BUTTONS_MAP_LIST - play
        self._transport.set_play_button(self._end_buttons[index]) #ButtonElement(is_momentary, msg_type, channel, identifier)
      elif settings.END_BUTTONS_CURRENT[index] == 2: #BUTTONS_MAP_LIST - stop
        self._transport.set_stop_button(self._end_buttons[index])
      elif settings.END_BUTTONS_CURRENT[index] == 3:	#BUTTONS_MAP_LIST - device lock
        self._device.set_lock_button(self._end_buttons[index])
      elif settings.END_BUTTONS_CURRENT[index] == 4:	#BUTTONS_MAP_LIST - device on off
        self._device.set_on_off_button(self._end_buttons[index])
      elif settings.END_BUTTONS_CURRENT[index] == 5:	#BUTTONS_MAP_LIST - ???
        #self._device.set_on_off_button(self._end_buttons[index])
        do_nothing = False
		
      if (
		
      self._end_buttons[index].name = settings.BUTTONS_MAP_LIST[settings.END_BUTTONS_CURRENT[index]]	#set the name

  def _bt0_value(self, value):
    #callback when bt0 is triggered
    update_button(0)
    self.log_message("_bt0_value triggered")
	
  def _bt1_value(self, value):
    #callback when bt1 is triggered
	update_button(1)

  def _bt2_value(self, value):
    #callback when bt2 is triggered
	update_button(2)

  def _bt3_value(self, value):
    #callback when bt3 is triggered
	update_button(3)

#update button [index]
  def update_button(self, index):
    #nothing
	do_nothing = True

#update all buttons
  #def update_buttons(self):
    #for index in range(len(self._end_buttons)):
      #self._end_buttons[index].

# -*- coding: utf-8 -*-
#LiveStrip.py

from __future__ import with_statement
import Live 
import time
from _Framework.ControlSurface import ControlSurface
from _Framework.SessionComponent import SessionComponent

import Settings
from consts import *

#CHANNEL = 8  #channels are numbered 0 - 15 - try consts.MIDI_CHANNEL
#is_momentary = True	#used for buttons

class LiveStrip(ControlSurface):
  #Control Surface is central base class. acts as container.
  __module__ = "LiveStrip"
  __doc__ = "Ableton Live control surface script for LiveStrip"

  def __init__(self, c_instance):
    ControlSurface.__init__(self, c_instance)
    with self.component_guard():
      #self._suppress_send_midi = True
	  self._suppress_session_highlight = True
	  #self._suggested_input_port = 'LiveStrip'
      #self._suggested_output_port = 'LiveStrip'
      #self._control_is_with_automap = False
      #setup buttons here
	  #_do_combine()
	  self._setup_session_control()
	  self.set_highlighting_session_component(self.session)
	  self._suppress_session_highlight = False
    self.log_message("LiveStrip loaded")
	
  def _combine_active_instances():
    #nothing
  
  #_combine_active_instances = staticmethod(_combine_active_instances)
  
  def _do_combine(self):
    #nothing
  
  def _do_uncombine(self):
    #nothing
  
  def _activate_combination_mode(self, track_offset, support_devices):
    #nothing
  
  def refresh_state(self):
    #nothing
	
  def disconnect(self):
    #clean things up on disconnect
    #self._do_uncombine()
    #create entry in log file
    self.log_message(time.strftime("%d.%m.%Y %H:%M:%S", time.localtime()) + " - LiveStrip disconnected")    
    ControlSurface.disconnect(self)
    return None
		
  def _setup_session_control(self):
    #do i actually need session control ?
    #num_tracks = 1 #8 columns (tracks) - see consts
    #num_scenes = 8 #8 rows (scenes) - see consts
    #(num_tracks, num_scenes) a session highlight ("red box") 
    #self.session = SessionComponent(num_tracks,num_scenes)
    self.session = SessionComponent(NUM_TRACKS,NUM_SCENES)
    self.session.set_offsets(0,0)

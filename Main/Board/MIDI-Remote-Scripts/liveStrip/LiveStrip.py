#LiveStrip.py

from __future__ import with_statement
import Live 
from _Framework.ControlSurface import ControlSurface # Central base class for scripts based on the new Framework
from _Framework.ButtonElement import ButtonElement # Class representing a button a the controller
import Settings
from consts import *

DO_COMBINE = Live.Application.combine_apcs()  # requires 8.2 & higher

class LiveStrip(ControlSurface):
	_active_instances = []

    def __init__(self, c_instance):
		#live = Live.Application.get_application()
		#self._live_major_version = live.get_major_version()
		#self._live_minor_version = live.get_minor_version()
		#self._live_bugfix_version = live.get_bugfix_version()
		ControlSurface.__init__(self, c_instance)
		#self._device_selection_follows_track_selection = True
		with self.component_guard():
			self._suppress_send_midi = True
			self._suppress_session_highlight = True

			is_momentary = True
			self._suggested_input_port = 'LiveStrip'
			self._suggested_output_port = 'LiveStrip'
			self._control_is_with_automap = False
			#self._user_byte_write_button = ButtonElement(is_momentary, MIDI_CC_TYPE, 0, 16)
			#self._user_byte_write_button.name = 'User_Byte_Button'
			#self._user_byte_write_button.send_value(1)
			#self._user_byte_write_button.add_value_listener(self._user_byte_value)
			#self._wrote_user_byte = False
			#self._challenge = Live.Application.get_random_int(0, 400000000) & 2139062143
			#matrix = ButtonMatrixElement()
			#matrix.name = 'Button_Matrix'
			#for row in range(8):
			#	button_row = []
			#	for column in range(8):
			#		button = ConfigurableButtonElement(is_momentary, MIDI_NOTE_TYPE, 0, row * 16 + column)
			#		button.name = str(column) + '_Clip_' + str(row) + '_Button'
			#		button_row.append(button)

			#	matrix.add_row(tuple(button_row))

			#self._config_button = ButtonElement(is_momentary, MIDI_CC_TYPE, 0, 0, optimized_send_midi=False)
			#self._config_button.add_value_listener(self._config_value)
			#top_buttons = [ConfigurableButtonElement(is_momentary, MIDI_CC_TYPE, 0, 104 + index) for index in range(8)]
			#side_buttons = [ConfigurableButtonElement(is_momentary, MIDI_NOTE_TYPE, 0, SIDE_NOTES[index]) for index in range(8)]
			#top_buttons[0].name = 'Bank_Select_Up_Button'
			#top_buttons[1].name = 'Bank_Select_Down_Button'
			#top_buttons[2].name = 'Bank_Select_Left_Button'
			#top_buttons[3].name = 'Bank_Select_Right_Button'
			#top_buttons[4].name = 'Session_Button'
			#top_buttons[5].name = 'User1_Button'
			#top_buttons[6].name = 'User2_Button'
			#top_buttons[7].name = 'Mixer_Button'
			#side_buttons[0].name = 'Vol_Button'
			#side_buttons[1].name = 'Pan_Button'
			#side_buttons[2].name = 'SndA_Button'
			#side_buttons[3].name = 'SndB_Button'
			#side_buttons[4].name = 'Stop_Button'
			#side_buttons[5].name = 'Trk_On_Button'
			#side_buttons[6].name = 'Solo_Button'
			#side_buttons[7].name = 'Arm_Button'
			#self._osd = M4LInterface()
			#self._osd.name = "OSD"
			##self._selector = MainSelectorComponent(matrix, tuple(top_buttons), tuple(side_buttons), self._config_button, self._osd, self)
			##self._selector.name = 'Main_Modes'
			self._do_combine()
			#for control in self.controls:
			#	if isinstance(control, ConfigurableButtonElement):
			#		control.add_value_listener(self._button_value)

			self.set_highlighting_session_component(self._selector.session_component())
			self._suppress_session_highlight = False

			self.log_message("LiveStrip loaded")

	def _combine_active_instances():
	
	
	_combine_active_instances = staticmethod(_combine_active_instances)
	
	def _do_combine(self):
	
	def _do_uncombine(self):
	
	def _activate_combination_mode(self, track_offset, support_devices):
	
	#def refresh_state(self):
	
	//
	
	
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
	
	
	

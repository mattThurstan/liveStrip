#changeable values

# MIDI
MIDI_CHANNEL = 0
END_MIDI_MSG_TYPE = 0 #message type for buttons. 0 for MIDI Notes, 1 for MIDI CC.
END_NOTES = (64, 65, 66, 67) #end button midi note values - MIDI_NOTE_TYPE
#END_CCS = (0, 0, 0, 0) #end button midi cc values (if needed) - MIDI_CC_TYPE
ROT_MIDI_MSG_TYPE = 1 #message type for rotary knobs (prob handle continuous and rotation of unit within the unit itself)
ROT_NOTES = (70, 71, 72, 73, 74, 75, 76, 77) #rotary knob midi note values
ROT_CCS = (0, 0, 0, 0, 0, 0, 0, 0) #rotary knob midi cc values

# Device Control
DEVICELOCK = -1 #Device Lock (lock "blue hand")
DEVICEONOFF = -1 #Device on/off

# Session Navigation (aka "red box") - prob not going to use this
NUM_TRACKS = 1 #number of tracks per session. prob always be one.
NUM_SCENES = 1 #might be able to set this to 0 ???
#SESSIONLEFT = -1 #Session left
#SESSIONRIGHT = -1 #Session right

# Track Navigation
#TRACKLEFT = -1 #Track left
#TRACKRIGHT = -1 #Track right

# Sliders & Knobs - 0 to 127, or -1

MASTERVOLUME = -1 #Master track volume
PARAMCONTROL = (-1, #Param 1 #All 8 params must be assigned to positive values in order for param control to work
                -1, #Param 2
                -1, #Param 3
                -1, #Param 4
                -1, #Param 5
                -1, #Param 6
                -1, #Param 7
                -1, #Param 8
                )
				
#Link sessions between multiple LiveStrips
#SESSION__LINK = False

#presets ???
#all the mappings we could ever assign to buttons.
#these get overwritten by presets and user etc. 
#either individually, or by copying a whole preset bank onto it

#need to say - lock button, which end_button are you using now

#4 end buttons - number indicates the index within BUTTONS_MAP_LIST array
#gets overwritten
END_BUTTONS_PREV = (0, 0, 0, 0,)
END_BUTTONS_CURRENT = (1,	#button zero (top left) - init assign to NONE (TEMP Play)
					   3,	#button one - init assign to device lock
					   4,	#button two - init assign to device onOff
					   2,	#button three (bottom left) - init assign to NONE (TEMP Stop)
					   )
END_BUTTONS_NEXT = (0, 0, 0, 0)				

#all keep same index in array
BUTTONS_MAP_LIST = ('NONE', 					#0 - NONE or internal to LiveStrip, eg. rotate unit
					'Play_Button',				#1
					'Stop_Button',				#2
					'Device_Lock_Button',		#3
					'Device_On_Off_Button',		#4
					'_Button',					#5
					)


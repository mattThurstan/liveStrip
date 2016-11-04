#__init__.py
#first script run

#import script class LiveStrip
from LiveStrip_A import LiveStrip_A

#creates and returns an instance of LiveStrip_A
def create_instance(c_instance):
    return LiveStrip_A(c_instance)

#for later..
#from _Framework.Capabilities import *  # noqa
#def get_capabilities():
#	return {
#		CONTROLLER_ID_KEY: controller_id(vendor_id=4661, product_ids=[14], model_name='Launchpad'),
#		PORTS_KEY: [inport(props=[NOTES_CC, REMOTE, SCRIPT]), outport(props=[NOTES_CC, REMOTE, SCRIPT])]}

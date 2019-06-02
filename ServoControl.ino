#include "number.h"

void servo_setWheelMode(int _id)
{
	dxl.torqueOff(_id);
	delay(10);
	dxl.reset(_id);
	delay(10);
	dxl.setWheelMode(_id);
	delay(10);
	dxl.torqueOn(_id);
	delay(10);
}

void servo_setExtendedMode(int _id)
{
	dxl.torqueOff(_id);
	delay(10);
	dxl.reboot(_id);
	delay(10);
	dxl.setJointExtendedMode(_id);
	delay(10);
	dxl.torqueOn(_id);
	delay(10);
}

void servo_ledUpdate(int _id)
{
    if(_id != prev_id) {
        dxl.ledOff(DXL_ALL_ID);
        dxl.ledOn(_id);
    }
    prev_id = _id;
}
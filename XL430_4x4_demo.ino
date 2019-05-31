#include <DynamixelShield.h>
#include "InterfaceHardware.h"
#include "Encoder.h"

#define DXL_OPERATING_MODE 11

DynamixelShield dxl;

int curretnUImode = 0;
int previousUImode = 0;

const uint16_t click_freq	= 4000;
int32_t generalGoalPosition = 2048;

void setup() {
	// put your setup code here, to run once:
	dxl.begin(1000000, DXL_PACKET_VER_2_0);

	EC_init();
	initInterfacePin();
	led_launch();

	dxl.ping();
	delay(100);
	dxl.setJointExtendedMode(DXL_ALL_ID);
	dxl.setGoalPosition(DXL_ALL_ID, generalGoalPosition);

	dxl.torqueOn(DXL_ALL_ID);
}

void loop() {
	// put your main code here, to run repeatedly:

	updateCurrentUImode();
	EC_setLED(curretnUImode);

	// Serial.print(curretnUImode);
	// Serial.print("\t");
	// Serial.println(previousUImode);

	switch (curretnUImode) {
		case red:
			
			if(previousUImode != curretnUImode){
				previousUImode = curretnUImode;

				dxl.torqueOff(DXL_ALL_ID);
				delay(10);
				dxl.setJointExtendedMode(1);
				delay(10);
				dxl.torqueOn(DXL_ALL_ID);
				delay(10);
			}
			dxl.setGoalPosition(1, generalGoalPosition + EC_getEncoderCount() * 170);
			break;
		case green:
			if(previousUImode != curretnUImode){
				previousUImode = curretnUImode;

				dxl.torqueOff(DXL_ALL_ID);
				delay(10);
				dxl.setJointExtendedMode(DXL_ALL_ID);
				delay(10);
				dxl.torqueOn(DXL_ALL_ID);
				delay(10);
			}
			dxl.setGoalPosition(DXL_ALL_ID, generalGoalPosition + EC_getEncoderCount() * 170);
			break;
		case blue:
			if(previousUImode != curretnUImode){
				previousUImode = curretnUImode;

				EC_setECspeedOffset();

				dxl.torqueOff(DXL_ALL_ID);
				delay(10);
				dxl.setWheelMode(1);
				delay(10);
				dxl.torqueOn(DXL_ALL_ID);
				delay(10);
			}
			dxl.setGoalSpeed(1, EC_getECcountWithSpeedOffset() * 20);
			break;

		default:
			// do something
			break;
	}

	EC_update();
}

void dxl_setExtendedAngle()
{
	uint8_t p_data = 4;
	dxl.write(1, DXL_OPERATING_MODE, &p_data, 1, 100);
}

void led_launch()
{
	for(int i= 0; i < turnoff; i++){
			EC_setLED(i);
			delay(100);
	}
	EC_setLED(turnoff);
}

void updateCurrentUImode()
{
	if(digitalRead(ifPin[encoder_sw])){
			curretnUImode++;
			if(curretnUImode > blue){
				curretnUImode = 0;
			}

			tone(ifPin[beep], click_freq, 20);
			delay(20);
			while(digitalRead(ifPin[encoder_sw]) == HIGH);
			delay(50);
	}
}

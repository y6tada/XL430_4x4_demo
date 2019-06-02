#include <DynamixelShield.h>
#include "InterfaceHardware.h"
#include "Encoder.h"

#define DXL_OPERATING_MODE 11

DynamixelShield dxl;

int curretnUImode  = 0;
int previousUImode = 0;

const uint16_t click_freq	= 4000;
int32_t generalGoalPosition = 2048;

bool isHolded = false;

static int ECled_count = 0;
static int ECled_sing  = 1;
const  int ECled_limit = 3000;

void setup() {
	// put your setup code here, to run once:
	dxl.begin(1000000, DXL_PACKET_VER_2_0);

	EC_init();
	initInterfacePin();
	initIlluminate();

	dxl.ping();
	delay(100);
	dxl.setJointExtendedMode(DXL_ALL_ID);
	dxl.setGoalPosition(DXL_ALL_ID, generalGoalPosition);

	dxl.torqueOn(DXL_ALL_ID);
}

void loop() {
	// put your main code here, to run repeatedly:

	updateCurrentUImode();

	if(isHolded) {
		if()
	    EC_update(servoSelect);
	    ECled_count++;
	    if(ECled_count > ECled_limit) {
	     	ECled_count = 0;
	     	ECled_sing *= -1;
	    }
	    if(ECled_sing > 0) {
	        EC_setLED(curretnUImode);
	    }
	    else {
	    	EC_setLED(turnoff);
	    }
	}
	else {
		EC_setLED(curretnUImode);
		EC_update(servoAngle);

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
				dxl.setGoalPosition(1, generalGoalPosition + EC_getECcount(servoAngle) * 170);
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
				dxl.setGoalPosition(DXL_ALL_ID, generalGoalPosition + EC_getECcount(servoAngle) * 170);
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
	}
}

void initIlluminate()
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

		tone(ifPin[beep], click_freq, 20);
		// delay(20);

		if(isHolded) {
		    isHolded = false;
		    while(digitalRead(ifPin[encoder_sw]) == HIGH);
		    delay(100);
		}
		else {
			int encoder_sw_hold_cnt = 0;
			while(digitalRead(ifPin[encoder_sw]) == HIGH) {
				encoder_sw_hold_cnt++;
				delay(10);
				if(encoder_sw_hold_cnt > 50) {
				    isHolded = true;
				    tone(ifPin[beep], click_freq, 200);
				    delay(200);
				    while(digitalRead(ifPin[encoder_sw]) == HIGH);
				    delay(100);
				}
			}
			if(isHolded == false) {
			    switchUImodeToNext();
			}
		}		
	}
}

void switchUImodeToNext()
{
	curretnUImode++;
	if(curretnUImode > blue){
		curretnUImode = 0;
	}
}
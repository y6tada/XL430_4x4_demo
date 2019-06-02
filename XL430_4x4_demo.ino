#include <DynamixelShield.h>
#include "number.h"

#define DXL_OPERATING_MODE 11
#define ANGLE_CLICL_RATIO  170
#define SPEED_CLICL_RATIO  20

DynamixelShield dxl;

int curretnUImode  = green;
int previousUImode = 0;

const uint16_t click_freq	= 4000;
int32_t generalGoalPosition = 2048;

bool isHolded = false;

void setup() {
	// put your setup code here, to run once:
	dxl.begin(1000000, DXL_PACKET_VER_2_0);

	EC_init();
	initInterfacePin();
	EC_lauchIlluminate();

	dxl.ping();
	delay(100);
	servo_setExtendedMode(DXL_ALL_ID);
    delay(10);
    dxl.setGoalPosition(EC_getECcount(servoSelect), generalGoalPosition);
    delay(10);
}

void loop() {
	// put your main code here, to run repeatedly:

	updateCurrentUImode();

	if(isHolded) {
        EC_update(servoSelect);
	    servo_ledUpdate(EC_getECcount(servoSelect));

        EC_ledBlink();
	}
	else {
        EC_update(servoAngle);
		EC_setLED(curretnUImode);

		switch (curretnUImode) {
			case red:
				if(previousUImode != curretnUImode){
					previousUImode = curretnUImode;

                    servo_ledUpdate(EC_getECcount(servoSelect));
					servo_setExtendedMode(DXL_ALL_ID);
				}
				dxl.setGoalPosition(EC_getECcount(servoSelect), generalGoalPosition + EC_getECcount(servoAngle) * ANGLE_CLICL_RATIO);
				break;

			case green:
				if(previousUImode != curretnUImode){
					previousUImode = curretnUImode;

                    servo_ledUpdate(DXL_ALL_ID);
					servo_setExtendedMode(DXL_ALL_ID);
				}
				dxl.setGoalPosition(DXL_ALL_ID, generalGoalPosition + EC_getECcount(servoAngle) * ANGLE_CLICL_RATIO);
				break;

			case blue:
				if(previousUImode != curretnUImode){
					previousUImode = curretnUImode;

					EC_setECspeedOffset();
                    servo_ledUpdate(EC_getECcount(servoSelect));
					servo_setWheelMode(DXL_ALL_ID);
				}
				dxl.setGoalSpeed(EC_getECcount(servoSelect), EC_getECcountWithSpeedOffset() * SPEED_CLICL_RATIO);
				break;

			default:
				// do something
				break;
		}
	}
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
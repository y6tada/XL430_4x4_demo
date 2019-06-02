#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <Arduino.h>
#include "InterfaceHardware.h"

enum {
    red,
    green,
    blue,
    turnoff
};

enum {
	servoAngle,
	servoSelect
};

void 			EC_init();
void 			EC_getCurDat(byte *dat_p);
void 			EC_update(int rotationType);
static int8_t 	EC_getPulse(byte dat);
void 			EC_setECspeedOffset();
int16_t 		EC_getECcount(int rotationType);
int16_t 		EC_getECcountWithSpeedOffset();
void 			EC_setLED(int ledColors);


#endif

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

void 			EC_init();
void 			EC_getCurDat(byte *dat_p);
void 			EC_update();
static int8_t 	EC_getPulse(byte dat);
int16_t 		EC_getEncoderCount(void);
void 			EC_setECspeedOffset(void);
int16_t 		EC_getECcountWithSpeedOffset(void);
void 			EC_setLED(int ledColors);


#endif

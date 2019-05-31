// Encoder.h
#include <Arduino.h>
#include "InterfaceHardware.h"

#ifndef __ENCODER_H__
#define __ENCODER_H__

void EC_init();
void EC_getCurDat(byte *dat_p);
void EC_update();
static int8_t EC_getPulse(byte dat);
int16_t EC_getEncoderCount(void);
void EC_setECspeedOffset(void);
int16_t EC_getECcountWithSpeedOffset(void);

#endif

#include "Encoder.h"

const  int clickToneFreq    = 3000;
const  int clickTonePeriod  = 15;
static int encoderCount = 0;

byte curDat = 0;
byte befDat = 0;
byte rotDir = 0;
byte rotPat   = 0;

bool    inputMatch;
int16_t matchCnt;

// -------------------------------------------------------------------------- //
void EC_init()
{
    EC_getCurDat(&befDat);
}
// -------------------------------------------------------------------------- //
void EC_getCurDat(byte *dat_p)
{
  *dat_p = 0;

  if(digitalRead(ifPin[encoder_a]))
      *dat_p |= 2;
  if(digitalRead(ifPin[encoder_b]))
      *dat_p |= 1;
}
// -------------------------------------------------------------------------- //
void EC_update()
{
    EC_getCurDat(&curDat);

    if(befDat == curDat) {
        if(!inputMatch) {
            matchCnt++;
            if(matchCnt >= 5) {
                inputMatch = true;
                int8_t encoder_pulse = EC_getPulse(curDat);
                if (encoder_pulse) {
                  encoderCount += encoder_pulse;
                  tone(ifPin[beep], clickToneFreq, clickTonePeriod);
                  delay(15);
                }
            }
        }
    }
    else {
        befDat     = curDat;
        matchCnt   = 0;
        inputMatch = false;
    }
}
// -------------------------------------------------------------------------- //
int8_t EC_getPulse(byte dat)
{
    rotPat <<= 2;
    rotPat |= (dat & 0x03);

    switch (rotPat)
    {
    	case 0x4B:
    	return 1;
    	break;
    	//
    	case 0x87:
    	return -1;
    	break;
    	//
    	default:
    	return 0;
    	break;
    }
}
// -------------------------------------------------------------------------- //
int16_t EC_getEncoderCount(void)
{
  return encoderCount;
}

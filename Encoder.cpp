#include "Encoder.h"

const  int clickToneFreq            = 4000;
const  int clickTonePeriod          = 10;

static int encoderCount[2]          = {0, 0};
static int speedControlECoffset     = 0;

byte curDat     = 0;
byte befDat     = 0;
byte rotDir     = 0;
byte rotPat     = 0;

bool            inputMatch;
int16_t         matchCnt;
const int16_t   matchCntThreshold = 0;

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
void EC_update(int rotationType)
{
    EC_getCurDat(&curDat);

    if(befDat == curDat) {
        if(!inputMatch) {
            matchCnt++;
            if(matchCnt > 0) {
                inputMatch = true;
                int8_t encoder_pulse = EC_getPulse(curDat);
                if (encoder_pulse) {
                    encoderCount[rotationType] += encoder_pulse;
                    tone(ifPin[beep], clickToneFreq, clickTonePeriod);
                    delay(clickTonePeriod);
                }
            }
        }
    }
    else {
        befDat      = curDat;
        matchCnt    = 0;
        inputMatch  = false;
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
            
        case 0x87:
            return -1;
            break;
            
        default:
            return 0;
            break;
    }
}
// -------------------------------------------------------------------------- //
void EC_setECspeedOffset()
{
    speedControlECoffset = encoderCount[servoAngle];
}
// -------------------------------------------------------------------------- //
int16_t EC_getECcount(int rotationType)
{
    return encoderCount[rotationType];
}
// -------------------------------------------------------------------------- //
int16_t EC_getECcountWithSpeedOffset()
{
    return encoderCount[servoAngle] - speedControlECoffset;
}
// -------------------------------------------------------------------------- //
void EC_setLED(int ledColors)
{
    switch (ledColors) {
        case red:
            digitalWrite(ifPin[encoder_led_r], 0);
            digitalWrite(ifPin[encoder_led_g], 1);
            digitalWrite(ifPin[encoder_led_b], 1);
            break;
        case green:
            digitalWrite(ifPin[encoder_led_r], 1);
            digitalWrite(ifPin[encoder_led_g], 0);
            digitalWrite(ifPin[encoder_led_b], 1);
            break;

        case blue:
            digitalWrite(ifPin[encoder_led_r], 1);
            digitalWrite(ifPin[encoder_led_g], 1);
            digitalWrite(ifPin[encoder_led_b], 0);
            break;

        default:
            digitalWrite(ifPin[encoder_led_r], 1);
            digitalWrite(ifPin[encoder_led_g], 1);
            digitalWrite(ifPin[encoder_led_b], 1);
            break;
    }
}

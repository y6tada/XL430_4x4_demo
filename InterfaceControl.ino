#include "number.h"

void initInterfacePin() {
    for (int i = 0; i < max_pin_name; i++) {
    pinMode(ifPin[i], ifPinType[i]);
    }

    EC_setLED(turnoff);
}
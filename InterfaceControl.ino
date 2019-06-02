#include "number.h"

void initInterfacePin() {
  for (int i = 0; i < max_pin_name; i++) {
    pinMode(ifPin[i], ifPinType[i]);
  }

  digitalWrite(ifPin[encoder_led_r], 1);
  digitalWrite(ifPin[encoder_led_g], 1);
  digitalWrite(ifPin[encoder_led_b], 1);
}
#include <DynamixelShield.h>
#include "InterfaceHardware.h"
#include "Encoder.h"

DynamixelShield dxl;

void setup() {
  // put your setup code here, to run once:
  dxl.begin(1000000, DXL_PACKET_VER_2_0);
  delay(500);

  dxl.ping();
  initInterfacePin();

  tone(ifPin[beep], 2000, 100);
  delay(500);
  noTone(ifPin[beep]);

  EC_init();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (0) {
    digitalWrite(ifPin[encoder_led_r], 1);
    digitalWrite(ifPin[encoder_led_g], 1);
    digitalWrite(ifPin[encoder_led_b], 1);
    delay(500);
    digitalWrite(ifPin[encoder_led_r], 0);
    digitalWrite(ifPin[encoder_led_g], 1);
    digitalWrite(ifPin[encoder_led_b], 1);
    delay(500);
    digitalWrite(ifPin[encoder_led_r], 1);
    digitalWrite(ifPin[encoder_led_g], 0);
    digitalWrite(ifPin[encoder_led_b], 1);
    delay(500);
    digitalWrite(ifPin[encoder_led_r], 1);
    digitalWrite(ifPin[encoder_led_g], 1);
    digitalWrite(ifPin[encoder_led_b], 0);
    delay(500);
  }

  // for (int i = encoder_a; i <= encoder_sw; i++) {
  //   Serial.print(digitalRead(ifPin[i]));
  //   Serial.print("\t");
  // }
  Serial.print(EC_getEncoderCount());
  Serial.print("\n");

  EC_update();
}

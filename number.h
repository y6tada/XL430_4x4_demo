#ifndef __NUMBER_H__
#define __NUMBER_H__

enum ifPinName {
  sw_left_up,
  sw_left_down,
  sw_right_up,
  sw_right_down,
  encoder_a,
  encoder_b,
  encoder_sw,
  encoder_led_b,
  encoder_led_g,
  encoder_led_r,
  beep,
  max_pin_name
};

const byte ifPin[max_pin_name] = {
  A1,
  A0,
  A3,
  A2,
  12,
  11,
  10,
  6,
  3,
  4,
  5
};

const byte ifPinType[max_pin_name] = {
  INPUT,
  INPUT,
  INPUT,
  INPUT,
  INPUT,
  INPUT,
  INPUT,
  OUTPUT,
  OUTPUT,
  OUTPUT,
  OUTPUT
};

enum {
    red,
    green,
    blue,
    yellow,
    cyan,
    purple,
    turnoff
};

enum {
    servoAngle,
    servoSelect
};

#endif

#pragma once

#include <Arduino.h>

enum class InputEvent : uint8_t {
  None = 0,
  SwipeUp,
  SwipeDown,
  Tap,
};

struct TapPoint {
  int16_t x = 0;
  int16_t y = 0;
};

void input_init();
InputEvent input_poll(TapPoint* tap = nullptr);

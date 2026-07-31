#include "display.h"

#include <Arduino.h>

#include "board_pins.h"
#include "colors.h"

static TFT_eSPI tft;
static constexpr uint8_t kDefaultBacklight = 25;

void display_init() {
  tft.init();
  tft.setRotation(1);
  display_set_backlight(kDefaultBacklight);
  tft.fillScreen(colors::BG);
}

void display_set_backlight(uint8_t pwm) {
  analogWrite(board::LCD_BL, pwm);
}

TFT_eSPI& display() { return tft; }

int display_width() { return tft.width(); }

int display_height() { return tft.height(); }

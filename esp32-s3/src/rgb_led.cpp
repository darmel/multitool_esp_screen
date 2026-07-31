#include "rgb_led.h"

#include "board_pins.h"

// Waveshare ESP32-S3-LCD-1.47B: WS2812 on GPIO38

static bool g_lastAlert = false;
static bool g_lastGreen = false;

void rgb_led_init() {
  neopixelWrite(board::RGB_LED, 0, 0, 0);
  g_lastAlert = false;
}

void rgb_led_off() {
  neopixelWrite(board::RGB_LED, 0, 0, 0);
  g_lastAlert = false;
}

void rgb_led_tick(bool alerting, bool green_phase) {
  if (!alerting) {
    if (g_lastAlert) {
      rgb_led_off();
    }
    return;
  }

  if (!g_lastAlert || green_phase != g_lastGreen) {
    if (green_phase) {
      neopixelWrite(board::RGB_LED, 0, 80, 0);
    } else {
      neopixelWrite(board::RGB_LED, 80, 0, 0);
    }
    g_lastAlert = true;
    g_lastGreen = green_phase;
  }
}

#include "rgb_led.h"

#include "board_pins.h"
#include "display.h"

// ESP32-C6-Touch-LCD-1.47 has no WS2812 RGB LED (GPIO8 = BOOT).
// Mirror the alert with the LCD backlight so there's a visible light pulse.

static constexpr uint8_t kBlNormal = 25;
static constexpr uint8_t kBlBright = 180;
static constexpr uint8_t kBlDim = 12;

static bool g_lastAlert = false;
static bool g_lastGreen = false;

void rgb_led_init() {
  display_set_backlight(kBlNormal);
  g_lastAlert = false;
}

void rgb_led_off() {
  display_set_backlight(kBlNormal);
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
    // Bright on green phase, dim on red — syncs with screen flash.
    display_set_backlight(green_phase ? kBlBright : kBlDim);
    g_lastAlert = true;
    g_lastGreen = green_phase;
  }
  (void)board::BOOT_BTN;
}

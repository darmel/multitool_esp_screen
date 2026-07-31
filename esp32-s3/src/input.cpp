#include "input.h"

#include "board_pins.h"

// ESP32-S3-LCD-1.47B has no touch: BOOT cycles tools.
// Long-press BOOT (~700ms) = Primary action on stopwatch/timer.
// Double-click BOOT = Secondary (reset/cancel).

static constexpr int kBootPin = 0;  // BOOT
static constexpr uint32_t kLongMs = 700;
static constexpr uint32_t kDoubleMs = 400;

static bool g_prev = false;
static uint32_t g_downMs = 0;
static uint32_t g_lastReleaseMs = 0;
static uint8_t g_clicks = 0;

void input_init() {
  pinMode(kBootPin, INPUT_PULLUP);
}

InputEvent input_poll(TapPoint* tap) {
  const bool down = digitalRead(kBootPin) == LOW;
  const uint32_t now = millis();

  if (down && !g_prev) {
    g_downMs = now;
  }

  if (!down && g_prev) {
    const uint32_t held = now - g_downMs;
    if (held >= kLongMs) {
      g_clicks = 0;
      if (tap) {
        // Synthetic tap on primary button zone (left)
        tap->x = 60;
        tap->y = 140;
      }
      g_prev = down;
      return InputEvent::Tap;
    }

    g_clicks++;
    g_lastReleaseMs = now;
  }

  g_prev = down;

  if (g_clicks > 0 && !down && (now - g_lastReleaseMs) > kDoubleMs) {
    if (g_clicks >= 2) {
      g_clicks = 0;
      if (tap) {
        tap->x = 230;  // secondary zone
        tap->y = 140;
      }
      return InputEvent::Tap;
    }
    g_clicks = 0;
    return InputEvent::SwipeUp;  // short single click = next tool
  }

  return InputEvent::None;
}

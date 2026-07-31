#include "input.h"

#include <Wire.h>

#include "board_pins.h"
#include "display.h"
#include "esp_lcd_touch_axs5106l.h"

static constexpr int kSwipeMinPx = 30;
static constexpr uint32_t kMaxGestureMs = 1500;

static bool g_down = false;
static int16_t g_startX = 0;
static int16_t g_startY = 0;
static int16_t g_lastX = 0;
static int16_t g_lastY = 0;
static uint32_t g_startMs = 0;
static bool g_havePos = false;

void input_init() {
  Wire.begin(board::TP_SDA, board::TP_SCL);
  Wire.setClock(400000);
  bsp_touch_init(&Wire, board::TP_RST, board::TP_INT, display().getRotation(),
                 (uint16_t)display_width(), (uint16_t)display_height());
}

bool input_touch_pos(int16_t* x, int16_t* y) {
  if (!g_havePos || !x || !y) {
    return false;
  }
  *x = g_lastX;
  *y = g_lastY;
  return g_down;
}

InputEvent input_poll(TapPoint* tap) {
  bsp_touch_read();
  touch_data_t data{};
  const bool pressed = bsp_touch_get_coordinates(&data);

  if (pressed) {
    g_lastX = (int16_t)data.coords[0].x;
    g_lastY = (int16_t)data.coords[0].y;
    g_havePos = true;
    if (!g_down) {
      g_down = true;
      g_startX = g_lastX;
      g_startY = g_lastY;
      g_startMs = millis();
    }
    return InputEvent::None;
  }

  if (!g_down) {
    return InputEvent::None;
  }

  g_down = false;
  const int dy = g_lastY - g_startY;
  const int dx = g_lastX - g_startX;
  const uint32_t dt = millis() - g_startMs;

  if (dt <= kMaxGestureMs) {
    if (abs(dy) >= kSwipeMinPx && abs(dy) >= abs(dx)) {
      return dy < 0 ? InputEvent::SwipeUp : InputEvent::SwipeDown;
    }
    if (abs(dx) >= kSwipeMinPx && abs(dx) > abs(dy)) {
      return dx < 0 ? InputEvent::SwipeUp : InputEvent::SwipeDown;
    }
  }

  if (tap) {
    tap->x = g_lastX;
    tap->y = g_lastY;
  }
  return InputEvent::Tap;
}

#include "ui.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "colors.h"
#include "display.h"

static bool hit(int16_t x, int16_t y, int x0, int y0, int w, int h) {
  return x >= x0 && x < x0 + w && y >= y0 && y < y0 + h;
}

static void drawCentered(const char* text, int y, uint16_t color, uint8_t size) {
  Arduino_GFX& gfx = display();
  gfx.setTextSize(size);
  const int w = (int)strlen(text) * 6 * size;
  gfx.setTextColor(color);
  gfx.setCursor((gfx.width() - w) / 2, y);
  gfx.print(text);
}

static void drawButton(int x, int y, int w, int h, const char* label, uint16_t fill,
                       uint16_t textCol) {
  Arduino_GFX& gfx = display();
  gfx.fillRoundRect(x, y, w, h, 8, fill);
  gfx.setTextSize(2);
  const int tw = (int)strlen(label) * 12;
  gfx.setTextColor(textCol);
  gfx.setCursor(x + (w - tw) / 2, y + (h - 16) / 2);
  gfx.print(label);
}

void ui_format_ms(uint32_t ms, char* out, size_t outLen, bool showCents) {
  const uint32_t totalSec = ms / 1000UL;
  const uint32_t m = totalSec / 60UL;
  const uint32_t s = totalSec % 60UL;
  const uint32_t c = (ms / 10UL) % 100UL;
  if (showCents) {
    snprintf(out, outLen, "%02lu:%02lu.%02lu", (unsigned long)m, (unsigned long)s,
             (unsigned long)c);
  } else {
    snprintf(out, outLen, "%02lu:%02lu", (unsigned long)m, (unsigned long)s);
  }
}

void ui_show_message(const char* line1, const char* line2) {
  Arduino_GFX& gfx = display();
  gfx.fillScreen(colors::BG);
  drawCentered(line1, gfx.height() / 2 - (line2 ? 12 : 0), colors::CYAN, 2);
  if (line2) {
    drawCentered(line2, gfx.height() / 2 + 14, colors::WHITE, 1);
  }
}

// ---- Weather (icons) ----

static void drawSun(int cx, int cy) {
  Arduino_GFX& gfx = display();
  gfx.fillCircle(cx, cy, 18, colors::SUN);
  gfx.fillCircle(cx, cy, 12, colors::SUN_ORANGE);
  for (int i = 0; i < 8; i++) {
    const float a = i * PI / 4.0f;
    gfx.drawLine(cx + (int)(22 * cosf(a)), cy + (int)(22 * sinf(a)),
                 cx + (int)(30 * cosf(a)), cy + (int)(30 * sinf(a)), colors::SUN);
  }
}

static void drawCloud(int cx, int cy, uint16_t color) {
  Arduino_GFX& gfx = display();
  gfx.fillCircle(cx - 14, cy + 4, 12, color);
  gfx.fillCircle(cx + 12, cy + 6, 14, color);
  gfx.fillCircle(cx, cy - 4, 16, color);
  gfx.fillRoundRect(cx - 26, cy, 52, 20, 8, color);
}

static void drawRainDrops(int cx, int cy) {
  Arduino_GFX& gfx = display();
  for (int i = -2; i <= 2; i++) {
    const int x = cx + i * 10;
    gfx.fillTriangle(x, cy + 18, x - 3, cy + 28, x + 3, cy + 28, colors::RAIN);
    gfx.fillCircle(x, cy + 29, 3, colors::RAIN);
  }
}

static void drawWeatherIcon(int code, int cx, int cy) {
  Arduino_GFX& gfx = display();
  if (code == 0) {
    drawSun(cx, cy);
  } else if (code <= 2) {
    drawSun(cx - 8, cy - 8);
    drawCloud(cx + 6, cy + 6, colors::CLOUD);
  } else if (code == 3 || code == 45 || code == 48) {
    drawCloud(cx, cy - 4, colors::CLOUD_DK);
    drawCloud(cx + 8, cy + 8, colors::CLOUD);
  } else if (code >= 51 && code <= 82) {
    drawCloud(cx, cy - 10, colors::CLOUD_DK);
    drawRainDrops(cx, cy);
  } else if (code >= 95) {
    drawCloud(cx, cy - 12, colors::CLOUD_DK);
    gfx.fillTriangle(cx - 2, cy + 8, cx + 10, cy + 8, cx - 4, cy + 26, colors::STORM);
    gfx.fillTriangle(cx - 6, cy + 20, cx + 8, cy + 20, cx - 12, cy + 40, colors::STORM);
  } else {
    drawCloud(cx, cy, colors::CLOUD);
  }
}

static void drawDropIcon(int x, int y) {
  Arduino_GFX& gfx = display();
  gfx.fillTriangle(x, y, x - 6, y + 12, x + 6, y + 12, colors::DROP);
  gfx.fillCircle(x, y + 14, 6, colors::DROP);
}

static void drawWindArrow(int cx, int cy, int fromDeg, uint16_t color) {
  Arduino_GFX& gfx = display();
  const float rad = (fromDeg + 180) * PI / 180.0f;
  const int len = 22;
  const int tipX = cx + (int)(len * sinf(rad));
  const int tipY = cy - (int)(len * cosf(rad));
  const int tailX = cx - (int)(len * 0.55f * sinf(rad));
  const int tailY = cy + (int)(len * 0.55f * cosf(rad));
  gfx.drawLine(tailX, tailY, tipX, tipY, color);
  const float left = rad + 2.5f;
  const float right = rad - 2.5f;
  gfx.fillTriangle(tipX, tipY,
                   tipX - (int)(10 * sinf(left)), tipY + (int)(10 * cosf(left)),
                   tipX - (int)(10 * sinf(right)), tipY + (int)(10 * cosf(right)),
                   color);
  gfx.drawCircle(cx, cy, 28, color);
}

void ui_draw_weather(const WeatherData& w) {
  Arduino_GFX& gfx = display();
  gfx.fillScreen(colors::BG);
  gfx.fillRect(0, 0, gfx.width(), 30, colors::PANEL);
  drawCentered("Cordoba, AR", 7, colors::TITLE, 2);

  if (!w.ok) {
    drawCentered(w.status, gfx.height() / 2, colors::RED, 2);
    return;
  }

  gfx.fillRoundRect(6, 36, 92, 100, 10, colors::PANEL);
  drawWeatherIcon(w.code, 52, 80);

  char tempStr[16];
  snprintf(tempStr, sizeof(tempStr), "%.1f", w.tempC);
  gfx.setTextSize(4);
  gfx.setTextColor(weather_temp_color(w.tempC));
  gfx.setCursor(108, 40);
  gfx.print(tempStr);
  gfx.setTextSize(2);
  gfx.setCursor(108 + (int)strlen(tempStr) * 24 + 4, 52);
  gfx.print("C");

  gfx.setTextSize(2);
  gfx.setTextColor(colors::RAIN);
  gfx.setCursor(108, 82);
  gfx.print(w.status);

  drawDropIcon(116, 112);
  char humStr[20];
  snprintf(humStr, sizeof(humStr), "%d%%", w.humidity);
  gfx.setTextColor(colors::DROP);
  gfx.setCursor(134, 118);
  gfx.print(humStr);

  gfx.fillRoundRect(214, 36, 100, 100, 10, colors::PANEL);
  const uint16_t wcol = weather_wind_color(w.windKmh);
  drawWindArrow(264, 72, w.windDeg, wcol);

  char spdStr[16];
  snprintf(spdStr, sizeof(spdStr), "%.0fkm/h", w.windKmh);
  gfx.setTextSize(2);
  gfx.setTextColor(wcol);
  gfx.setCursor(264 - (int)strlen(spdStr) * 6, 108);
  gfx.print(spdStr);

  drawCentered("swipe ^ v", 152, colors::MUTED, 1);
}

// ---- Stopwatch ----

void ui_update_stopwatch_time() {
  Arduino_GFX& gfx = display();
  gfx.fillRect(0, 48, gfx.width(), 36, colors::BG);
  char buf[16];
  ui_format_ms(stopwatch_elapsed_ms(), buf, sizeof(buf), true);
  drawCentered(buf, 55, colors::WHITE, 3);
}

void ui_draw_stopwatch() {
  Arduino_GFX& gfx = display();
  gfx.fillScreen(colors::BG);
  gfx.fillRect(0, 0, gfx.width(), 28, colors::PANEL);
  drawCentered("STOPWATCH", 6, colors::TITLE, 2);

  ui_update_stopwatch_time();

  const char* primary =
      stopwatch_state() == StopwatchState::Running ? "PAUSE" : "START";
  drawButton(20, 120, 130, 40, primary, colors::RAIN, colors::WHITE);
  drawButton(170, 120, 130, 40, "RESET", colors::CLOUD_DK, colors::WHITE);
}

UiAction ui_hit_stopwatch(int16_t x, int16_t y) {
  if (hit(x, y, 20, 120, 130, 40)) return UiAction::Primary;
  if (hit(x, y, 170, 120, 130, 40)) return UiAction::Secondary;
  return UiAction::None;
}

// ---- Countdown / Timer ----

void ui_update_countdown_time() {
  Arduino_GFX& gfx = display();
  const bool alert = countdown_is_alerting();
  const uint16_t bg =
      alert ? (countdown_alert_green_phase() ? colors::GREEN_ALERT
                                             : colors::RED_ALERT)
            : colors::BG;
  gfx.fillRect(0, 32, gfx.width(), 48, bg);

  char buf[16];
  if (alert) {
    buf[0] = '+';
    ui_format_ms(countdown_overtime_ms(), buf + 1, sizeof(buf) - 1, true);
    drawCentered(buf, 40, colors::WHITE, 3);
    return;
  }

  const uint32_t ms = (countdown_state() == CountdownState::Idle)
                          ? countdown_selected_ms()
                          : countdown_remaining_ms();
  ui_format_ms(ms, buf, sizeof(buf), false);

  uint16_t timeCol = colors::WHITE;
  if (countdown_state() == CountdownState::Running) {
    timeCol = colors::SUN;
  }
  drawCentered(buf, 40, timeCol, 4);
}

void ui_draw_countdown() {
  Arduino_GFX& gfx = display();
  const bool alert = countdown_is_alerting();
  const bool green = countdown_alert_green_phase();
  const uint16_t bg =
      alert ? (green ? colors::GREEN_ALERT : colors::RED_ALERT) : colors::BG;
  const uint16_t panel =
      alert ? (green ? colors::GREEN_ALERT_DK : colors::RED_ALERT_DK)
            : colors::PANEL;

  gfx.fillScreen(bg);
  gfx.fillRect(0, 0, gfx.width(), 28, panel);
  if (alert) {
    drawCentered("¡TIEMPO!", 6, colors::WHITE, 2);
  } else {
    drawCentered("TIMER", 6, colors::TITLE, 2);
  }

  ui_update_countdown_time();

  if (alert) {
    drawCentered("OVERTIME", 88, colors::WHITE, 2);
    drawButton(20, 124, 130, 36, "AGAIN", colors::RAIN, colors::WHITE);
    drawButton(170, 124, 130, 36, "CANCEL", colors::CLOUD_DK, colors::WHITE);
    return;
  }

  // Preset chips
  static const char* labels[] = {"1", "3", "5", "8", "10", "C"};
  const int chipW = 44;
  const int gap = 6;
  const int totalW = 6 * chipW + 5 * gap;
  int x0 = (gfx.width() - totalW) / 2;
  for (uint8_t i = 0; i < 6; i++) {
    const bool sel = countdown_preset_index() == i;
    const uint16_t fill = sel ? colors::RAIN : colors::PANEL;
    gfx.fillRoundRect(x0 + i * (chipW + gap), 88, chipW, 28, 6, fill);
    gfx.setTextSize(2);
    gfx.setTextColor(colors::WHITE);
    const int tw = (int)strlen(labels[i]) * 12;
    gfx.setCursor(x0 + i * (chipW + gap) + (chipW - tw) / 2, 94);
    gfx.print(labels[i]);
  }

  if (countdown_is_custom() && countdown_state() == CountdownState::Idle) {
    drawButton(20, 124, 60, 36, "-", colors::CLOUD_DK, colors::WHITE);
    char cust[12];
    snprintf(cust, sizeof(cust), "%umin", countdown_custom_minutes());
    drawCentered(cust, 132, colors::CYAN, 2);
    drawButton(240, 124, 60, 36, "+", colors::CLOUD_DK, colors::WHITE);
  } else {
    const char* primary =
        countdown_state() == CountdownState::Running ? "PAUSE" : "START";
    drawButton(20, 124, 130, 36, primary, colors::RAIN, colors::WHITE);
    drawButton(170, 124, 130, 36, "CANCEL", colors::CLOUD_DK, colors::WHITE);
  }
}

UiAction ui_hit_countdown(int16_t x, int16_t y) {
  if (countdown_is_alerting()) {
    if (hit(x, y, 20, 124, 130, 36)) return UiAction::Primary;
    if (hit(x, y, 170, 124, 130, 36)) return UiAction::Secondary;
    return UiAction::None;
  }

  const int chipW = 44;
  const int gap = 6;
  const int totalW = 6 * chipW + 5 * gap;
  const int x0 = (display_width() - totalW) / 2;
  for (uint8_t i = 0; i < 6; i++) {
    if (hit(x, y, x0 + i * (chipW + gap), 88, chipW, 28)) {
      return static_cast<UiAction>(static_cast<uint8_t>(UiAction::Preset0) + i);
    }
  }

  if (countdown_is_custom() && countdown_state() == CountdownState::Idle) {
    if (hit(x, y, 20, 124, 60, 36)) return UiAction::CustomMinus;
    if (hit(x, y, 240, 124, 60, 36)) return UiAction::CustomPlus;
    return UiAction::None;
  }

  if (hit(x, y, 20, 124, 130, 36)) return UiAction::Primary;
  if (hit(x, y, 170, 124, 130, 36)) return UiAction::Secondary;
  return UiAction::None;
}

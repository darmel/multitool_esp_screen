#include "ui.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "colors.h"
#include "display.h"

static bool hit(int16_t x, int16_t y, int x0, int y0, int w, int h) {
  return x >= x0 && x < x0 + w && y >= y0 && y < y0 + h;
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
  TFT_eSPI& tft = display();
  tft.fillScreen(colors::BG);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(colors::CYAN, colors::BG);
  tft.drawString(line1, tft.width() / 2, tft.height() / 2 - (line2 ? 12 : 0), 2);
  if (line2) {
    tft.setTextColor(colors::WHITE, colors::BG);
    tft.drawString(line2, tft.width() / 2, tft.height() / 2 + 14, 2);
  }
}

static void drawSun(int cx, int cy) {
  TFT_eSPI& tft = display();
  tft.fillCircle(cx, cy, 18, colors::SUN);
  tft.fillCircle(cx, cy, 12, colors::SUN_ORANGE);
  for (int i = 0; i < 8; i++) {
    const float a = i * PI / 4.0f;
    tft.drawLine(cx + (int)(22 * cosf(a)), cy + (int)(22 * sinf(a)),
                 cx + (int)(30 * cosf(a)), cy + (int)(30 * sinf(a)), colors::SUN);
  }
}

static void drawCloud(int cx, int cy, uint16_t color) {
  TFT_eSPI& tft = display();
  tft.fillCircle(cx - 14, cy + 4, 12, color);
  tft.fillCircle(cx + 12, cy + 6, 14, color);
  tft.fillCircle(cx, cy - 4, 16, color);
  tft.fillRoundRect(cx - 26, cy, 52, 20, 8, color);
}

static void drawRainDrops(int cx, int cy) {
  TFT_eSPI& tft = display();
  for (int i = -2; i <= 2; i++) {
    const int x = cx + i * 10;
    tft.fillTriangle(x, cy + 18, x - 3, cy + 28, x + 3, cy + 28, colors::RAIN);
    tft.fillCircle(x, cy + 29, 3, colors::RAIN);
  }
}

static void drawBolt(int cx, int cy) {
  TFT_eSPI& tft = display();
  tft.fillTriangle(cx - 2, cy + 8, cx + 10, cy + 8, cx - 4, cy + 26, colors::STORM);
  tft.fillTriangle(cx - 6, cy + 20, cx + 8, cy + 20, cx - 12, cy + 40, colors::STORM);
}

static void drawWeatherIcon(int code, int cx, int cy) {
  TFT_eSPI& tft = display();
  if (code == 0) drawSun(cx, cy);
  else if (code == 1) {
    drawSun(cx - 6, cy - 6);
    drawCloud(cx + 8, cy + 10, colors::CLOUD);
  } else if (code == 2) {
    drawSun(cx - 10, cy - 10);
    drawCloud(cx + 4, cy + 4, colors::CLOUD);
  } else if (code == 3 || code == 45 || code == 48) {
    drawCloud(cx, cy - 4, colors::CLOUD_DK);
    drawCloud(cx + 8, cy + 8, colors::CLOUD);
  } else if (code >= 51 && code <= 67) {
    drawCloud(cx, cy - 10, colors::CLOUD_DK);
    drawRainDrops(cx, cy);
  } else if (code >= 80 && code <= 82) {
    drawCloud(cx, cy - 12, colors::CLOUD_DK);
    drawRainDrops(cx, cy - 2);
  } else if (code >= 95) {
    drawCloud(cx, cy - 14, colors::CLOUD_DK);
    drawBolt(cx, cy);
  } else if (code >= 71 && code <= 77) {
    drawCloud(cx, cy - 8, colors::CLOUD);
    for (int i = -2; i <= 2; i++) tft.fillCircle(cx + i * 10, cy + 22, 3, colors::WHITE);
  } else {
    drawCloud(cx, cy, colors::CLOUD);
  }
}

static void drawDropIcon(int x, int y) {
  TFT_eSPI& tft = display();
  tft.fillTriangle(x, y, x - 6, y + 12, x + 6, y + 12, colors::DROP);
  tft.fillCircle(x, y + 14, 6, colors::DROP);
}

static void drawWindArrow(int cx, int cy, int fromDeg, uint16_t color) {
  TFT_eSPI& tft = display();
  const float rad = (fromDeg + 180) * PI / 180.0f;
  const int len = 22;
  const int tipX = cx + (int)(len * sinf(rad));
  const int tipY = cy - (int)(len * cosf(rad));
  const int tailX = cx - (int)(len * 0.55f * sinf(rad));
  const int tailY = cy + (int)(len * 0.55f * cosf(rad));
  tft.drawLine(tailX, tailY, tipX, tipY, color);
  const float left = rad + 2.5f;
  const float right = rad - 2.5f;
  tft.fillTriangle(tipX, tipY, tipX - (int)(10 * sinf(left)),
                   tipY + (int)(10 * cosf(left)), tipX - (int)(10 * sinf(right)),
                   tipY + (int)(10 * cosf(right)), color);
  tft.drawCircle(cx, cy, 28, color);
}

void ui_draw_weather(const WeatherData& w) {
  TFT_eSPI& tft = display();
  tft.fillScreen(colors::BG);
  tft.fillRect(0, 0, tft.width(), 26, colors::PANEL);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(colors::TITLE, colors::PANEL);
  tft.drawString("Cordoba, Argentina", tft.width() / 2, 5, 2);

  if (!w.ok) {
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(colors::RED, colors::BG);
    tft.drawString(w.status, tft.width() / 2, tft.height() / 2, 2);
    return;
  }

  tft.fillRoundRect(8, 34, 100, 100, 12, colors::PANEL);
  drawWeatherIcon(w.code, 58, 78);

  char tempStr[16];
  snprintf(tempStr, sizeof(tempStr), "%.1f", w.tempC);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(weather_temp_color(w.tempC), colors::BG);
  tft.drawString(tempStr, 120, 38, 4);
  tft.setTextColor(colors::MUTED, colors::BG);
  tft.drawString("C", 120 + tft.textWidth(tempStr, 4) + 4, 52, 2);
  tft.setTextColor(colors::RAIN, colors::BG);
  tft.drawString(w.status, 120, 78, 2);

  drawDropIcon(128, 108);
  char humStr[20];
  snprintf(humStr, sizeof(humStr), "%d%%", w.humidity);
  tft.setTextColor(colors::DROP, colors::BG);
  tft.drawString(humStr, 142, 108, 2);

  tft.fillRoundRect(210, 34, 102, 100, 12, colors::PANEL);
  const uint16_t wcol = weather_wind_color(w.windKmh);
  drawWindArrow(261, 78, w.windDeg, wcol);
  char spdStr[16];
  snprintf(spdStr, sizeof(spdStr), "%.0f km/h", w.windKmh);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(wcol, colors::PANEL);
  tft.drawString(spdStr, 261, 112, 2);
  tft.setTextColor(colors::MUTED, colors::BG);
  tft.drawString("BOOT: next tool", tft.width() / 2, 155, 1);
}

static void drawBtn(int x, int y, int w, int h, const char* label, uint16_t fill) {
  TFT_eSPI& tft = display();
  tft.fillRoundRect(x, y, w, h, 8, fill);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(colors::WHITE, fill);
  tft.drawString(label, x + w / 2, y + h / 2, 2);
}

void ui_update_stopwatch_time() {
  TFT_eSPI& tft = display();
  tft.fillRect(0, 48, tft.width(), 44, colors::BG);
  char buf[16];
  ui_format_ms(stopwatch_elapsed_ms(), buf, sizeof(buf), true);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(colors::WHITE, colors::BG);
  tft.drawString(buf, tft.width() / 2, 70, 4);
}

void ui_draw_stopwatch() {
  TFT_eSPI& tft = display();
  tft.fillScreen(colors::BG);
  tft.fillRect(0, 0, tft.width(), 26, colors::PANEL);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(colors::TITLE, colors::PANEL);
  tft.drawString("STOPWATCH", tft.width() / 2, 5, 2);

  ui_update_stopwatch_time();

  const char* primary =
      stopwatch_state() == StopwatchState::Running ? "PAUSE" : "START";
  drawBtn(20, 120, 130, 40, primary, colors::RAIN);
  drawBtn(170, 120, 130, 40, "RESET", colors::CLOUD_DK);
}

UiAction ui_hit_stopwatch(int16_t x, int16_t y) {
  if (hit(x, y, 20, 120, 130, 40)) return UiAction::Primary;
  if (hit(x, y, 170, 120, 130, 40)) return UiAction::Secondary;
  return UiAction::None;
}

void ui_update_countdown_time() {
  TFT_eSPI& tft = display();
  const bool alert = countdown_is_alerting();
  const uint16_t bg =
      alert ? (countdown_alert_green_phase() ? colors::GREEN_ALERT
                                             : colors::RED_ALERT)
            : colors::BG;
  tft.fillRect(0, 30, tft.width(), 50, bg);

  char buf[16];
  tft.setTextDatum(MC_DATUM);
  if (alert) {
    buf[0] = '+';
    ui_format_ms(countdown_overtime_ms(), buf + 1, sizeof(buf) - 1, true);
    tft.setTextColor(colors::WHITE, bg);
    tft.drawString(buf, tft.width() / 2, 55, 4);
    return;
  }

  const uint32_t ms = (countdown_state() == CountdownState::Idle)
                          ? countdown_selected_ms()
                          : countdown_remaining_ms();
  ui_format_ms(ms, buf, sizeof(buf), false);
  uint16_t timeCol = colors::WHITE;
  if (countdown_state() == CountdownState::Running) timeCol = colors::SUN;
  tft.setTextColor(timeCol, colors::BG);
  tft.drawString(buf, tft.width() / 2, 55, 4);
}

void ui_draw_countdown() {
  TFT_eSPI& tft = display();
  const bool alert = countdown_is_alerting();
  const bool green = countdown_alert_green_phase();
  const uint16_t bg =
      alert ? (green ? colors::GREEN_ALERT : colors::RED_ALERT) : colors::BG;
  const uint16_t panel =
      alert ? (green ? colors::GREEN_ALERT_DK : colors::RED_ALERT_DK)
            : colors::PANEL;

  tft.fillScreen(bg);
  tft.fillRect(0, 0, tft.width(), 26, panel);
  tft.setTextDatum(TC_DATUM);
  if (alert) {
    tft.setTextColor(colors::WHITE, panel);
    tft.drawString("TIEMPO!", tft.width() / 2, 5, 2);
  } else {
    tft.setTextColor(colors::TITLE, panel);
    tft.drawString("TIMER", tft.width() / 2, 5, 2);
  }

  ui_update_countdown_time();

  if (alert) {
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(colors::WHITE, bg);
    tft.drawString("OVERTIME", tft.width() / 2, 90, 2);
    drawBtn(20, 124, 130, 36, "AGAIN", colors::RAIN);
    drawBtn(170, 124, 130, 36, "CANCEL", colors::CLOUD_DK);
    return;
  }

  static const char* labels[] = {"1", "3", "5", "8", "10", "C"};
  const int chipW = 44, gap = 6;
  const int totalW = 6 * chipW + 5 * gap;
  int x0 = (tft.width() - totalW) / 2;
  for (uint8_t i = 0; i < 6; i++) {
    const bool sel = countdown_preset_index() == i;
    tft.fillRoundRect(x0 + i * (chipW + gap), 90, chipW, 26, 6,
                      sel ? colors::RAIN : colors::PANEL);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(colors::WHITE, sel ? colors::RAIN : colors::PANEL);
    tft.drawString(labels[i], x0 + i * (chipW + gap) + chipW / 2, 103, 2);
  }

  if (countdown_is_custom() && countdown_state() == CountdownState::Idle) {
    drawBtn(20, 124, 60, 36, "-", colors::CLOUD_DK);
    char cust[12];
    snprintf(cust, sizeof(cust), "%umin", countdown_custom_minutes());
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(colors::CYAN, colors::BG);
    tft.drawString(cust, tft.width() / 2, 142, 2);
    drawBtn(240, 124, 60, 36, "+", colors::CLOUD_DK);
  } else {
    const char* primary =
        countdown_state() == CountdownState::Running ? "PAUSE" : "START";
    drawBtn(20, 124, 130, 36, primary, colors::RAIN);
    drawBtn(170, 124, 130, 36, "CANCEL", colors::CLOUD_DK);
  }
}

UiAction ui_hit_countdown(int16_t x, int16_t y) {
  if (countdown_is_alerting()) {
    if (hit(x, y, 20, 124, 130, 36)) return UiAction::Primary;
    if (hit(x, y, 170, 124, 130, 36)) return UiAction::Secondary;
    return UiAction::None;
  }
  const int chipW = 44, gap = 6;
  const int totalW = 6 * chipW + 5 * gap;
  const int x0 = (display_width() - totalW) / 2;
  for (uint8_t i = 0; i < 6; i++) {
    if (hit(x, y, x0 + i * (chipW + gap), 90, chipW, 26)) {
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

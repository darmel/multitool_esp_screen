#pragma once

#include "countdown.h"
#include "stopwatch.h"
#include "weather.h"

void ui_show_message(const char* line1, const char* line2 = nullptr);
void ui_draw_weather(const WeatherData& w);
void ui_draw_stopwatch();
void ui_draw_countdown();
// Fast path: only refresh the time digits (no full-screen clear).
void ui_update_stopwatch_time();
void ui_update_countdown_time();

// Hit-test helpers for the currently drawn tool UI (screen coords).
enum class UiAction : uint8_t {
  None = 0,
  Primary,    // start/pause
  Secondary,  // reset/cancel
  Preset0,
  Preset1,
  Preset2,
  Preset3,
  Preset4,
  PresetCustom,
  CustomMinus,
  CustomPlus,
};

UiAction ui_hit_stopwatch(int16_t x, int16_t y);
UiAction ui_hit_countdown(int16_t x, int16_t y);

void ui_format_ms(uint32_t ms, char* out, size_t outLen, bool showCents);

#pragma once

#include <Arduino.h>

enum class ToolId : uint8_t {
  Weather = 0,
  Stopwatch = 1,
  Countdown = 2,
  Count = 3,
};

void app_init();
void app_tick();
void app_render(bool force);
ToolId app_current_tool();
void app_next_tool();
void app_prev_tool();
void app_set_tool(ToolId id);
void app_request_redraw();

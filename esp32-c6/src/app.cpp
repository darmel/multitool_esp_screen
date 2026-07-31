#include "app.h"

#include "countdown.h"
#include "input.h"
#include "rgb_led.h"
#include "stopwatch.h"
#include "ui.h"
#include "weather.h"
#include "wifi_net.h"

static constexpr uint32_t kWeatherRefreshMs = 10UL * 60UL * 1000UL;
static constexpr uint32_t kStopwatchUiMs = 33;
static constexpr uint32_t kCountdownUiMs = 100;
static constexpr uint32_t kAlertUiMs = 80;

static ToolId g_tool = ToolId::Weather;
static WeatherData g_weather;
static uint32_t g_lastWeatherFetch = 0;
static bool g_needFullRedraw = true;
static bool g_needTimeRedraw = false;
static uint32_t g_lastUiMs = 0;
static bool g_lastAlertGreen = false;
static bool g_wasAlerting = false;

static void handleTap(const TapPoint& tap) {
  if (g_tool == ToolId::Stopwatch) {
    const UiAction a = ui_hit_stopwatch(tap.x, tap.y);
    if (a == UiAction::Primary) stopwatch_toggle();
    if (a == UiAction::Secondary) stopwatch_reset();
    g_needFullRedraw = true;
    return;
  }
  if (g_tool == ToolId::Countdown) {
    const UiAction a = ui_hit_countdown(tap.x, tap.y);
    switch (a) {
      case UiAction::Primary:
        countdown_toggle();
        break;
      case UiAction::Secondary:
        countdown_cancel();
        break;
      case UiAction::Preset0:
      case UiAction::Preset1:
      case UiAction::Preset2:
      case UiAction::Preset3:
      case UiAction::Preset4:
      case UiAction::PresetCustom:
        if (!countdown_is_alerting()) {
          countdown_select_preset(static_cast<uint8_t>(a) -
                                  static_cast<uint8_t>(UiAction::Preset0));
        }
        break;
      case UiAction::CustomMinus:
        countdown_adjust_custom(-1);
        break;
      case UiAction::CustomPlus:
        countdown_adjust_custom(1);
        break;
      default:
        break;
    }
    g_needFullRedraw = true;
  }
}

void app_init() {
  rgb_led_init();
  countdown_init();
  stopwatch_reset();
  g_tool = ToolId::Weather;
  g_needFullRedraw = true;

  if (wifi_connect()) {
    if (weather_fetch(g_weather)) {
      g_lastWeatherFetch = millis();
    }
  }
}

void app_next_tool() {
  g_tool = static_cast<ToolId>((static_cast<uint8_t>(g_tool) + 1) %
                               static_cast<uint8_t>(ToolId::Count));
  g_needFullRedraw = true;
}

void app_prev_tool() {
  const uint8_t n = static_cast<uint8_t>(ToolId::Count);
  g_tool = static_cast<ToolId>((static_cast<uint8_t>(g_tool) + n - 1) % n);
  g_needFullRedraw = true;
}

void app_set_tool(ToolId id) {
  g_tool = id;
  g_needFullRedraw = true;
}

ToolId app_current_tool() { return g_tool; }

void app_request_redraw() { g_needFullRedraw = true; }

void app_tick() {
  stopwatch_tick();
  countdown_tick();

  const bool alerting = countdown_is_alerting();
  const bool green = countdown_alert_green_phase();
  rgb_led_tick(alerting, green);

  if (alerting && !g_wasAlerting) {
    // Just hit zero — jump to timer screen so the alert is visible.
    if (g_tool != ToolId::Countdown) {
      g_tool = ToolId::Countdown;
    }
    g_needFullRedraw = true;
  }
  g_wasAlerting = alerting;

  if (millis() - g_lastWeatherFetch >= kWeatherRefreshMs ||
      g_lastWeatherFetch == 0) {
    const bool quiet = g_tool != ToolId::Weather || g_lastWeatherFetch != 0;
    if (weather_fetch(g_weather, quiet)) {
      g_lastWeatherFetch = millis();
      if (g_tool == ToolId::Weather) {
        g_needFullRedraw = true;
      }
    } else if (g_tool == ToolId::Weather) {
      g_needFullRedraw = true;
    }
  }

  TapPoint tap{};
  const InputEvent ev = input_poll(&tap);
  if (ev == InputEvent::SwipeUp) {
    app_next_tool();
  } else if (ev == InputEvent::SwipeDown) {
    app_prev_tool();
  } else if (ev == InputEvent::Tap) {
    handleTap(tap);
  }

  const uint32_t now = millis();
  if (g_tool == ToolId::Stopwatch &&
      stopwatch_state() == StopwatchState::Running &&
      now - g_lastUiMs >= kStopwatchUiMs) {
    g_needTimeRedraw = true;
  } else if (g_tool == ToolId::Countdown && alerting) {
    if (green != g_lastAlertGreen || now - g_lastUiMs >= kAlertUiMs) {
      g_lastAlertGreen = green;
      g_needFullRedraw = true;
    }
  } else if (g_tool == ToolId::Countdown &&
             countdown_state() == CountdownState::Running &&
             now - g_lastUiMs >= kCountdownUiMs) {
    g_needTimeRedraw = true;
  }
}

void app_render(bool force) {
  if (force) {
    g_needFullRedraw = true;
  }
  if (!g_needFullRedraw && !g_needTimeRedraw) {
    return;
  }

  if (g_needFullRedraw) {
    g_needFullRedraw = false;
    g_needTimeRedraw = false;
    g_lastUiMs = millis();
    switch (g_tool) {
      case ToolId::Weather:
        ui_draw_weather(g_weather);
        break;
      case ToolId::Stopwatch:
        ui_draw_stopwatch();
        break;
      case ToolId::Countdown:
        ui_draw_countdown();
        break;
      default:
        break;
    }
    return;
  }

  g_needTimeRedraw = false;
  g_lastUiMs = millis();
  if (g_tool == ToolId::Stopwatch) {
    ui_update_stopwatch_time();
  } else if (g_tool == ToolId::Countdown) {
    ui_update_countdown_time();
  }
}

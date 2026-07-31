#include "countdown.h"

static const uint16_t kPresetsMin[] = {1, 3, 5, 8, 10};
static constexpr uint32_t kAlertHalfMs = 400;

static CountdownState g_state = CountdownState::Idle;
static uint8_t g_preset = 0;
static uint16_t g_customMin = 7;
static uint32_t g_remaining = 0;
static uint32_t g_overtime = 0;
static uint32_t g_lastTick = 0;

static uint32_t selectedMs() {
  if (g_preset < 5) {
    return (uint32_t)kPresetsMin[g_preset] * 60UL * 1000UL;
  }
  return (uint32_t)g_customMin * 60UL * 1000UL;
}

void countdown_init() {
  g_state = CountdownState::Idle;
  g_preset = 2;  // 5 min default
  g_customMin = 7;
  g_remaining = selectedMs();
  g_overtime = 0;
  g_lastTick = 0;
}

void countdown_tick() {
  if (g_state != CountdownState::Running &&
      g_state != CountdownState::Finished) {
    return;
  }

  const uint32_t now = millis();
  const uint32_t dt = now - g_lastTick;
  g_lastTick = now;

  if (g_state == CountdownState::Finished) {
    g_overtime += dt;
    return;
  }

  if (dt >= g_remaining) {
    g_remaining = 0;
    g_overtime = 0;
    g_state = CountdownState::Finished;
    return;
  }
  g_remaining -= dt;
}

void countdown_select_preset(uint8_t index) {
  if (index > 5) {
    return;
  }
  g_preset = index;
  if (g_state == CountdownState::Idle || g_state == CountdownState::Finished) {
    g_remaining = selectedMs();
    g_overtime = 0;
    g_state = CountdownState::Idle;
  }
}

void countdown_set_custom_minutes(uint16_t minutes) {
  if (minutes < 1) minutes = 1;
  if (minutes > 180) minutes = 180;
  g_customMin = minutes;
  g_preset = 5;
  if (g_state == CountdownState::Idle || g_state == CountdownState::Finished) {
    g_remaining = selectedMs();
    g_overtime = 0;
    g_state = CountdownState::Idle;
  }
}

void countdown_adjust_custom(int delta_min) {
  int m = (int)g_customMin + delta_min;
  if (m < 1) m = 1;
  if (m > 180) m = 180;
  countdown_set_custom_minutes((uint16_t)m);
}

void countdown_arm_selected() {
  g_remaining = selectedMs();
  g_overtime = 0;
  g_state = CountdownState::Idle;
}

void countdown_toggle() {
  if (g_state == CountdownState::Running) {
    g_state = CountdownState::Paused;
    return;
  }
  if (g_state == CountdownState::Finished) {
    g_remaining = selectedMs();
    g_overtime = 0;
  }
  if (g_remaining == 0) {
    g_remaining = selectedMs();
  }
  g_state = CountdownState::Running;
  g_lastTick = millis();
}

void countdown_cancel() {
  g_state = CountdownState::Idle;
  g_remaining = selectedMs();
  g_overtime = 0;
  g_lastTick = 0;
}

CountdownState countdown_state() { return g_state; }

uint8_t countdown_preset_index() { return g_preset; }

uint16_t countdown_custom_minutes() { return g_customMin; }

uint32_t countdown_remaining_ms() { return g_remaining; }

uint32_t countdown_overtime_ms() { return g_overtime; }

uint32_t countdown_selected_ms() { return selectedMs(); }

bool countdown_is_custom() { return g_preset == 5; }

bool countdown_is_alerting() { return g_state == CountdownState::Finished; }

bool countdown_alert_green_phase() {
  return ((millis() / kAlertHalfMs) % 2) == 0;
}

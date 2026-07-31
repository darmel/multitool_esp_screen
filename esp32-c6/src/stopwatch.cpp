#include "stopwatch.h"

static StopwatchState g_state = StopwatchState::Idle;
static uint32_t g_elapsed = 0;
static uint32_t g_lastTick = 0;

void stopwatch_reset() {
  g_state = StopwatchState::Idle;
  g_elapsed = 0;
  g_lastTick = 0;
}

void stopwatch_toggle() {
  if (g_state == StopwatchState::Running) {
    g_state = StopwatchState::Paused;
    return;
  }
  g_state = StopwatchState::Running;
  g_lastTick = millis();
}

void stopwatch_tick() {
  if (g_state != StopwatchState::Running) {
    return;
  }
  const uint32_t now = millis();
  g_elapsed += now - g_lastTick;
  g_lastTick = now;
}

StopwatchState stopwatch_state() { return g_state; }

uint32_t stopwatch_elapsed_ms() { return g_elapsed; }

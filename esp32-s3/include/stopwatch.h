#pragma once

#include <Arduino.h>

enum class StopwatchState : uint8_t { Idle, Running, Paused };

void stopwatch_reset();
void stopwatch_toggle();  // start / pause
void stopwatch_tick();
StopwatchState stopwatch_state();
uint32_t stopwatch_elapsed_ms();

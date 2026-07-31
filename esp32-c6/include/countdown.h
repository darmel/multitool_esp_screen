#pragma once

#include <Arduino.h>

enum class CountdownState : uint8_t { Idle, Running, Paused, Finished };

void countdown_init();
void countdown_tick();
void countdown_select_preset(uint8_t index);  // 0..4 = 1/3/5/8/10 min, 5 = custom
void countdown_set_custom_minutes(uint16_t minutes);
void countdown_adjust_custom(int delta_min);
void countdown_arm_selected();  // load selected duration into remaining (idle)
void countdown_toggle();        // start/pause / again
void countdown_cancel();        // back to idle with selected duration
CountdownState countdown_state();
uint8_t countdown_preset_index();
uint16_t countdown_custom_minutes();
uint32_t countdown_remaining_ms();
uint32_t countdown_overtime_ms();  // elapsed since 0 (Finished)
uint32_t countdown_selected_ms();
bool countdown_is_custom();
bool countdown_is_alerting();  // Finished / overtime alarm active
// Shared blink phase for screen + RGB (true = green, false = red).
bool countdown_alert_green_phase();

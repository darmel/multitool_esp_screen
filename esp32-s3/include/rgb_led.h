#pragma once

#include <Arduino.h>

void rgb_led_init();
void rgb_led_off();
// Drive alert blink (green/red) when alerting; otherwise off.
void rgb_led_tick(bool alerting, bool green_phase);

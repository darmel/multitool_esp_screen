#pragma once

#include <TFT_eSPI.h>
#include <stdint.h>

void display_init();
void display_set_backlight(uint8_t pwm);
TFT_eSPI& display();
int display_width();
int display_height();

#pragma once

#include <Arduino_GFX_Library.h>
#include <stdint.h>

void display_init();
void display_set_backlight(uint8_t pwm);
Arduino_GFX& display();
Arduino_DataBus* display_bus();
int display_width();
int display_height();

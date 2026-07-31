#pragma once

#include <Arduino.h>

struct WeatherData {
  bool ok = false;
  float tempC = 0;
  int humidity = 0;
  float windKmh = 0;
  int windDeg = 0;
  int code = -1;
  char status[48] = "Sin datos";
};

bool weather_fetch(WeatherData& out, bool quiet = false);
const char* weather_text(int code);
const char* weather_wind_cardinal(int deg);
const char* weather_wind_label(float kmh);
uint16_t weather_temp_color(float t);
uint16_t weather_wind_color(float kmh);

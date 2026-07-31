#include "weather.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "colors.h"
#include "ui.h"
#include "wifi_net.h"

static constexpr float kLat = -31.4201f;
static constexpr float kLon = -64.1888f;

const char* weather_text(int code) {
  if (code == 0) return "Despejado";
  if (code == 1) return "Mayormente claro";
  if (code == 2) return "Parcial nublado";
  if (code == 3) return "Nublado";
  if (code == 45 || code == 48) return "Niebla";
  if (code >= 51 && code <= 57) return "Llovizna";
  if (code >= 61 && code <= 67) return "Lluvia";
  if (code >= 71 && code <= 77) return "Nieve";
  if (code >= 80 && code <= 82) return "Chubascos";
  if (code >= 95 && code <= 99) return "Tormenta";
  return "Variable";
}

const char* weather_wind_cardinal(int deg) {
  static const char* dirs[] = {"N", "NE", "E", "SE", "S", "SO", "O", "NO"};
  const int idx = ((deg % 360) + 360) % 360;
  return dirs[(int)((idx + 22) / 45) % 8];
}

const char* weather_wind_label(float kmh) {
  if (kmh < 1) return "Sin viento";
  if (kmh < 6) return "Casi calmo";
  if (kmh < 12) return "Brisa suave";
  if (kmh < 20) return "Hay viento";
  if (kmh < 30) return "Viento fresco";
  return "Viento fuerte";
}

uint16_t weather_temp_color(float t) {
  if (t < 5) return 0x7DFF;
  if (t < 15) return 0x07FF;
  if (t < 25) return 0x07E0;
  if (t < 32) return 0xFE60;
  return colors::RED;
}

uint16_t weather_wind_color(float kmh) {
  if (kmh < 6) return 0x7BEF;
  if (kmh < 20) return colors::WIND;
  if (kmh < 30) return colors::SUN_ORANGE;
  return colors::RED;
}

bool weather_fetch(WeatherData& out, bool quiet) {
  if (!wifi_is_connected()) {
    if (quiet) {
      out.ok = false;
      snprintf(out.status, sizeof(out.status), "Sin WiFi");
      return false;
    }
    if (!wifi_connect()) {
      out.ok = false;
      snprintf(out.status, sizeof(out.status), "Sin WiFi");
      return false;
    }
  }

  if (!quiet) {
    ui_show_message("Consultando", "clima Cordoba...");
  }

  String url =
      "https://api.open-meteo.com/v1/forecast?latitude=" + String(kLat, 4) +
      "&longitude=" + String(kLon, 4) +
      "&current=temperature_2m,relative_humidity_2m,weather_code,"
      "wind_speed_10m,wind_direction_10m&wind_speed_unit=kmh"
      "&timezone=America%2FArgentina%2FCordoba";

  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  http.setTimeout(12000);
  if (!http.begin(client, url)) {
    out.ok = false;
    snprintf(out.status, sizeof(out.status), "HTTP begin fail");
    return false;
  }

  const int httpCode = http.GET();
  if (httpCode != HTTP_CODE_OK) {
    out.ok = false;
    snprintf(out.status, sizeof(out.status), "HTTP %d", httpCode);
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  JsonDocument doc;
  if (deserializeJson(doc, payload)) {
    out.ok = false;
    snprintf(out.status, sizeof(out.status), "JSON error");
    return false;
  }

  JsonObject current = doc["current"];
  out.tempC = current["temperature_2m"] | 0.0f;
  out.humidity = current["relative_humidity_2m"] | 0;
  out.windKmh = current["wind_speed_10m"] | 0.0f;
  out.windDeg = current["wind_direction_10m"] | 0;
  out.code = current["weather_code"] | -1;
  snprintf(out.status, sizeof(out.status), "%s", weather_text(out.code));
  out.ok = true;
  return true;
}

#include "wifi_net.h"

#include <WiFi.h>

#include "secrets.h"
#include "ui.h"

static constexpr uint32_t kWifiTimeoutMs = 20000;

bool wifi_is_connected() { return WiFi.status() == WL_CONNECTED; }

bool wifi_connect() {
  ui_show_message("Conectando WiFi", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  const uint32_t start = millis();
  while (!wifi_is_connected() && millis() - start < kWifiTimeoutMs) {
    delay(250);
  }

  if (!wifi_is_connected()) {
    ui_show_message("WiFi error", "Reintentando...");
    return false;
  }

  ui_show_message("WiFi OK", WiFi.localIP().toString().c_str());
  delay(600);
  return true;
}

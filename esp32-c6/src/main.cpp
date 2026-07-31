#include <Arduino.h>

#include "app.h"
#include "display.h"
#include "input.h"

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("multitool / esp32-c6");

  display_init();
  input_init();
  app_init();
  app_render(true);
}

void loop() {
  app_tick();
  app_render(false);
  delay(2);
}

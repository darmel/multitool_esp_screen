#include "esp_lcd_touch_axs5106l.h"

TwoWire *g_touch_i2c;

uint16_t g_width;
uint16_t g_height;
uint16_t g_rotation;
touch_data_t g_touch_data;

static volatile bool g_touch_int_flag = false;

static bool touch_i2c_read(uint8_t driver_addr, uint8_t reg_addr, uint8_t *data,
                           uint32_t length) {
  g_touch_i2c->beginTransmission(driver_addr);
  g_touch_i2c->write(reg_addr);
  if (g_touch_i2c->endTransmission() != 0) {
    return false;
  }

  const size_t got = g_touch_i2c->requestFrom(driver_addr, (size_t)length);
  if (got != length) {
    return false;
  }
  g_touch_i2c->readBytes(data, length);
  return true;
}

static void IRAM_ATTR touch_int_cb(void) { g_touch_int_flag = true; }

void bsp_touch_init(TwoWire *touch_i2c, int tp_rst, int tp_int,
                    uint16_t rotation, uint16_t width, uint16_t height) {
  g_touch_i2c = touch_i2c;
  g_width = width;
  g_height = height;
  g_rotation = rotation;
  g_touch_data.touch_num = 0;

  pinMode(tp_rst, OUTPUT);
  digitalWrite(tp_rst, LOW);
  delay(200);
  digitalWrite(tp_rst, HIGH);
  delay(300);

  // Match ESP-IDF factory: INPUT (no pull), falling edge.
  pinMode(tp_int, INPUT);
  attachInterrupt(tp_int, touch_int_cb, FALLING);

  uint8_t data[3] = {0};
  if (touch_i2c_read(AXS5106L_ADDR, AXS5106L_ID_REG, data, 3) && data[0] != 0) {
    Serial.printf("AXS5106L id: %u %u %u\n", data[0], data[1], data[2]);
  } else {
    Serial.println("AXS5106L: id read failed or empty");
  }
}

void bsp_touch_read(void) {
  // Factory firmware always polls I2C (no INT gate). INT alone is not enough
  // for continuous swipe tracking on this panel.
  uint8_t data[14] = {0};
  g_touch_int_flag = false;

  if (!touch_i2c_read(AXS5106L_ADDR, AXS5106L_TOUCH_DATA_REG, data, 14)) {
    g_touch_data.touch_num = 0;
    return;
  }

  uint8_t points = data[1] & 0x0f;
  if (points > MAX_TOUCH_MAX_POINTS) {
    points = MAX_TOUCH_MAX_POINTS;
  }
  g_touch_data.touch_num = points;
  if (points == 0) {
    return;
  }

  for (uint8_t i = 0; i < points; i++) {
    g_touch_data.coords[i].x =
        ((uint16_t)(data[2 + i * 6] & 0x0f) << 8) | data[3 + i * 6];
    g_touch_data.coords[i].y =
        ((uint16_t)(data[4 + i * 6] & 0x0f) << 8) | data[5 + i * 6];
  }
}

bool bsp_touch_get_coordinates(touch_data_t *touch_data) {
  if (touch_data == NULL || g_touch_data.touch_num == 0) {
    return false;
  }

  touch_data->touch_num = g_touch_data.touch_num;
  for (int i = 0; i < g_touch_data.touch_num; i++) {
    switch (g_rotation) {
      case 1:
        touch_data->coords[i].y = g_touch_data.coords[i].x;
        touch_data->coords[i].x = g_touch_data.coords[i].y;
        break;
      case 2:
        touch_data->coords[i].x = g_touch_data.coords[i].x;
        touch_data->coords[i].y = g_height - 1 - g_touch_data.coords[i].y;
        break;
      case 3:
        touch_data->coords[i].y = g_height - 1 - g_touch_data.coords[i].x;
        touch_data->coords[i].x = g_width - 1 - g_touch_data.coords[i].y;
        break;
      default:
        touch_data->coords[i].x = g_width - 1 - g_touch_data.coords[i].x;
        touch_data->coords[i].y = g_touch_data.coords[i].y;
        break;
    }
  }
  return true;
}

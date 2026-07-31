#pragma once

// Waveshare ESP32-S3-LCD-1.47B pin map
// https://www.waveshare.com/wiki/ESP32-S3-LCD-1.47B

namespace board {

constexpr int LCD_MOSI = 45;
constexpr int LCD_SCLK = 40;
constexpr int LCD_CS = 42;
constexpr int LCD_DC = 41;
constexpr int LCD_RST = 39;
constexpr int LCD_BL = 46;

constexpr int LCD_WIDTH = 172;
constexpr int LCD_HEIGHT = 320;

constexpr int RGB_LED = 38;

constexpr int IMU_SCL = 47;
constexpr int IMU_SDA = 48;

constexpr int SD_CMD = 15;
constexpr int SD_SCK = 14;
constexpr int SD_D0 = 16;
constexpr int SD_D1 = 18;
constexpr int SD_D2 = 17;
constexpr int SD_D3 = 21;

}  // namespace board

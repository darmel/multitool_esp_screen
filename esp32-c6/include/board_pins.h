#pragma once

// Waveshare ESP32-C6-Touch-LCD-1.47 pin map
// https://docs.waveshare.com/ESP32-C6-Touch-LCD-1.47

namespace board {

constexpr int LCD_SCK = 1;
constexpr int LCD_MOSI = 2;
constexpr int LCD_CS = 14;
constexpr int LCD_DC = 15;
constexpr int LCD_RST = 22;
constexpr int LCD_BL = 23;

constexpr int LCD_WIDTH = 172;
constexpr int LCD_HEIGHT = 320;

constexpr int TP_SDA = 18;
constexpr int TP_SCL = 19;
constexpr int TP_RST = 20;
constexpr int TP_INT = 21;

constexpr int IMU_SDA = 18;
constexpr int IMU_SCL = 19;
constexpr int IMU_INT1 = 5;
constexpr int IMU_INT2 = 6;

constexpr int SD_SCK = 1;
constexpr int SD_MOSI = 2;
constexpr int SD_MISO = 3;
constexpr int SD_CS = 4;

constexpr int BAT_ADC = 0;
constexpr int BOOT_BTN = 8;

// No onboard WS2812 on the Touch variant (GPIO8 is BOOT).
// Alert light uses LCD backlight; see rgb_led.cpp.
constexpr int RGB_LED = -1;

}  // namespace board

# ESP32-C6-Touch-LCD-1.47 — docs

Fuente oficial: [docs.waveshare.com/ESP32-C6-Touch-LCD-1.47](https://docs.waveshare.com/ESP32-C6-Touch-LCD-1.47)

## Hardware (resumen)

| Pieza | Detalle |
|---|---|
| MCU | ESP32-C6FH8, WiFi 6 + BLE 5, **8 MB Flash** |
| LCD | IPS 172×320, driver **JD9853** (SPI) |
| Touch | AXS5106L (I2C) |
| IMU | QMI8658A (I2C compartido) |
| Extra | TF SPI, carga ETA6098, BAT_ADC GPIO0 |
| RGB LED | **No** en esta variante Touch (GPIO8 = BOOT) |

## Pines LCD

| Señal | GPIO |
|---|---|
| SCK | 1 |
| MOSI | 2 |
| CS | 14 |
| DC | 15 |
| RST | 22 |
| BL | 23 |

## Touch

| Señal | GPIO |
|---|---|
| SDA | 18 |
| SCL | 19 |
| RST | 20 |
| INT | 21 |

En firmware: `bsp_touch_read()` hace **poll I2C continuo** (como el `touch_test` del factory ESP-IDF). La INT sola no alcanza para swipes fluidos.

## Driver en Arduino

Waveshare **no usa TFT_eSPI** en esta placa. Usa `GFX_Library_for_Arduino` + `Arduino_ST7789` + secuencia de init JD9853 (`lcd_reg_init`). Ver `examples/01_gfx_helloworld.ino`.

Demo oficial: https://files.waveshare.com/wiki/ESP32-C6-Touch-LCD-1.47/ESP32-C6-Touch-LCD-1.47-Demo.zip

## En esta carpeta

- `ESP32-C6-Touch-LCD-1.47-Schematic.pdf`
- `wiki/` — texto scrapeado de la wiki
- `examples/` — helloworld y demos extractos

La carpeta raíz `ESP32-C6-Touch-LCD-1.47-Demo/` (zip completo) es referencia local y está **gitignored**.

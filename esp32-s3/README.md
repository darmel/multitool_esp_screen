# ESP32-S3 multitool

Placa: **Waveshare ESP32-S3-LCD-1.47B**  
Driver: **ST7789** + [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)  
RGB: WS2812 en **GPIO38**

Arquitectura compartida: [README raíz](../README.md).

## Qué corre hoy

1. **Weather** — Córdoba, Open-Meteo  
2. **Stopwatch** — Start / Pause / Reset  
3. **Timer** — presets + custom; alerta overtime (pantalla + NeoPixel)

Navegación / controles (sin touch):

| Acción | BOOT |
|---|---|
| Siguiente herramienta | click corto |
| Start / Pause | hold largo |
| Reset / Cancel | doble click |

## Setup

```bash
cp include/secrets.h.example include/secrets.h   # WiFi
pio run -t upload
pio device monitor   # 115200
```

Pines y flags TFT_eSPI están en `platformio.ini` y `include/board_pins.h`.

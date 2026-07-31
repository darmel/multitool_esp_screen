# ESP32-C6 multitool

Placa: **Waveshare ESP32-C6-Touch-LCD-1.47**  
Driver: **JD9853** + [Arduino_GFX](https://github.com/moononournation/Arduino_GFX)  
Touch: **AXS5106L** (`lib/esp_lcd_touch_axs5106l/`)

Arquitectura compartida: [README raíz](../README.md).  
Hardware / pines / schematic: [`docs/`](docs/).

## Qué corre hoy

1. **Weather** — Córdoba, Open-Meteo  
2. **Stopwatch** — Start / Pause / Reset  
3. **Timer** — presets + custom; alerta overtime (pantalla verde/rojo + backlight)

Navegación: **swipe ↑/↓**. Controles: **tap**.

## Setup

```bash
cp include/secrets.h.example include/secrets.h   # WiFi
pio run -t upload
pio device monitor   # 115200
```

Platform: pioarduino `espressif32` (ver `platformio.ini`). Flash 8 MB.

## Notas

- El touch se lee por **poll I2C** (no solo INT), igual que el test factory.
- Esta variante **no tiene LED RGB WS2812**; la alerta usa backlight.
- Carpeta `../ESP32-C6-Touch-LCD-1.47-Demo/` (si existe) es el zip oficial de Waveshare; está en `.gitignore`.
